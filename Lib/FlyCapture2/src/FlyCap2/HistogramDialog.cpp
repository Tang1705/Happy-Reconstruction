//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#include "stdafx.h"
#include "FlyCap2_MFC.h"
#include "HistogramDialog.h"

using namespace FlyCapture2;
using namespace Histogram;

// HistogramDialog dialog

IMPLEMENT_DYNAMIC(HistogramDialog, CDialog)

	HistogramDialog::HistogramDialog(CWnd* pParent /*=NULL*/)
: CDialog(HistogramDialog::IDD, pParent)
{
	m_running = false;
	m_updateLoopThread = NULL;
	m_pRowColStats = new RowColStats();
	m_pRowColStatsBuffer = new RowColStats();
	m_threadDoneEvent = CreateEvent(NULL,FALSE,FALSE,"Update histogram thread finish");
	m_hRowColStatMutex = CreateMutex(NULL,FALSE,"Update row / column plot statistics");
}


HistogramDialog::~HistogramDialog()
{
	CloseHandle(m_threadDoneEvent);
	CloseHandle(m_hRowColStatMutex);
	delete m_pRowColStats;
	delete m_pRowColStatsBuffer;
	delete m_updateLoopThread;
}

void HistogramDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABCTRL_HISTOGRAM, m_tabControl);
	DDX_Control(pDX, IDC_STATIC_DRAWINGAREA, m_drawingAreaStaticFrame);
}


	BEGIN_MESSAGE_MAP(HistogramDialog, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_HISTOGRAM, &HistogramDialog::OnTcnSelchangeTabHistogram)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL HistogramDialog::OnInitDialog()
{
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,FALSE);
	if (CDialog::OnInitDialog() == FALSE)
	{
		MessageBox("Fail to initialize Histogram Dialog");
		return FALSE;
	}


	if (m_tabControl.InsertItem(0,"Histogram") == -1)
	{
		MessageBox("Failed to insert histogram tab page");
		return FALSE;
	}

	if (m_tabControl.InsertItem(1,"Row / Column Plot") == -1)
	{
		MessageBox("Failed to insert Row / Column Plot tab page");
		return FALSE;
	}


	if (m_histogramPage.Create(IDD_TABPAGE_HISTOGRAM,&m_tabControl) == FALSE)
	{
		MessageBox("Failed to create histogram tab page");
		return FALSE;
	}

	if (m_rowColPlotPage.Create(IDD_TABPAGE_ROWCOLPLOT,&m_tabControl) == FALSE)
	{
		MessageBox("Failed to create Row / Column Plot tab page");
		return FALSE;
	}
	m_drawingArea.SetDrawingArea(&m_drawingAreaStaticFrame);
	//m_hStatsMutex = ::CreateMutex(NULL, FALSE, "Image Histogram Data");
	//Calculate page size
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	m_tabControl.GetClientRect(&tabRect);
	m_tabControl.GetItemRect(0, &itemRect);
	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-2;
	nYc=tabRect.bottom-nY-2;

	//config page setting
	m_histogramPage.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);//display this page first
	m_rowColPlotPage.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	m_drawMode = Histogram::MODE_HISTOGRAM;

	return TRUE;
}
// HistogramDialog message handlers

void HistogramDialog::OnTcnSelchangeTabHistogram(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(m_tabControl.GetCurSel())
	{
		case 0:
			m_histogramPage.ShowWindow(SW_SHOW);
			m_rowColPlotPage.ShowWindow(SW_HIDE);
			m_drawMode = Histogram::MODE_HISTOGRAM;
			break;
		case 1:
			m_histogramPage.ShowWindow(SW_HIDE);
			m_rowColPlotPage.ShowWindow(SW_SHOW);
			m_drawMode = Histogram::MODE_ROWCOL;
			break;
		default:
			MessageBox("Unknown page index.");
			break;
	}
	*pResult = 0;
}

void HistogramDialog::Update()
{
	CSingleLock bufferLock(&m_stats_input_buffer);

	EnableForPixelFormat( m_image.GetPixelFormat() );
	switch (m_drawMode)
	{
		case Histogram::MODE_HISTOGRAM:
			bufferLock.Lock();
			m_image.CalculateStatistics( m_histogramPage.GetImageStatisticsBuffer());
			bufferLock.Unlock();
			m_histogramPage.UpdateHistogramStatToBuffer();
			m_histogramPage.SwapBuffer();
			break;

		case Histogram::MODE_ROWCOL:
			bufferLock.Lock();
			m_rowColPlotPage.CalculateRowColStats( &m_image, m_pRowColStatsBuffer );
			bufferLock.Unlock();
			if (WaitForSingleObject(m_hRowColStatMutex,1000) == WAIT_OBJECT_0)
			{
				Histogram::RowColStats* pTemp = m_pRowColStats;
				m_pRowColStats = m_pRowColStatsBuffer;
				m_pRowColStatsBuffer = pTemp;
				ReleaseMutex(m_hRowColStatMutex);
			}
			break;
	}
}

void HistogramDialog::SetImageForStatistics(Image image)
{

	CSingleLock bufferLock(&m_stats_input_buffer);
	//bool bIs16bit = false;
	switch (image.GetPixelFormat())
	{
		case PIXEL_FORMAT_MONO8:

			bufferLock.Lock();
			m_image.DeepCopy( &image );
			bufferLock.Unlock();
			break;
		case PIXEL_FORMAT_MONO12:
			bufferLock.Lock();
			image.Convert(PIXEL_FORMAT_MONO16, &m_image);
			bufferLock.Unlock();
			break;
		case PIXEL_FORMAT_MONO16:
			//bIs16bit = true;
			bufferLock.Lock();
			m_image.DeepCopy( &image );
			bufferLock.Unlock();
			break;
		default:
			// raw image format can not be calculated,
			// so we just convert it to BGR format.
			bufferLock.Lock();
			image.Convert(PIXEL_FORMAT_BGR, &m_image);
			bufferLock.Unlock();
	}

	//ReleaseMutex(m_hStatsMutex);
	/*if (bIs16bit == true)
	  {
	  m_histogramPage.EnableBinningRadioButton(Histogram::BINNING_8_16_BITS);
	  m_histogramPage.EnableBinningRadioButton(Histogram::BINNING_10_BITS);
	  m_histogramPage.EnableBinningRadioButton(Histogram::BINNING_12_BITS);
	  }
	  else
	  {
	  m_histogramPage.EnableBinningRadioButton(Histogram::BINNING_8_16_BITS);
	  m_histogramPage.DisableBinningRadioButton(Histogram::BINNING_10_BITS);
	  m_histogramPage.DisableBinningRadioButton(Histogram::BINNING_12_BITS);
	  m_histogramPage.SetBinningSelection(Histogram::BINNING_8_16_BITS);
	  }*/

	//the binning function has not implemented yet, just disable radio buttons for now
	m_histogramPage.DisableBinningRadioButton(Histogram::BINNING_8_16_BITS);
	m_histogramPage.DisableBinningRadioButton(Histogram::BINNING_10_BITS);
	m_histogramPage.DisableBinningRadioButton(Histogram::BINNING_12_BITS);

	SetEvent(m_imageReadyEvent);
}

void HistogramDialog::EnableForPixelFormat( PixelFormat pixelFormat )
{
	if (m_prevPixelFormat == pixelFormat)
	{
		//Nothing changed
		return;
	}

	//change setting for histogram page
	switch (pixelFormat)
	{
		case PIXEL_FORMAT_MONO8:
		case PIXEL_FORMAT_MONO12:
		case PIXEL_FORMAT_MONO16:
			m_histogramPage.EnableChannel( ImageStatistics::GREY );
			m_histogramPage.DisableChannel( ImageStatistics::RED );
			m_histogramPage.DisableChannel( ImageStatistics::GREEN );
			m_histogramPage.DisableChannel( ImageStatistics::BLUE );
			m_histogramPage.DisableChannel( ImageStatistics::HUE );
			m_histogramPage.DisableChannel( ImageStatistics::SATURATION );
			m_histogramPage.DisableChannel( ImageStatistics::LIGHTNESS );
			break;
		case PIXEL_FORMAT_BGR:
		case PIXEL_FORMAT_RGB:
		case PIXEL_FORMAT_BGRU:
		case PIXEL_FORMAT_RGBU:
			m_histogramPage.EnableChannel( ImageStatistics::GREY );
			m_histogramPage.EnableChannel( ImageStatistics::RED );
			m_histogramPage.EnableChannel( ImageStatistics::GREEN );
			m_histogramPage.EnableChannel( ImageStatistics::BLUE );
			m_histogramPage.EnableChannel( ImageStatistics::HUE );
			m_histogramPage.EnableChannel( ImageStatistics::SATURATION );
			m_histogramPage.EnableChannel( ImageStatistics::LIGHTNESS );
			break;
		default:
			DisableAllHistogramChannel();
			break;
	}


	//change setting for row / column plot page
	switch (pixelFormat)
	{
		case PIXEL_FORMAT_MONO8:
		case PIXEL_FORMAT_MONO12:
		case PIXEL_FORMAT_MONO16:
			m_rowColPlotPage.DisableColorChannelCheckBoxes();
			break;
		case PIXEL_FORMAT_BGR:
		case PIXEL_FORMAT_RGB:
		case PIXEL_FORMAT_BGRU:
		case PIXEL_FORMAT_RGBU:
			m_rowColPlotPage.EnableColorChannelCheckBoxes();
			break;
		default:
			break;
	}


	m_histogramPage.CleanCheckStatus();
	m_prevPixelFormat = pixelFormat;
}

void HistogramDialog::DisableAllHistogramChannel()
{
	m_histogramPage.DisableChannel( ImageStatistics::GREY );
	m_histogramPage.DisableChannel( ImageStatistics::RED );
	m_histogramPage.DisableChannel( ImageStatistics::GREEN );
	m_histogramPage.DisableChannel( ImageStatistics::BLUE );
	m_histogramPage.DisableChannel( ImageStatistics::HUE );
	m_histogramPage.DisableChannel( ImageStatistics::SATURATION );
	m_histogramPage.DisableChannel( ImageStatistics::LIGHTNESS );
}

void HistogramDialog::OnOK()
{
	// Do nothing
	// this dialog will be hidden when user press enter
	// In order to avoid that bug we must override this function
}

void HistogramDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// check to see if window has been created, if not the resize action will crash program
	if (IsWindow( m_hWnd ) == TRUE &&
			IsWindow(m_tabControl.GetSafeHwnd())&&
			IsWindow(m_drawingAreaStaticFrame.GetSafeHwnd()))
	{
		static const int sk_padded = 10;
		CRect tabRect;
		m_tabControl.GetWindowRect(&tabRect);
		int tabControlHeight = tabRect.Height();
		m_drawingAreaStaticFrame.MoveWindow(
				sk_padded ,
				sk_padded ,
				cx-(2*sk_padded) ,
				(cy - tabControlHeight) - 3*sk_padded);
		m_tabControl.MoveWindow(
				sk_padded ,
				cy - tabControlHeight - sk_padded,
				cx - (2*sk_padded),
				tabControlHeight);
	}
	InvalidateRect(NULL,TRUE);
	GetUpdateRect(NULL,FALSE);
}

void HistogramDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	//just temp values feel free to change it
	lpMMI->ptMinTrackSize.x =  570;
	lpMMI->ptMinTrackSize.y =  400;
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void HistogramDialog::OnClose()
{
	m_histogramPage.UncheckAverage();
	StopUpdate();
	ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

UINT HistogramDialog::ThreadUpdateStats( void* pparam )
{
	TRACE("Histogram update thread - start\n");
	HistogramDialog* pDoc = ((HistogramDialog*)pparam);
	UINT retVal = pDoc->DoUpdateStats();
	SetEvent(pDoc->m_threadDoneEvent );
	TRACE("Histogram update thread - exit\n");
	return retVal;
}

UINT HistogramDialog::DoUpdateStats()
{
	// Start of dialog data update loop
	while(m_running)
	{
		if (IsWindow( m_hWnd ) && IsWindowVisible())
		{
			DWORD retVal = WaitForSingleObject(m_imageReadyEvent, INFINITE);
			if (retVal == WAIT_OBJECT_0)
			{
				Update();
			}

		}
	}
	return 0;
}

void HistogramDialog::StopUpdate()
{
	m_running = false;
	/*
TODO: figure out why the code below is not working

if (m_running == true)
{
m_running = false;

DWORD dwRet = WaitForSingleObject(m_threadDoneEvent, INFINITE);
	//DWORD dwRet = WaitForSingleObject(m_updateLoopThread->m_hThread, INFINITE);
	if ( dwRet == WAIT_OBJECT_0 )
	{
	//TRACE("Histogram update thread - exit\n");
	m_updateLoopThread = NULL;
	}
	else
	{
	if (TerminateThread(m_updateLoopThread->m_hThread,0) == TRUE)// force thread exit
	{
	TRACE("Histogram update thread - force exit\n");
	//m_drawingArea.CleanUp();
	}
	else
	{
	TRACE("Histogram update thread - exit fail...\n");
	}
	}
	}*/
	}

void HistogramDialog::StartUpdate()
{
	if (m_running == false)
	{
		m_imageReadyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		m_running = true;
		m_updateLoopThread = AfxBeginThread( ThreadUpdateStats, this);
	}
}
void HistogramDialog::OnPaint()
{
	//Update drawing area
	switch (m_drawMode)
	{
		case Histogram::MODE_HISTOGRAM:
			if (WaitForSingleObject(m_histogramPage.m_statsMutex,1000) == WAIT_OBJECT_0)
			{
				m_drawingArea.Update(
						m_histogramPage.GetImageStatistics(),
						m_histogramPage.GetHistogramMax(),
						m_histogramPage.GetNumOfFrames());
				ReleaseMutex(m_histogramPage.m_statsMutex);
			}
			break;
		case Histogram::MODE_ROWCOL:
			if (WaitForSingleObject(m_hRowColStatMutex,1000) == WAIT_OBJECT_0)
			{
				m_drawingArea.Update(m_pRowColStats);
				ReleaseMutex(m_hRowColStatMutex);
			}
			break;
	}
	CDialog::OnPaint();
}
