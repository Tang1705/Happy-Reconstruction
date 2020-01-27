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
#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class HistogramPage : public CDialog
{
	DECLARE_DYNAMIC(HistogramPage)
	public:
		HistogramPage(CWnd* pParent = NULL);   // standard constructor
		virtual ~HistogramPage();
		HANDLE m_statsMutex;
		// Dialog Data
		enum { IDD = IDD_TABPAGE_HISTOGRAM };
		/*BOOL SetDataGridText(
		  FlyCapture2::ImageStatistics::StatisticsChannel channel,
		  Histogram::DataGridColumns dataType,
		  LPCTSTR text);*/
		//BOOL GetChannelCheckState(FlyCapture2::ImageStatistics::StatisticsChannel channel);
		//BOOL SetChannelCheckState(FlyCapture2::ImageStatistics::StatisticsChannel channel, BOOL bCheck);
		void EnableChannel( FlyCapture2::ImageStatistics::StatisticsChannel channel );
		void DisableChannel( FlyCapture2::ImageStatistics::StatisticsChannel channel );
		void UpdateHistogramStatToBuffer();
		bool SwapBuffer();
		FlyCapture2::ImageStatistics* GetImageStatistics();
		FlyCapture2::ImageStatistics* GetImageStatisticsBuffer();
		unsigned int GetHistogramMax();
		unsigned int* GetNumOfFrames();
		void UncheckAverage();
		void CleanCheckStatus();
		Histogram::BinningType GetBinningSelection();
		void SetBinningSelection(Histogram::BinningType type);
		void EnableBinningRadioButton(Histogram::BinningType type);
		void DisableBinningRadioButton(Histogram::BinningType type);
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		CListCtrl m_channelsTable;
		bool m_bChannelEnabled[FlyCapture2::ImageStatistics::NUM_STATISTICS_CHANNELS];
		bool m_bValueChanged[FlyCapture2::ImageStatistics::NUM_STATISTICS_CHANNELS];
		//the max percent shown in the histogram
		unsigned int m_histogramMax;

		//the check status of binning selection
		int m_binningSelection;

		// Histogram stats
		FlyCapture2::ImageStatistics* m_pHistogramStats;

		// Histogram stats
		FlyCapture2::ImageStatistics* m_pHistogramStatsBuffer;

		//previous statistics values (for average option use)
		float m_prevPixelValueMin[FlyCapture2::ImageStatistics::NUM_STATISTICS_CHANNELS];
		float m_prevPixelValueMax[FlyCapture2::ImageStatistics::NUM_STATISTICS_CHANNELS];
		float m_prevPixelValueMean[FlyCapture2::ImageStatistics::NUM_STATISTICS_CHANNELS];
		unsigned int m_numOfFrames[FlyCapture2::ImageStatistics::NUM_STATISTICS_CHANNELS];
		const char* GetChannelString( FlyCapture2::ImageStatistics::StatisticsChannel channel );
		void UpdateSingleChannel(FlyCapture2::ImageStatistics::StatisticsChannel channel);
		DECLARE_MESSAGE_MAP()

			virtual void OnOK();
		UINT m_maxPercentValue;
		CSpinButtonCtrl m_maxPercentSpinButton;
		CButton m_enableAverageCheckBox;

	public:
		virtual BOOL OnInitDialog();
		afx_msg void OnChannelCheckStateChanged(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnNMCustomdrawListChannel(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnEnChangePercentEdit();
		afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

};
