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
#include "HistogramPage.h"

using namespace FlyCapture2;
using namespace Histogram;

// HistogramPage dialog

IMPLEMENT_DYNAMIC(HistogramPage, CDialog)

	HistogramPage::HistogramPage(CWnd* pParent /*=NULL*/)
	: CDialog(HistogramPage::IDD, pParent)
	, m_maxPercentValue(100)
	  , m_binningSelection(0)
{
	m_pHistogramStats = new ImageStatistics();
	m_pHistogramStatsBuffer = new ImageStatistics();
	for (int i=0; i < ImageStatistics::NUM_STATISTICS_CHANNELS; i++)
	{
		m_bChannelEnabled[i] = false;
		m_bValueChanged[i] = true;

		m_prevPixelValueMin[i] = 0;
		m_prevPixelValueMax[i] = 0;
		m_prevPixelValueMean[i] = 0;
		m_numOfFrames[i] = 0;
	}
	m_histogramMax = 100;
	m_statsMutex = CreateMutex(NULL,FALSE,"Stat update Mutex");
}

HistogramPage::~HistogramPage()
{
	CloseHandle(m_statsMutex);
	delete m_pHistogramStats;
	delete m_pHistogramStatsBuffer;
}

void HistogramPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHANNEL, m_channelsTable);
	DDX_Text(pDX, IDC_PERCENT_EDIT, m_maxPercentValue);
	DDV_MinMaxUInt(pDX, m_maxPercentValue, 1, 100);
	DDX_Control(pDX, IDC_PERCENT_SPIN, m_maxPercentSpinButton);
	DDX_Control(pDX, IDC_AVERAGE_CHECK, m_enableAverageCheckBox);
	DDX_Radio(pDX, IDC_8_16_BIT_RADIO, m_binningSelection);
}


BEGIN_MESSAGE_MAP(HistogramPage, CDialog)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CHANNEL, &HistogramPage::OnChannelCheckStateChanged)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CHANNEL, &HistogramPage::OnNMCustomdrawListChannel)
	ON_EN_CHANGE(IDC_PERCENT_EDIT, &HistogramPage::OnEnChangePercentEdit)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


	// HistogramPage message handlers

BOOL HistogramPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_channelsTable.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);

	static const LPSTR headerName[Histogram::NUM_OF_COLUMNS] = {"Channel","Range","Mean","Min","Max"};
	LVCOLUMN lvColumn;
	CRect tableRect;
	m_channelsTable.GetWindowRect(&tableRect);
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = (tableRect.Width()/Histogram::NUM_OF_COLUMNS);
	for (int i = 0; i < Histogram::NUM_OF_COLUMNS; i++)
	{
		lvColumn.pszText = headerName[i];
		m_channelsTable.InsertColumn(i, &lvColumn);
	}

	for (int i = 0; i < ImageStatistics::NUM_STATISTICS_CHANNELS; i++)
	{
		int nItem = m_channelsTable.InsertItem(i,
				GetChannelString((ImageStatistics::StatisticsChannel)i ));
		m_channelsTable.SetItemText(nItem,RANGE,"0 - 0");
		m_channelsTable.SetItemText(nItem,MEAN,"0.00");
		m_channelsTable.SetItemText(nItem,MIN,"0");
		m_channelsTable.SetItemText(nItem,MAX,"0");
	}
	m_maxPercentSpinButton.SetRange(1,100);
	m_maxPercentSpinButton.SetBuddy(GetDlgItem(IDC_PERCENT_EDIT));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

const char* HistogramPage::GetChannelString( ImageStatistics::StatisticsChannel channel )
{
	switch (channel)
	{
		case ImageStatistics::GREY:
			return "Grey";
		case ImageStatistics::RED:
			return "Red";
		case ImageStatistics::GREEN:
			return "Green";
		case ImageStatistics::BLUE:
			return "Blue";
		case ImageStatistics::HUE:
			return "Hue";
		case ImageStatistics::SATURATION:
			return "Saturation";
		case ImageStatistics::LIGHTNESS:
			return "Lightness";
		default:
#ifdef _DEBUG
			//this should not happen,
			//if you added a new type in ImageStatistics
			//please add a related string above the default case.
			DebugBreak();
#endif
			return "Unknown";
	}
}


void HistogramPage::OnChannelCheckStateChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	m_channelsTable.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED);//Cancel the selection, we don't need this

	if (pNMLV->iSubItem == 0)
	{
		ImageStatistics::StatisticsChannel channel = (ImageStatistics::StatisticsChannel)pNMLV->iItem;
		//char buff[64];
		if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */
				&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */
		  )
		{
			//sprintf_s(buff,"iItem:%d is checked",pNMLV->iItem);
			//MessageBox(buff);
			/*if (WaitForSingleObject(m_statsMutex,INFINITE) == WAIT_OBJECT_0)
			  {
			  m_pHistogramStats->SetChannelStatus(channel,true);
			  ReleaseMutex(m_statsMutex);
			  }*/
			m_pHistogramStats->SetChannelStatus(channel,true);
			m_pHistogramStatsBuffer->SetChannelStatus(channel,true);
		}
		else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */
				&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */
			   )
		{
			//sprintf_s(buff,"iItem:%d is unchecked",pNMLV->iItem);
			//MessageBox(buff);
			/*if (WaitForSingleObject(m_statsMutex,INFINITE) == WAIT_OBJECT_0)
			  {
			  m_pHistogramStats->SetChannelStatus(channel,false);
			  ReleaseMutex(m_statsMutex);
			  }*/
			m_pHistogramStats->SetChannelStatus(channel,false);
			m_pHistogramStatsBuffer->SetChannelStatus(channel,false);
			//reset average statistic value when this channel get uncheck action
			m_numOfFrames[channel] = 0;
		}
		else
		{
			if (pNMLV->uOldState == 0 &&
					m_bChannelEnabled[channel] == false)
			{
				//set check box to invisible when channel is disabled
				m_channelsTable.SetItemState(channel,0,LVIS_STATEIMAGEMASK);
			}
		}
	}
	*pResult = 0;
}

bool HistogramPage::SwapBuffer()
{
	if (WaitForSingleObject(m_statsMutex,1000) == WAIT_OBJECT_0)
	{
		FlyCapture2::ImageStatistics* pTemp;
		pTemp = m_pHistogramStats;
		m_pHistogramStats = m_pHistogramStatsBuffer;
		m_pHistogramStatsBuffer = pTemp;
		ReleaseMutex(m_statsMutex);
		return true;
	}
	return false;
}

void HistogramPage::UpdateHistogramStatToBuffer()
{
	for (int i=0; i < ImageStatistics::NUM_STATISTICS_CHANNELS; i++)
	{
		UpdateSingleChannel((ImageStatistics::StatisticsChannel)i);
	}
}

void HistogramPage::UpdateSingleChannel( ImageStatistics::StatisticsChannel channel )
{
	// If the channel is disabled, then there is no updating to be done
	if ( m_bChannelEnabled[channel] == false )
	{
		return;
	}

	bool enabled = false;
	Error error = m_pHistogramStatsBuffer->GetChannelStatus( channel, &enabled );
	if (error != PGRERROR_OK)
	{
		return;
	}

	if ( enabled != true )
	{
		if (m_bValueChanged[channel] == true)
		{
			//set all value to zero
			m_channelsTable.SetCheck(channel,FALSE);
			const char* rangeZero = "0 - 0";
			const char* meanZero = "0.00";
			const char* minZero = "0";
			const char* maxZero = "0";
			m_channelsTable.SetItemText(channel,Histogram::RANGE,rangeZero);
			m_channelsTable.SetItemText(channel,Histogram::MEAN,meanZero);
			m_channelsTable.SetItemText(channel,Histogram::MIN,minZero);
			m_channelsTable.SetItemText(channel,Histogram::MAX,maxZero);
		}
		m_bValueChanged[channel] = false;
	}
	else
	{
		m_bValueChanged[channel] = true;
		unsigned int rangeMin, rangeMax, pixelValueMin, pixelValueMax;
		unsigned int numPixelValues;
		float pixelValueMean;
		m_pHistogramStatsBuffer->GetStatistics(
				channel,
				&rangeMin,
				&rangeMax,
				&pixelValueMin,
				&pixelValueMax,
				&numPixelValues,
				&pixelValueMean );


		m_channelsTable.SetCheck(channel,TRUE);
		char rangeStr[32];
		char meanStr[32];
		char maxStr[32];
		char minStr[32];

		if (m_enableAverageCheckBox.GetCheck() == TRUE)
		{
			float averageValueMin = ((m_prevPixelValueMin[channel] * m_numOfFrames[channel]) + pixelValueMin )/ (m_numOfFrames[channel]+1);
			float averageValueMax = ((m_prevPixelValueMax[channel] * m_numOfFrames[channel]) + pixelValueMax )/ (m_numOfFrames[channel]+1);
			//pixelValueMin = static_cast<int>(averageValueMin);
			//pixelValueMax = static_cast<int>(averageValueMax);
			pixelValueMean = ((m_prevPixelValueMean[channel] * m_numOfFrames[channel]) + pixelValueMean )/ (m_numOfFrames[channel]+1);
			//m_numOfFrames[channel]++; //Attention: the increment action happens in drawing function (HistogramDrawingArea::GetPercentages()), not here
			m_prevPixelValueMin[channel] = averageValueMin;
			m_prevPixelValueMax[channel] = averageValueMax;
			m_prevPixelValueMean[channel] = pixelValueMean;
			sprintf( minStr, "%3.2f", averageValueMin );
			sprintf( maxStr, "%3.2f", averageValueMax );
		}
		else
		{
			m_numOfFrames[channel] = 0;
			sprintf( minStr, "%d", pixelValueMin );
			sprintf( maxStr, "%d", pixelValueMax );
		}

		sprintf( rangeStr, "%d - %d", rangeMin, rangeMax );
		sprintf( meanStr, "%3.2f", pixelValueMean );

		m_channelsTable.SetItemText(channel,Histogram::RANGE,rangeStr);
		m_channelsTable.SetItemText(channel,Histogram::MEAN,meanStr);
		m_channelsTable.SetItemText(channel,Histogram::MIN,minStr);
		m_channelsTable.SetItemText(channel,Histogram::MAX,maxStr);
	}

	//TRACE("Exiting\n");
}
ImageStatistics* HistogramPage::GetImageStatistics()
{
	return (m_pHistogramStats);
}
ImageStatistics* HistogramPage::GetImageStatisticsBuffer()
{
	return (m_pHistogramStatsBuffer);
}

void HistogramPage::OnNMCustomdrawListChannel(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if ( pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT )
	{
		// This is the prepaint stage for an item. Here's where we set the
		// item's text color. Our return value will tell Windows to draw the
		// item itself, but it will use the new color we set here.
		if (m_bChannelEnabled[pLVCD->nmcd.dwItemSpec] == false)
		{
			COLORREF crText;
			crText = RGB(200,200,200);
			pLVCD->clrText = crText;
		}
		else
		{
			COLORREF crText;
			crText = RGB(0,0,0);
			pLVCD->clrText = crText;
		}
		*pResult = CDRF_DODEFAULT;
	}
}
void HistogramPage::EnableChannel(ImageStatistics::StatisticsChannel channel )
{
	m_bChannelEnabled[channel] = true;
}

void HistogramPage::DisableChannel(ImageStatistics::StatisticsChannel channel )
{
	const char* naStr = "N/A";
	m_bChannelEnabled[channel] = false;
	m_channelsTable.SetItemState(channel,0,LVIS_STATEIMAGEMASK);//hide check box
	m_channelsTable.SetItemText(channel,Histogram::RANGE,naStr);
	m_channelsTable.SetItemText(channel,Histogram::MEAN,naStr);
	m_channelsTable.SetItemText(channel,Histogram::MIN,naStr);
	m_channelsTable.SetItemText(channel,Histogram::MAX,naStr);
}

void HistogramPage::OnOK()
{
	// Do nothing
	// this dialog will be hidden when user press enter
	// In order to avoid that bug we must override this function
}
unsigned int HistogramPage::GetHistogramMax()
{
	return m_histogramMax;
}
void HistogramPage::OnEnChangePercentEdit()
{
	UpdateData(TRUE);
	if (m_maxPercentValue <= 100 && m_maxPercentValue >= 1)
	{
		m_histogramMax = m_maxPercentValue;
	}
	else
	{
		//restore data if is not in range 1 ~ 100
		m_maxPercentValue = m_histogramMax;
		UpdateData(FALSE);
	}
}
unsigned int* HistogramPage::GetNumOfFrames()
{
	return m_numOfFrames;
}
void HistogramPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (bShow == FALSE)
	{
		UncheckAverage();
	}
}
void HistogramPage::UncheckAverage()
{
	m_enableAverageCheckBox.SetCheck(FALSE);
}
void HistogramPage::CleanCheckStatus()
{
	for (int i=0; i < ImageStatistics::NUM_STATISTICS_CHANNELS; i++)
	{
		m_channelsTable.SetCheck(i,FALSE);
	}
	/*if (WaitForSingleObject(m_statsMutex,INFINITE) == WAIT_OBJECT_0)
	  {
	  m_pHistogramStats->DisableAll();
	  ReleaseMutex(m_statsMutex);
	  }*/
	m_pHistogramStats->DisableAll();
	m_pHistogramStatsBuffer->DisableAll();
}

BinningType HistogramPage::GetBinningSelection()
{
	BinningType result;
	UpdateData();
	switch(m_binningSelection)
	{
		case 0:
			result = BINNING_8_16_BITS;
			break;
		case 1:
			result = BINNING_10_BITS;
			break;
		case 2:
			result = BINNING_12_BITS;
			break;
		default:
			result = NUM_OF_BINNING_TYPES;
#ifdef _DEBUG
			//bug: this should not happen, please add new case above
			DebugBreak();
#endif
	}
	return result;
}

void HistogramPage::SetBinningSelection(BinningType type)
{
	switch(type)
	{
		case BINNING_8_16_BITS:
			CheckRadioButton(IDC_8_16_BIT_RADIO,IDC_12_BIT_RADIO,IDC_8_16_BIT_RADIO);
			break;
		case BINNING_10_BITS:
			CheckRadioButton(IDC_8_16_BIT_RADIO,IDC_12_BIT_RADIO,IDC_10_BIT_RADIO);
			break;
		case BINNING_12_BITS:
			CheckRadioButton(IDC_8_16_BIT_RADIO,IDC_12_BIT_RADIO,IDC_12_BIT_RADIO);
			break;
#ifdef _DEBUG
		default:
			//bug: this should not happen, please add new case above
			DebugBreak();
#endif
	}
}

void HistogramPage::EnableBinningRadioButton(Histogram::BinningType type)
{
	switch(type)
	{
		case BINNING_8_16_BITS:
			GetDlgItem( IDC_8_16_BIT_RADIO )->EnableWindow( TRUE );
			break;
		case BINNING_10_BITS:
			GetDlgItem( IDC_10_BIT_RADIO )->EnableWindow( TRUE );
			break;
		case BINNING_12_BITS:
			GetDlgItem( IDC_12_BIT_RADIO )->EnableWindow( TRUE );
			break;
#ifdef _DEBUG
		default:
			//bug: this should not happen, please add new case above
			DebugBreak();
#endif
	}
}
void HistogramPage::DisableBinningRadioButton(Histogram::BinningType type)
{
	switch(type)
	{
		case BINNING_8_16_BITS:
			GetDlgItem( IDC_8_16_BIT_RADIO )->EnableWindow( FALSE );
			break;
		case BINNING_10_BITS:
			GetDlgItem( IDC_10_BIT_RADIO )->EnableWindow( FALSE );
			break;
		case BINNING_12_BITS:
			GetDlgItem( IDC_12_BIT_RADIO )->EnableWindow( FALSE );
			break;
#ifdef _DEBUG
		default:
			//bug: this should not happen, please add new case above
			DebugBreak();
#endif
	}
}
