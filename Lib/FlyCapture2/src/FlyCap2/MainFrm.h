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

#include "AboutDialog.h"
#include "FlyCap2_MFCDoc.h"
#include "FlyCap2_MFCView.h"
#pragma once

class CMainFrame : public CFrameWnd
{
	private:
		static const int sk_defualtFastTimerDelay = 50;// in MS
		static const int sk_defualtSlowTimerDelay = 600;// in MS
		static const int sk_statusbarIconOffsetX = 5;
		static const int sk_statusbarIconOffsetY = 3;
	protected: // create from serialization only
		CMainFrame();
		DECLARE_DYNCREATE(CMainFrame)

			// Operations
	public:
			void UpdateStatusBar();
			void ToggleView();
			virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
			virtual BOOL PreTranslateMessage(MSG* pMsg);
			virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
			virtual ~CMainFrame();
#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
#endif

	protected:
			enum TimerID{ FAST_TIMER = 0, SLOW_TIMER};
			CStatusBar  m_wndStatusBar;
			CToolBar    m_wndToolBar;
			AboutDialog m_aboutDlg;
			bool m_WarningShown;
			CFlyCap2_MFCDoc* m_pDoc;
			CFlyCap2_MFCView* m_pView;
			CFont m_Font;
			CBitmap m_bitmapHelp;
			CBitmap m_bitmapAbout;
			CBitmap m_bitmapSaveAs;
			CBitmap m_bitmapExit;
			CBitmap m_bitmapControl;
			CBitmap m_bitmapEventStatusBad;
			CBitmap m_bitmapEventStatusOK;

			UINT_PTR m_fastTimer;
			UINT_PTR m_slowTimer;
			RECT m_rectStatus;
			RECT m_rectToolBar;


			CRect m_normalRect;
			CRect m_fullRect;
			bool m_isFullScreen;
			BOOL m_prevIsStatusBarVisible;
			BOOL m_prevIsToolBarVisible;

			double m_requestedFPS;
			CCriticalSection m_csOnTimer;

			//update status bar information functions
			void UpdateEventsStatus();
			void UpdateFrameRateInfoStatus();
			void UpdateCursorInfoStatus();
			void UpdateImageInfoStatus();
			// Generated message map functions
	protected:
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			DECLARE_MESSAGE_MAP()
	public:
				afx_msg void OnTimer(UINT_PTR idEvent);
				afx_msg void OnDestroy();
				afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
				afx_msg void OnViewFullscreen();
				afx_msg void OnAppAbout();
				afx_msg void OnLaunchHelp();

				afx_msg void OnViewStatusBar();
};


