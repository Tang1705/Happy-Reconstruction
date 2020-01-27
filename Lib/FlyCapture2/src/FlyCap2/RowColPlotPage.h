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
#include "Resource.h"
#pragma once#include "afxwin.h"



// RowColPlotPage dialog

class RowColPlotPage : public CDialog
{
	DECLARE_DYNAMIC(RowColPlotPage)

	public:
		RowColPlotPage(CWnd* pParent = NULL);   // standard constructor
		virtual ~RowColPlotPage();


		void CalculateRowColStats(
				FlyCapture2::Image* pImage,
				Histogram::RowColStats* pStats );
		void EnableColorChannelCheckBoxes();
		void DisableColorChannelCheckBoxes();

		// Dialog Data
		enum { IDD = IDD_TABPAGE_ROWCOLPLOT };

	protected:
		// Row col stats
		Histogram::RowColStats m_rowColStats;

		// Row col display options
		Histogram::RowColDisplayOptions m_dispOptions;

		// Row col function options
		Histogram::RowColFunctionOptions m_funcOptions;

		Histogram::RowColMode m_rowColMode;

		static void ResizeRowColChannelStats(
				Histogram::RowColChannelStats* pStats,
				unsigned int newSize );

		static void ClearRowColChannelStats(
				Histogram::RowColChannelStats* pStats );

		void CalculateRowColStatsMono(
				FlyCapture2::Image* pImage,
				Histogram::RowColStats* pStats );

		void CalculateRowColStatsMonoColumn(
				FlyCapture2::Image* pImage,
				Histogram::RowColStats* pStats );

		void CalculateRowColStatsMonoRow(
				FlyCapture2::Image* pImage,
				Histogram::RowColStats* pStats );

		void CalculateRowColStatsColor(
				FlyCapture2::Image* pImage,
				Histogram::RowColStats* pStats );

		void CalculateRowColStatsColorColumn(
				FlyCapture2::Image* pImage,
				Histogram::RowColStats* pStats );

		void CalculateRowColStatsColorRow(
				FlyCapture2::Image* pImage,
				Histogram::RowColStats* pStats );

		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			BOOL m_showGrey;
		BOOL m_showRed;
		BOOL m_showGreen;
		BOOL m_showBlue;
		BOOL m_showMax;
		BOOL m_showMean;
		BOOL m_showMin;
	public:
		afx_msg void OnBnClickedModeColumn();
		afx_msg void OnBnClickedModeRow();
		virtual BOOL OnInitDialog();
		afx_msg void OnControlCheckStateChanged();
};
