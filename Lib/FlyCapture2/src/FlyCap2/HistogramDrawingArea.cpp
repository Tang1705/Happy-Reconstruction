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

#include "StdAfx.h"
#include "HistogramDrawingArea.h"

using namespace FlyCapture2;

const float HistogramDrawingArea::sk_horzScale = 0.9f;
const float HistogramDrawingArea::sk_vertScale = 0.8f;

HistogramDrawingArea::HistogramDrawingArea()
{
	m_pDrawingArea = NULL;
	m_pBufferDC = NULL;
	for (int i=0; i<ImageStatistics::NUM_STATISTICS_CHANNELS; i++)
	{
		for (int j=0; j<MAX_NUM_OF_PIXEL_VALUES; j++)
		{
			m_averageHistogram[i][j] = 0;
		}
	}
}

HistogramDrawingArea::~HistogramDrawingArea()
{
	if (m_pBufferDC !=NULL)
	{
		if (m_pBufferDC->DeleteDC()== FALSE)//delete DC
		{
			TRACE("Unable to delete buffer DC\n");
		}
		delete m_pBufferDC;
		m_pBufferDC = NULL;
	}
}
void HistogramDrawingArea::SetDrawingArea(CStatic* pStaticFrame)
{
	m_pDrawingArea = pStaticFrame;
}

void HistogramDrawingArea::Update(ImageStatistics* pStatistics, unsigned int maxVal,unsigned int* numOfFrames)
{
	m_pHistogramStats = pStatistics;
	m_maxVal = maxVal;
	m_numOfFrames = numOfFrames;
	m_drawMode = Histogram::MODE_HISTOGRAM;
	Draw();
}

void HistogramDrawingArea::Update(Histogram::RowColStats* pRowColStats )
{
	m_pRowColStats = pRowColStats;
	m_drawMode = Histogram::MODE_ROWCOL;
	Draw();
}

void HistogramDrawingArea::Draw()
{
	if (m_pDrawingArea == NULL)
	{
		return;
	}
	CRect rc;
	m_pDrawingArea->GetClientRect(&rc);
	CDC* pDrawingAreaDC = m_pDrawingArea->GetDC();
	if (m_pBufferDC !=NULL)
	{
		if (m_pBufferDC->DeleteDC()== FALSE)//delete DC
		{
			TRACE("Unable to delete buffer DC\n");
		}
		delete m_pBufferDC;
		m_pBufferDC = NULL;
	}
	m_pBufferDC = new CDC();
	//use double buffer to draw chart
	CBitmap bufferBitmap; //buffer image
	if (m_pBufferDC->CreateCompatibleDC(pDrawingAreaDC) == FALSE)
	{
		return;
	}
	if (bufferBitmap.CreateCompatibleBitmap(pDrawingAreaDC, rc.Width(), rc.Height()) == FALSE)
	{
		return;
	}
	CBitmap* oldBitmap = m_pBufferDC->SelectObject(&bufferBitmap);

	// Clear the background
	m_pBufferDC->FillSolidRect(&rc,(RGB(255,255,255)));

	if ( m_drawMode == Histogram::MODE_HISTOGRAM )
	{
		for ( int i=0; i < ImageStatistics::NUM_STATISTICS_CHANNELS; i++ )
		{
			DrawSingleHistogramLine(&rc,static_cast<ImageStatistics::StatisticsChannel>(i));
		}
		DrawHistogramGridLabels(&rc);
	}
	else if ( m_drawMode == Histogram::MODE_ROWCOL )
	{
		if (m_pRowColStats->options.displayOptions.showGrey == true)
		{
			DrawSingleRowColChannel(
					&rc,
					m_pRowColStats->grey,
					m_pRowColStats->numPixelValues,
					GetLineColor(ImageStatistics::GREY));
		}
		if (m_pRowColStats->options.displayOptions.showRed == true)
		{
			DrawSingleRowColChannel(
					&rc,
					m_pRowColStats->red,
					m_pRowColStats->numPixelValues,
					GetLineColor(ImageStatistics::RED));
		}
		if (m_pRowColStats->options.displayOptions.showBlue == true)
		{
			DrawSingleRowColChannel(
					&rc,
					m_pRowColStats->blue,
					m_pRowColStats->numPixelValues,
					GetLineColor(ImageStatistics::BLUE));
		}
		if (m_pRowColStats->options.displayOptions.showGreen == true)
		{
			DrawSingleRowColChannel(
					&rc,
					m_pRowColStats->green,
					m_pRowColStats->numPixelValues,
					GetLineColor(ImageStatistics::GREEN));
		}
		DrawRowColGridLabels(&rc);
	}
	DrawBackgroundGrid(&rc);

	//paint buffer to drawing area DC
	pDrawingAreaDC->BitBlt(0,0, rc.Width(), rc.Height(),m_pBufferDC,0,0,SRCCOPY);
	m_pBufferDC->SelectObject(oldBitmap);
	if (bufferBitmap.DeleteObject() == FALSE)
	{
		TRACE("Unable to delete buffer Bitmap\n");
	}
	if (m_pBufferDC->DeleteDC()== FALSE)//delete dc
	{
		TRACE("Unable to delete buffer DC\n");
	}
	if (m_pDrawingArea->ReleaseDC(pDrawingAreaDC) == 0)
	{
		TRACE("Unable to delete drawing area DC\n");
	}
	delete m_pBufferDC;
	m_pBufferDC = NULL;
}

void HistogramDrawingArea::DrawBackgroundGrid(LPCRECT lpRect)
{
	CDC* pDC = m_pBufferDC;

	// Reserve the outside 10%
	int paddedLeft, paddedTop, paddedWidth, paddedHeight;
	GetPaddedSize(lpRect, paddedLeft, paddedTop, paddedWidth, paddedHeight );

	// Draw a horizontal line across the bottom
	CPen blackPen(PS_SOLID, 2 , RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&blackPen);
	pDC->MoveTo( paddedLeft, paddedTop + paddedHeight );
	pDC->LineTo( paddedLeft + paddedWidth, paddedTop + paddedHeight );

	// Draw vertical an horizontal lines
	CPen greyPen(PS_SOLID, 1 , RGB(200,200,200));
	pDC->SelectObject(&greyPen);
	const int k_numPartitions = 8;
	for ( int i=1; i < k_numPartitions; i++ )
	{
		const float fraction = i / static_cast<float>(k_numPartitions);

		// Draw vertical lines
		int xOffset = static_cast<int>(paddedLeft + (paddedWidth * fraction));
		pDC->MoveTo( xOffset, paddedTop );
		pDC->LineTo( xOffset, paddedTop + paddedHeight );

		int yOffset = 0;

		if ( m_drawMode == Histogram::MODE_HISTOGRAM )
		{
			if ( i % 2 != 0 )
			{
				continue;
			}

			float scaleRatio = 100 / static_cast<float>(m_maxVal);
			yOffset = static_cast<int>(paddedTop + paddedHeight - (paddedHeight * fraction * scaleRatio));
		}
		else if ( m_drawMode == Histogram::MODE_ROWCOL )
		{
			yOffset = static_cast<int>(paddedTop + paddedHeight - (paddedHeight * fraction));
		}

		//Draw horizontal lines
		if ( yOffset > paddedTop )
		{
			pDC->MoveTo( paddedLeft, yOffset );
			pDC->LineTo( paddedLeft + paddedWidth, yOffset );
		}
	}
	pDC->SelectObject(pOldPen);
	blackPen.DeleteObject();
	greyPen.DeleteObject();
}

void HistogramDrawingArea::DrawHistogramGridLabels(LPCRECT lpRect)
{
	CDC* pDC = m_pBufferDC;
	CFont newFont, *pOldFont;
	//set text font
	newFont.CreatePointFont(80, "Arial", pDC);
	pOldFont = pDC->SelectObject(&newFont);
	// Reserve the outside 10%
	int paddedLeft, paddedTop, paddedWidth, paddedHeight;
	GetPaddedSize(lpRect ,paddedLeft, paddedTop, paddedWidth, paddedHeight );
	const int k_numPartitions = 8;
	// Render the x-axis labels
	for ( int i=0; i <= k_numPartitions; i++ )
	{
		const float fraction = i / static_cast<float>(k_numPartitions);

		unsigned int maxNumPixelValues = 0;

		for ( int j=0; j < ImageStatistics::NUM_STATISTICS_CHANNELS; j++ )
		{
			unsigned int numPixelValues = 0;

			m_pHistogramStats->GetNumPixelValues(
					static_cast<ImageStatistics::StatisticsChannel>(j),
					&numPixelValues );

			maxNumPixelValues = max( numPixelValues, maxNumPixelValues );
		}

		float pixelValue;
		if ( maxNumPixelValues == 0 )
		{
			pixelValue = 256 * fraction;
		}
		else
		{
			pixelValue = maxNumPixelValues * fraction;
		}

		CString caption;
		caption.Format("%.0f",pixelValue);

		const float xOffset = paddedLeft + (paddedWidth * fraction);
		const float yOffset = paddedTop + paddedHeight + (paddedTop / 2.0f);
		CSize textExtents = pDC->GetTextExtent(caption);
		RECT textRect;
		textRect.left =  static_cast<LONG>(xOffset - (textExtents.cx / 2));
		textRect.right = textRect.left + textExtents.cx;
		textRect.top = static_cast<LONG>(yOffset - (textExtents.cy / 2));
		textRect.bottom = textRect.top + textExtents.cy;
		pDC->DrawText(caption, &textRect, DT_VCENTER |DT_CENTER |DT_SINGLELINE);
	}
	// Render the y-axis labels
	for ( int i=1; i < k_numPartitions; i++ )
	{
		if ( i % 2 != 0 )
		{
			continue;
		}

		const float fraction = i / static_cast<float>(k_numPartitions);
		float scaleRatio = 100 / static_cast<float>(m_maxVal);
		int yOffset = static_cast<int>(paddedTop + paddedHeight - (paddedHeight * fraction * scaleRatio));

		CString caption;
		caption.Format("%u%%",(i*100)/k_numPartitions );

		if ( yOffset > paddedTop )
		{
			CSize textExtents = pDC->GetTextExtent(caption);
			RECT textRect;
			textRect.left =  static_cast<LONG>((paddedLeft / 2) - (textExtents.cx / 2));
			textRect.right = textRect.left + textExtents.cx;
			textRect.top = static_cast<LONG>(yOffset + (textExtents.cy / 2));
			textRect.bottom = textRect.top - textExtents.cy;
			pDC->DrawText(caption,&textRect,DT_VCENTER |DT_CENTER |DT_SINGLELINE);
		}
	}
	pDC->SelectObject(pOldFont);
	if (newFont.DeleteObject() == FALSE)//delete font
	{
		TRACE("Unable to delete font\n");
	}
}
void HistogramDrawingArea::DrawRowColGridLabels(LPCRECT lpRect)
{
	CDC* pDC = m_pBufferDC;
	CFont newFont, *pOldFont;
	//set text font
	newFont.CreatePointFont(80, "Arial", pDC);
	pOldFont = pDC->SelectObject(&newFont);
	// Reserve the outside 10%
	int paddedLeft, paddedTop, paddedWidth, paddedHeight;
	GetPaddedSize(lpRect, paddedLeft, paddedTop, paddedWidth, paddedHeight );
	const int k_numPartitions = 8;
	for ( int i=0; i <= k_numPartitions; i++ )
	{
		const float fraction = i / static_cast<float>(k_numPartitions);
		float dimensionValue = m_pRowColStats->imageDimension * fraction;

		CString caption;
		caption.Format("%.0f",dimensionValue );

		const float xOffset = paddedLeft + (paddedWidth * fraction);
		const float yOffset = paddedTop + paddedHeight + (paddedTop/2.0f);

		CSize textExtents = pDC->GetTextExtent(caption);
		RECT textRect;
		textRect.left =  static_cast<LONG>(xOffset - (textExtents.cx / 2));
		textRect.right = textRect.left + textExtents.cx;
		textRect.top = static_cast<LONG>(yOffset - (textExtents.cy / 2));
		textRect.bottom = textRect.top + textExtents.cy;
		pDC->DrawText(caption, &textRect, DT_VCENTER |DT_CENTER |DT_SINGLELINE);
	}

	for ( int i=1; i <= k_numPartitions; i++ )
	{
		const float fraction = i / static_cast<float>(k_numPartitions);
		float pixelValue = m_pRowColStats->numPixelValues * fraction;

		CString caption;
		caption.Format("%.0f",pixelValue );

		float yOffset = paddedTop + paddedHeight - (paddedHeight * fraction);
		CSize textExtents = pDC->GetTextExtent(caption);
		RECT textRect;
		textRect.left =  static_cast<LONG>((paddedLeft/2) - (textExtents.cx / 2));
		textRect.right = textRect.left + textExtents.cx;
		textRect.top = static_cast<LONG>(yOffset - (textExtents.cy / 2));
		textRect.bottom = textRect.top + textExtents.cy;
		pDC->DrawText(caption, &textRect, DT_VCENTER |DT_CENTER |DT_SINGLELINE);
	}
	pDC->SelectObject(pOldFont);
	if (newFont.DeleteObject() == FALSE)//delete font
	{
		TRACE("Unable to delete font\n");
	}
}

void HistogramDrawingArea::GetPaddedSize(
		LPCRECT lpRect,
		int& paddedLeft,
		int& paddedTop,
		int& paddedWidth,
		int& paddedHeight )
{
	// Get width / height of widget
	int width = abs(lpRect->right - lpRect->left);
	int height = abs(lpRect->top - lpRect->bottom);

	// Reserve the outside 10%
	paddedLeft = static_cast<int>(width * ((1-sk_horzScale)/2));
	paddedTop = static_cast<int>(height * ((1-sk_vertScale)/2));
	paddedWidth = static_cast<int>(width * sk_horzScale);
	paddedHeight = static_cast<int>(height * sk_vertScale);
}

void HistogramDrawingArea::DrawSingleHistogramLine(LPCRECT lpRect,ImageStatistics::StatisticsChannel channel )
{
	CDC* pDC = m_pBufferDC;
	unsigned int rangeMin, rangeMax, pixelValueMin, pixelValueMax;
	unsigned int numPixelValues;
	float pixelValueMean;
	int* pHistogram;
	m_pHistogramStats->GetStatistics(
			channel,
			&rangeMin,
			&rangeMax,
			&pixelValueMin,
			&pixelValueMax,
			&numPixelValues,
			&pixelValueMean,
			&pHistogram );

	if (numPixelValues == 0)
	{
		return;
	}
	std::vector<float> percentages = GetPercentages( numPixelValues, pHistogram, channel);

	// Reserve the outside 10%
	int paddedLeft, paddedTop, paddedWidth, paddedHeight;
	GetPaddedSize(lpRect, paddedLeft, paddedTop, paddedWidth, paddedHeight );

	const float xScale = static_cast<float>(paddedWidth) / numPixelValues;
	const float yScale = paddedHeight / static_cast<float>(m_maxVal);

	// Set draw color
	COLORREF lineColor = GetLineColor(channel);
	CPen pen(PS_SOLID,1,lineColor);
	CPen* pOldPen = m_pBufferDC->SelectObject(&pen);
	if ( numPixelValues > 256 )
	{
		const int k_pixelsToAvg = static_cast<int>(numPixelValues / paddedWidth);

		for ( unsigned int i=0; i < numPixelValues; i += k_pixelsToAvg )
		{
			float maxVal = 0.0;
			for ( int j=0; j < k_pixelsToAvg; j++ )
			{
				if ( i+j >= numPixelValues )
				{
					break;
				}

				if ( percentages[i+j] > maxVal )
				{
					maxVal = percentages[i+j];
				}
			}

			// Calculate the scaled height of the current percentage
			float yScaledHeight = yScale * maxVal;

			if ( i == 0 )
			{
				m_pBufferDC->MoveTo(
						paddedLeft,
						static_cast<int>(paddedTop + paddedHeight - yScaledHeight) );
			}

			m_pBufferDC->LineTo(
					static_cast<int>(paddedLeft + (xScale * i)),
					static_cast<int>(paddedTop + paddedHeight - yScaledHeight) );
		}
	}
	else
	{
		for ( unsigned int i=0; i < numPixelValues; i++ )
		{
			// Calculate the scaled height of the current percentage
			float yScaledHeight = yScale * percentages[i];

			if ( i == 0 )
			{
				m_pBufferDC->MoveTo(
						paddedLeft,
						static_cast<int>(paddedTop + paddedHeight - yScaledHeight) );
			}

			m_pBufferDC->LineTo(
					static_cast<int>(paddedLeft + (xScale * i)),
					static_cast<int>(paddedTop + paddedHeight - yScaledHeight) );
		}
	}
	m_pBufferDC->SelectObject(pOldPen);
}

std::vector<float> HistogramDrawingArea::GetPercentages(
		unsigned int numPixelValues,
		const int* pHistogram ,
		ImageStatistics::StatisticsChannel channel)
{
	int numPixels = GetNumPixels( numPixelValues, pHistogram );

	std::vector<float> percentages;
	percentages.assign( MAX_NUM_OF_PIXEL_VALUES, 0 );

	if ( numPixels == 0 )
	{
		return percentages;
	}

	for ( unsigned int i=0; i < numPixelValues; i++ )
	{
		int currentFrameNumber = m_numOfFrames[channel];
		m_averageHistogram[channel][i] = ((m_averageHistogram[channel][i] * currentFrameNumber) + pHistogram[i] )/(currentFrameNumber+1);
		float currPercentage = (m_averageHistogram[channel][i] * 100)/ static_cast<float>(numPixels);
		percentages[i] = currPercentage;
	}
	m_numOfFrames[channel]++;
	return percentages;
}
void HistogramDrawingArea::DrawSingleRowColChannel(
		LPCRECT lpRect,
		Histogram::RowColChannelStats stats,
		unsigned int numValues,
		COLORREF lineColor)
{
	if (m_pRowColStats->options.functionOptions.showMax== true )
	{
		DrawSingleRowColLine( lpRect, stats.vecMax, numValues, lineColor );
	}
	if (m_pRowColStats->options.functionOptions.showMean== true )
	{
		DrawSingleRowColLine( lpRect, stats.vecMean, numValues, lineColor );
	}
	if (m_pRowColStats->options.functionOptions.showMin== true )
	{
		DrawSingleRowColLine( lpRect, stats.vecMin, numValues, lineColor );
	}
}
void HistogramDrawingArea::DrawSingleRowColLine(
		LPCRECT lpRect,
		std::vector<unsigned int> vecData,
		unsigned int numValues,
		COLORREF lineColor)
{
	// Reserve the outside 10%
	int paddedLeft, paddedTop, paddedWidth, paddedHeight;
	GetPaddedSize(lpRect, paddedLeft, paddedTop, paddedWidth, paddedHeight );
	const float xScale = paddedWidth / static_cast<float>(vecData.size());
	const float yScale = paddedHeight / static_cast<float>(numValues);
	// Set draw color
	CPen pen(PS_SOLID,1,lineColor);
	CPen* pOldPen = m_pBufferDC->SelectObject(&pen);
	int k_pixelsToAvg = static_cast<int>( vecData.size() / paddedWidth);
	if ( k_pixelsToAvg == 0 )
	{
		k_pixelsToAvg = 1;
	}
	const unsigned int dataSize = static_cast<unsigned int>(vecData.size());

	for ( unsigned int i=0; i < dataSize; i++ )
	{
		unsigned int maxVal = 0;
		for ( int j=0; j < k_pixelsToAvg; j++ )
		{
			if ( i+j >= dataSize )
			{
				break;
			}

			if ( vecData[i+j] > maxVal )
			{
				maxVal = vecData[i+j];
			}
		}

		// Calculate the scaled height of the current percentage
		float yScaledHeight = yScale * maxVal;

		if ( i == 0 )
		{
			m_pBufferDC->MoveTo(
					paddedLeft,
					static_cast<int>(paddedTop + paddedHeight - yScaledHeight) );
		}

		m_pBufferDC->LineTo(
				static_cast<int>(paddedLeft + (xScale * i)),
				static_cast<int>(paddedTop + paddedHeight - yScaledHeight) );
	}
	m_pBufferDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

COLORREF HistogramDrawingArea::GetLineColor(ImageStatistics::StatisticsChannel channel)
{
	int red,green,blue;

	switch (channel)
	{
		case ImageStatistics::GREY:
			red = 128;
			green = 128;
			blue = 128;
			break;

		case ImageStatistics::RED:
			red = 255;
			green = 0;
			blue = 0;
			break;

		case ImageStatistics::GREEN:
			red = 0;
			green = 255;
			blue = 0;
			break;

		case ImageStatistics::BLUE:
			red = 0;
			green = 0;
			blue = 255;
			break;

		case ImageStatistics::HUE:
			red = 255;
			green = 150;
			blue = 0;
			break;

		case ImageStatistics::SATURATION:
			red = 0;
			green = 255;
			blue = 255;
			break;

		case ImageStatistics::LIGHTNESS:
			red = 255;
			green = 0;
			blue = 255;
			break;

		default:
			red = 0;
			green = 0;
			blue = 0;
	}

	return RGB(red,green,blue);
}
int HistogramDrawingArea::GetNumPixels(
		unsigned int numPixelValues,
		const int* pHistogram )
{
	int numPixels = 0;

	for ( unsigned int i=0; i < numPixelValues; i++ )
	{
		numPixels += pHistogram[i];
	}

	return numPixels;
}
