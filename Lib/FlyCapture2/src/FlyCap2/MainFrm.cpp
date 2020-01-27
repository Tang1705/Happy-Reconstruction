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
#include "MainFrm.h"
#include "HelpLauncher.h"
#include <IO.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

	BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_VIEW_FULLSCREEN, &CMainFrame::OnViewFullscreen)
	ON_COMMAND(ID_LAUNCH_HELP, &CMainFrame::OnLaunchHelp)
	ON_COMMAND(ID_APP_ABOUT, &CMainFrame::OnAppAbout)
	ON_COMMAND(ID_VIEW_STATUS_BAR, &CMainFrame::OnViewStatusBar)
END_MESSAGE_MAP()

	static UINT indicators[] =
{
	ID_INDICATOR_EVENTS,			// display event status
	ID_SEPARATOR,					// display UI information and camera frame rate status
	ID_INDICATOR_CURSORINFO,		// position for cursor info display.
	ID_INDICATOR_IMAGEINFO          // position for image info display.

};


// CMainFrame construction/destruction
CMainFrame::CMainFrame()
{
	m_fastTimer = NULL;
	m_slowTimer = NULL;
	m_pDoc = NULL;
	m_pView = NULL;

	// Calculates window position and span in full screen mode
	HDC hDC = ::GetDC(NULL);
	int xSpan = GetDeviceCaps(hDC, HORZRES);
	int ySpan = GetDeviceCaps(hDC, VERTRES);
	::ReleaseDC(NULL, hDC);

	m_isFullScreen = false;
	m_requestedFPS = 0.0;

	// Calculates size of window elements
	int borderSizeX = GetSystemMetrics(SM_CXFRAME);
	int captionHeight = GetSystemMetrics(SM_CYCAPTION);
	int menuHeight = 0;//GetSystemMetrics(SM_CYMENU);//enable this will hide menu in full screen mode
	int borderSizeY = GetSystemMetrics(SM_CYFRAME);

	// Calculates window origin and span for full screen mode
	CPoint originSize = CPoint(-borderSizeX, -borderSizeY - captionHeight - menuHeight);
	xSpan += 2 * borderSizeX, ySpan += 2 * borderSizeY + menuHeight + captionHeight;

	// Calculates full screen window rectangle
	m_fullRect = CRect(originSize, CSize(xSpan, ySpan));

	//consider previous status bar and tool bar is invisible
	m_prevIsStatusBarVisible = FALSE;
	m_prevIsToolBarVisible = FALSE;

	m_WarningShown = true;
}

CMainFrame::~CMainFrame()
{
	m_bitmapHelp.DeleteObject();
	m_bitmapAbout.DeleteObject();
	m_bitmapSaveAs.DeleteObject();
	m_bitmapExit.DeleteObject();
	m_bitmapControl.DeleteObject();
	m_bitmapEventStatusBad.DeleteObject();
	m_bitmapEventStatusOK.DeleteObject();
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Load Lucida Grande font
	VERIFY(m_Font.CreatePointFont(80, _T("Lucida Sans Unicode")));

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
				| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
			!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
			!m_wndStatusBar.SetIndicators(indicators,
				sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(0,ID_INDICATOR_EVENTS,SBPS_NORMAL,60);
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,350);
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_CURSORINFO,SBPS_NORMAL,210);
	m_wndStatusBar.SetPaneInfo(3,ID_INDICATOR_IMAGEINFO,SBPS_STRETCH,0);

	m_wndStatusBar.SetFont(&m_Font);

	if( m_fastTimer == NULL )
	{
		m_fastTimer = ::SetTimer( m_hWnd, FAST_TIMER, sk_defualtFastTimerDelay, (TIMERPROC) NULL );
	}
	if( m_slowTimer == NULL )
	{
		m_slowTimer = ::SetTimer( m_hWnd, SLOW_TIMER, sk_defualtSlowTimerDelay, (TIMERPROC) NULL );
	}

	CFlyCap2_MFCDoc* pDoc = (CFlyCap2_MFCDoc*)GetActiveDocument();

	if (m_aboutDlg.Create(AboutDialog::IDD,this) == FALSE)
	{
		TRACE0("Failed to create about dialog box\n");
		return -1;      // fail to create UI
	}

	CMenu* mainMenu = GetMenu();
	m_bitmapHelp.LoadBitmap(IDB_BITMAP_HELP);
	m_bitmapAbout.LoadBitmap(IDB_BITMAP_ABOUT);
	m_bitmapSaveAs.LoadBitmap(IDB_BITMAP_SAVEAS);
	m_bitmapExit.LoadBitmap(IDB_BITMAP_EXIT);
	m_bitmapControl.LoadBitmap(IDB_BITMAP_CONTROL);
	m_bitmapEventStatusBad.LoadBitmap(IDB_BITMAP_EVENT_BAD);
	m_bitmapEventStatusOK.LoadBitmap(IDB_BITMAP_EVENT_OK);
	mainMenu->SetMenuItemBitmaps(ID_LAUNCH_HELP,MF_BYCOMMAND, &m_bitmapHelp, &m_bitmapHelp);
	mainMenu->SetMenuItemBitmaps(ID_APP_ABOUT,MF_BYCOMMAND, &m_bitmapAbout, &m_bitmapAbout);
	mainMenu->SetMenuItemBitmaps(ID_FILE_SAVE_AS,MF_BYCOMMAND, &m_bitmapSaveAs, &m_bitmapSaveAs);
	mainMenu->SetMenuItemBitmaps(ID_APP_EXIT,MF_BYCOMMAND, &m_bitmapExit, &m_bitmapExit);
	mainMenu->SetMenuItemBitmaps(ID_CAMERACONTROL_TOGGLECAMERACONTROL,MF_BYCOMMAND, &m_bitmapControl, &m_bitmapControl);

	//Set Toolbar icon to true color (24 bit)
	CImageList	toolbarImageList;
	CBitmap		toolbarBitmap;

	// Create and set the enabled image list.
	toolbarBitmap.LoadBitmap(IDB_TOOLBAR_ENABLE);
	toolbarImageList.Create(30, 30, ILC_COLORDDB|ILC_MASK, 1, 1);
	toolbarImageList.Add(&toolbarBitmap, RGB(246,246,246));
	m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)toolbarImageList.m_hImageList);
	toolbarImageList.Detach();
	toolbarBitmap.Detach();

	// Create and set the disabled image list.
	toolbarBitmap.LoadBitmap(IDB_TOOLBAR_DISABLE);
	toolbarImageList.Create(30, 30, ILC_COLORDDB|ILC_MASK, 1, 1);
	toolbarImageList.Add(&toolbarBitmap, RGB(246,246,246));
	m_wndToolBar.SendMessage(TB_SETDISABLEDIMAGELIST, 0, (LPARAM)toolbarImageList.m_hImageList);
	toolbarImageList.Detach();
	toolbarBitmap.Detach();

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.SetFont(&m_Font);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	return 0;
}

void CMainFrame::OnDestroy()
{
	if( m_fastTimer != NULL )
	{
		::KillTimer( m_hWnd, m_fastTimer );
	}
	if( m_slowTimer != NULL )
	{
		::KillTimer( m_hWnd, m_slowTimer );
	}
	if (m_wndToolBar.DestroyWindow() == FALSE)
	{
		TRACE("Unable to destroy tool bar\n");
	}
	if (m_wndStatusBar.DestroyWindow() == FALSE)
	{
		TRACE("Unable to destroy status bar\n");
	}
	if (m_aboutDlg.DestroyWindow() == FALSE)
	{
		TRACE("Unable to destroy about dialog\n");
	}
	m_Font.DeleteObject();

	CFrameWnd::OnDestroy();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}
// CMainFrame message handlers

void CMainFrame::UpdateStatusBar()
{
	if ( m_pDoc == NULL || m_pView == NULL )
	{
		return;
	}
	UpdateFrameRateInfoStatus();
	UpdateCursorInfoStatus();
	UpdateImageInfoStatus();
}

void CMainFrame::UpdateEventsStatus()
{
	CString status;
	CDC* pDC = m_wndStatusBar.GetDC();
	CBrush* pBrush;
	if (m_pDoc->HasBadEventRecently() == true)
	{
		pBrush = new CBrush(&m_bitmapEventStatusBad);
		status = "\r\tStreaming Problem. Click Here for more info";
		m_wndStatusBar.SetPaneInfo(0,ID_INDICATOR_EVENTS,SBPS_NORMAL,280);
	}
	else
	{
		pBrush = new CBrush(&m_bitmapEventStatusOK);
		status = "\r\tOK";
		m_wndStatusBar.SetPaneInfo(0,ID_INDICATOR_EVENTS,SBPS_NORMAL,60);
	}
	m_wndStatusBar.SetPaneText(0, status );
	RECT rect;
	rect.left = sk_statusbarIconOffsetX;
	rect.right  = sk_statusbarIconOffsetX + 15;
	rect.top = sk_statusbarIconOffsetY;
	rect.bottom = sk_statusbarIconOffsetY + 15;
	if(m_pDoc->HasBadEventRecently() == true)
	{
		switch (m_WarningShown)
		{
			case true:
				m_WarningShown = false;
				break;
			case false:
				// Clean up old pBrush
				if (pBrush != NULL)
				{
					pBrush->DeleteObject();
					delete pBrush;
				}
				pBrush = new CBrush(RGB(212,208,200));
				m_wndStatusBar.SetPaneText(0, "");
				m_WarningShown = true;
				break;
		}
	}
	pDC->FillRect(&rect,pBrush);
	ReleaseDC(pDC);
	pBrush->DeleteObject();
	delete pBrush;

}
void CMainFrame::UpdateFrameRateInfoStatus()
{
	CString status;
	if (m_pDoc->IsGrabThreadRunning())
	{
		double processedFPS = m_pDoc->GetProcessedFrameRate();
		double displayedFPS = m_pView->GetDisplayedFrameRate();
		status.Format(
				"Frame Rate (Proc/Disp/Req): %3.2f fps / %3.2f fps / %3.2f fps",
				processedFPS,
				displayedFPS,
				m_requestedFPS);
		m_wndStatusBar.SetPaneText( 1, status );
	}
	else
	{
		CString statusBarInfo;
		m_wndStatusBar.GetPaneText(0, statusBarInfo);

		if (statusBarInfo == "Ready" ||
				statusBarInfo.IsEmpty())
		{
			m_wndStatusBar.SetPaneText( 1, "Camera not started." );
		}
	}
}
void CMainFrame::UpdateCursorInfoStatus()
{
	CStatic* pDrawingArea = (CStatic*)m_pView->GetDlgItem(IDC_IMAGEAREA);
	if (pDrawingArea == NULL)
	{
		return;
	}

	CString status;
	int x,y=0;
	m_pView->GetPixelPositionFromImage(&x,&y);

	CPoint dcPoint;
	CDC* pDC = pDrawingArea->GetDC();

	// Fix for Bug 20448
	if(pDC == NULL)
	{
		return;
	}

	HDC hdc = pDC->GetSafeHdc();
	if(hdc == NULL)
	{
		return;
	}

	GetCursorPos(&dcPoint);
	pDrawingArea->ScreenToClient(&dcPoint);
	COLORREF cr = pDC->GetPixel( dcPoint );
	m_pView->ReleaseDC( pDC );

	if( this == GetActiveWindow() &&
			x != -1 && y != -1 )
	{
		status.Format(
				"Cursor: (%d,%d) | RGB: (%u,%u,%u)",
				x,
				y,
				cr & 0xFF,
				(cr & 0xFF00) >> 8,
				(cr & 0xFF0000) >> 16 );
	}
	else
	{
		status.Format("Cursor: (N/A) | RGB: (N/A)");
	}

	m_wndStatusBar.SetPaneText( 2, status );
}

void CMainFrame::UpdateImageInfoStatus()
{
	CString status;
	unsigned int width;
	unsigned int height;
	m_pDoc->GetImageSize( &width, &height );
	RECT windowRect = m_pView->GetDisplaySize();
	status.Format("Zoom: %.1f%% | Image dimensions: (%u x %u) | Display dimensions: (%u x %u)",
			m_pView->GetZoomLevel() * 100.0f,
			width,
			height,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top);
	m_wndStatusBar.SetPaneText( 3, status );
}

void CMainFrame::OnTimer(UINT_PTR idEvent)
{
	CFrameWnd::OnTimer(idEvent);
	if (IsWindowVisible() == TRUE)
	{
		switch (idEvent)
		{
			case FAST_TIMER:
				m_pView = (CFlyCap2_MFCView*)GetActiveView();
				m_pDoc = (CFlyCap2_MFCDoc*)GetActiveDocument();
				UpdateStatusBar();
				if (m_pView != NULL)
				{
					m_pView->UpdateCameraInfoData();
				}
				if (m_pDoc != NULL && m_pDoc->IsGrabThreadRunning())
				{
					m_pDoc->UpdateHistogramWindow();
				}
				break;
			case SLOW_TIMER:
				if (m_pDoc != NULL )
				{
					if (m_pDoc->IsGrabThreadRunning())
					{
						//
						// we're only updating the requested frame rate once
						// a second to cut down on the number of register reads.
						//
						m_requestedFPS = m_pDoc->GetRequestedFrameRate();
						m_pDoc->CheckCameraPower();
					}
					UpdateEventsStatus();
				}
				break;
		}
	}
}

void CMainFrame::ToggleView()
{
	// Toggles window status
	m_isFullScreen = (!m_isFullScreen);
	CFlyCap2_MFCView* pView = (CFlyCap2_MFCView*)GetActiveView();
	if (m_isFullScreen == false)
	{
		// Toggles from full screen to normal mode
		// Shows status bar and tool bar if they were visible
		if (m_prevIsStatusBarVisible)
		{
			m_wndStatusBar.ShowWindow(SW_SHOW);
		}

		if (m_prevIsToolBarVisible)
		{
			m_wndToolBar.ShowWindow(SW_SHOW);
		}

		RecalcLayout();
		// Shows window in normal mode
		MoveWindow(m_normalRect);
		pView->SetToWindowedMode();

		//disable top most mode
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else
	{	// Toggles from normal to full screen mode
		// Saves status bar and toolbar status and hides them
		if (m_prevIsStatusBarVisible = m_wndStatusBar.IsWindowVisible() == TRUE)
		{
			m_wndStatusBar.ShowWindow(SW_HIDE);
		}

		if (m_prevIsToolBarVisible = m_wndToolBar.IsWindowVisible() == TRUE)
		{
			m_wndToolBar.ShowWindow(SW_HIDE);
		}
		RecalcLayout();
		// Saves current window position and size
		GetWindowRect(m_normalRect);

		// Shows window in full screen
		MoveWindow(m_fullRect);
		pView->SetToFullScreenMode();

		//Set window to top most
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	// Resets position and maximum window size for full screen mode
	if(this->m_isFullScreen == TRUE){
		lpMMI->ptMaxPosition = m_fullRect.TopLeft();
		lpMMI->ptMaxTrackSize = lpMMI->ptMaxSize = CPoint(m_fullRect.Size());
	}
	else
	{
		lpMMI->ptMinTrackSize.x = 800;
		lpMMI->ptMinTrackSize.y = 600;
	}

	CFrameWnd::OnGetMinMaxInfo(lpMMI);

}
void CMainFrame::OnViewFullscreen()
{
	ToggleView();
}

void CMainFrame::OnAppAbout()
{
	m_aboutDlg.ShowWindow(SW_SHOW);
}

void CMainFrame::OnLaunchHelp()
{
#if defined(_WIN32) || defined(_WIN64)
	std::string helpFilePath = GetHelpFilePath();
	if (_access (helpFilePath.c_str(), 0) == 0)
	{
		//if the window is in full screen mode
		//the help file will be hiden behind window
		//so we need to disable top most to show help file
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShellExecute(NULL,"open",helpFilePath.c_str(),NULL,NULL,SW_SHOW);
	}
	else
	{
		CString secondaryTxt = "Unable to locate help file at ";
		secondaryTxt += helpFilePath.c_str();
		MessageBox(secondaryTxt,"Error locating help file",MB_OK);
	}

#else

	// All other platforms
	MessageBox("The function has not implemented yet. Sorry for the inconvenience.","Error",MB_OK);
#endif
}



BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// For some reason, we must force send "mouse wheel message" to
	// view object, otherwise mouse wheel won't control image size
	if (pMsg->message == WM_MOUSEWHEEL && (GetActiveWindow() == this))
	{
		CView *pView = GetActiveView();
		if (pView != NULL)
		{
			pView->SendMessage(
					WM_MOUSEWHEEL,
					pMsg->wParam,
					pMsg->lParam	);
			return TRUE;
		}
	}
	return CFrameWnd::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult )
{
	NMHDR* pNMHDR = (NMHDR*) lParam;

	//
	// This catches clicks to the status bar fields.
	//
	if(m_wndStatusBar &&
			m_pDoc != NULL &&
			pNMHDR->hwndFrom == m_wndStatusBar.m_hWnd &&
			pNMHDR->code == NM_CLICK )
	{
		NMMOUSE* pNMMOUSE = (NMMOUSE*) pNMHDR;
		POINT pt = pNMMOUSE->pt;

		CRect itemRect;
		m_wndStatusBar.GetItemRect( 0, &itemRect );
		if(pt.x > itemRect.left &&
				pt.x < itemRect.right &&
				pt.y > itemRect.top &&
				pt.y < itemRect.bottom )
		{
			m_pDoc->ToggleEventStatDialog();
			return TRUE;
		}
	}
	return CFrameWnd::OnNotify( wParam, lParam, pResult );
}

// Adding code to increase or decrease main window
// to properly show or hide status bar
void CMainFrame::OnViewStatusBar()
{
	CControlBar* pBar = GetControlBar(AFX_IDW_STATUS_BAR);

	if (pBar != NULL)
	{
		RECT AppWinRect, BarRect;

		GetWindowRect(&AppWinRect);
		pBar->GetWindowRect(&BarRect);
		int iBarHeight = BarRect.bottom - BarRect.top;

		BOOL bShow = (pBar->GetStyle() & WS_VISIBLE) == 0;
		ShowControlBar(pBar, bShow, FALSE);

		// Changing rect size to trigger an repaint
		long recWidth = AppWinRect.right - AppWinRect.left;
		long rectHeight = AppWinRect.bottom - AppWinRect.top;
		SetWindowPos(&CWnd::wndNoTopMost, AppWinRect.top, AppWinRect.left, recWidth, rectHeight + 1, SWP_NOMOVE);
		SetWindowPos(&CWnd::wndNoTopMost, AppWinRect.top, AppWinRect.left, recWidth, rectHeight - 1, SWP_NOMOVE);
	}
}
