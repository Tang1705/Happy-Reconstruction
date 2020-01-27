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

#include "afxcmn.h"
#include "HistogramPage.h"
#include "RowColPlotPage.h"
#include "HistogramDrawingArea.h"
#pragma once
#include "afxwin.h"


// HistogramDialog dialog

class HistogramDialog : public CDialog
{
	DECLARE_DYNAMIC(HistogramDialog)

	public:
		HistogramDialog(CWnd* pParent = NULL);   // standard constructor
		virtual ~HistogramDialog();
		void SetImageForStatistics(FlyCapture2::Image image);
		void Update();
		// Dialog Data
		enum { IDD = IDD_DIALOG_HISTOGRAM };
		UINT DoUpdateStats();
		static UINT ThreadUpdateStats( void* pparam );
		HANDLE m_threadDoneEvent;
		HANDLE m_hRowColStatMutex;
		void StartUpdate();
		void StopUpdate();

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		virtual BOOL OnInitDialog();

		//HANDLE m_hStatsMutex;

		bool m_running;
		HANDLE m_imageReadyEvent;
		CCriticalSection m_stats_input_buffer;

		/**
		 * The overall draw mode.
		 */
		Histogram::DrawMode m_drawMode;

		Histogram::RowColMode m_rowColMode;

		FlyCapture2::Image m_image;
		CCriticalSection m_csUpdateData;
		Histogram::RowColStats* m_pRowColStats;
		Histogram::RowColStats* m_pRowColStatsBuffer;

		// Blank histogram states
		FlyCapture2::ImageStatistics m_blankStats;
		void EnableForPixelFormat( FlyCapture2::PixelFormat pixelFormat );
		void DisableAllHistogramChannel();

		DECLARE_MESSAGE_MAP()
			//HANDLE m_updateEvent;
			HistogramPage m_histogramPage;
		RowColPlotPage m_rowColPlotPage;
		HistogramDrawingArea m_drawingArea;
		CTabCtrl m_tabControl;
		FlyCapture2::PixelFormat m_prevPixelFormat;

		CWinThread* m_updateLoopThread;
		virtual void OnOK();
		CStatic m_drawingAreaStaticFrame;
	public:
		afx_msg void OnTcnSelchangeTabHistogram(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
		afx_msg void OnClose();
		afx_msg void OnPaint();
};
