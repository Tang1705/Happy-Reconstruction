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
#pragma once
#define MAX_NUM_OF_PIXEL_VALUES 65536
class HistogramDrawingArea
{
	public:
		HistogramDrawingArea();
		~HistogramDrawingArea();
		void SetDrawingArea(CStatic* pStaticFrame);

		/**
		 * Update the drawing area for histogram mode.
		 */
		void Update(FlyCapture2::ImageStatistics* pStatistics,
				unsigned int maxVal,
				unsigned int* numOfFrames);

		/**
		 * Update the drawing area for row column mode.
		 */
		void Update(Histogram::RowColStats* pRowColStats);
	private:
		CStatic* m_pDrawingArea;
		CDC* m_pBufferDC;
		/** The draw mode, i.e. histogram or row/column. */
		Histogram::DrawMode m_drawMode;
		unsigned int* m_numOfFrames;
		static const float sk_horzScale;
		static const float sk_vertScale;
		FlyCapture2::ImageStatistics* m_pHistogramStats;
		unsigned int m_maxVal;
		float m_averageHistogram[FlyCapture2::ImageStatistics::NUM_STATISTICS_CHANNELS][MAX_NUM_OF_PIXEL_VALUES];
		Histogram::RowColStats* m_pRowColStats;

		void Draw();
		void DrawBackgroundGrid(LPCRECT lpRect);
		void DrawHistogramGridLabels(LPCRECT lpRect);
		void DrawRowColGridLabels(LPCRECT lpRect);

		//@}

		/** @name Histogram drawing functions.
		 *  These functions deal with drawing for the histogram mode.
		 */
		//@{

		void DrawSingleHistogramLine(
				LPCRECT lpRect,
				FlyCapture2::ImageStatistics::StatisticsChannel channel );

void DrawSingleRowColLine(
		LPCRECT lpRect,
		std::vector<unsigned int> vecData,
		unsigned int numValues,
		COLORREF color);

void DrawSingleRowColChannel(
		LPCRECT lpRect,
		Histogram::RowColChannelStats stats,
		unsigned int numValues,
		COLORREF lineColor);

void GetPaddedSize(
		LPCRECT lpRect,
		int& paddedLeft,
		int& paddedTop,
		int& paddedWidth,
		int& paddedHeight );

static int GetNumPixels(
		unsigned int numPixelValues,
		const int* pHistogram );

std::vector<float> GetPercentages(
		unsigned int numPixelValues,
		const int* pHistogram ,
		FlyCapture2::ImageStatistics::StatisticsChannel channel);

static COLORREF GetLineColor(FlyCapture2::ImageStatistics::StatisticsChannel channel);
};
