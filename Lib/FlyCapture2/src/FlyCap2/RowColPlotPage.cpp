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
#include "RowColPlotPage.h"

using namespace FlyCapture2;
using namespace Histogram;
// RowColPlotPage dialog

IMPLEMENT_DYNAMIC(RowColPlotPage, CDialog)

	RowColPlotPage::RowColPlotPage(CWnd* pParent /*=NULL*/)
	: CDialog(RowColPlotPage::IDD, pParent)
	, m_showGrey(FALSE)
	, m_showRed(FALSE)
	, m_showGreen(FALSE)
	, m_showBlue(FALSE)
	, m_showMax(FALSE)
	, m_showMean(FALSE)
	  , m_showMin(FALSE)
{

}

RowColPlotPage::~RowColPlotPage()
{
}

void RowColPlotPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_DISPLAY_GREY, m_showGrey);
	DDX_Check(pDX, IDC_DISPLAY_RED, m_showRed);
	DDX_Check(pDX, IDC_DISPLAY_GREEN, m_showGreen);
	DDX_Check(pDX, IDC_DISPLAY_BLUE, m_showBlue);
	DDX_Check(pDX, IDC_FUNCTION_MAX, m_showMax);
	DDX_Check(pDX, IDC_FUNCTION_MEAN, m_showMean);
	DDX_Check(pDX, IDC_FUNCTION_MIN, m_showMin);
}


void RowColPlotPage::ResizeRowColChannelStats(
		Histogram::RowColChannelStats* pStats,
		unsigned int newSize )
{
	if ( pStats->vecMax.size() != newSize )
	{
		pStats->vecMax.resize( newSize, 0 );
	}

	if ( pStats->vecMean.size() != newSize )
	{
		pStats->vecMean.resize( newSize, 0 );
	}

	if ( pStats->vecMin.size() != newSize )
	{
		pStats->vecMin.resize( newSize, 0 );
	}
}

void RowColPlotPage::ClearRowColChannelStats(
		Histogram::RowColChannelStats* pStats )
{
	if ( pStats->vecMax.size() != 0 )
	{
		pStats->vecMax.clear();
	}

	if ( pStats->vecMean.size() != 0 )
	{
		pStats->vecMean.clear();
	}

	if ( pStats->vecMin.size() != 0 )
	{
		pStats->vecMin.clear();
	}
}


void RowColPlotPage::CalculateRowColStats(Image* pImage, RowColStats* pStats )
{
	if ( pImage == NULL || pStats == NULL )
	{
		return;
	}
	pStats->options.mode = m_rowColMode;
	pStats->options.displayOptions.showGrey = ConvertToBoolean(m_showGrey);

	pStats->options.functionOptions.showMax = ConvertToBoolean(m_showMax);
	pStats->options.functionOptions.showMean = ConvertToBoolean(m_showMean);
	pStats->options.functionOptions.showMin = ConvertToBoolean(m_showMin);

	if ( m_showGrey  == FALSE &&
			m_showRed   == FALSE &&
			m_showGreen == FALSE &&
			m_showBlue  == FALSE  )
	{
		pStats->options.displayOptions.showRed = false;
		pStats->options.displayOptions.showGreen = false;
		pStats->options.displayOptions.showBlue = false;
		return;
	}
	PixelFormat pixelFormat = pImage->GetPixelFormat();

	unsigned int imageWidth, imageHeight;
	pImage->GetDimensions( &imageHeight, &imageWidth );

	if ( m_rowColMode == ROWCOL_COLUMN )
	{
		pStats->imageDimension = imageWidth;
	}
	else if ( m_rowColMode == ROWCOL_ROW )
	{
		pStats->imageDimension = imageHeight;
	}

	switch (pixelFormat)
	{
		case PIXEL_FORMAT_MONO8:
		case PIXEL_FORMAT_MONO16:
			CalculateRowColStatsMono( pImage, pStats );
			pStats->options.displayOptions.showRed = false;
			pStats->options.displayOptions.showGreen = false;
			pStats->options.displayOptions.showBlue = false;
			break;

		case PIXEL_FORMAT_BGR:
		case PIXEL_FORMAT_RGB:
		case PIXEL_FORMAT_BGRU:
		case PIXEL_FORMAT_RGBU:
			CalculateRowColStatsColor( pImage, pStats );
			pStats->options.displayOptions.showRed = ConvertToBoolean(m_showRed);
			pStats->options.displayOptions.showGreen = ConvertToBoolean(m_showGreen);
			pStats->options.displayOptions.showBlue = ConvertToBoolean(m_showBlue);
			break;

		default:
			break;
	}
}

void RowColPlotPage::CalculateRowColStatsMono(Image* pImage,RowColStats* pStats )
{
	PixelFormat pixelFormat = pImage->GetPixelFormat();
	switch (pixelFormat)
	{
		case PIXEL_FORMAT_MONO8:
			pStats->numPixelValues = 256;
			break;
		case PIXEL_FORMAT_MONO16:
			pStats->numPixelValues = 65536;
			break;
		default:
			break;
	}

	if ( m_rowColMode == Histogram::ROWCOL_COLUMN )
	{
		CalculateRowColStatsMonoColumn( pImage, pStats );
	}
	else if ( m_rowColMode == Histogram::ROWCOL_ROW )
	{
		CalculateRowColStatsMonoRow( pImage, pStats );
	}
}

void RowColPlotPage::CalculateRowColStatsMonoColumn( Image* pImage, RowColStats* pStats )
{
	unsigned int rows, cols, stride;
	pImage->GetDimensions( &rows, &cols, &stride );

	PixelFormat pixelFormat = pImage->GetPixelFormat();

	ClearRowColChannelStats( &pStats->red );
	ClearRowColChannelStats( &pStats->green );
	ClearRowColChannelStats( &pStats->blue );

	unsigned char* pData = pImage->GetData();

	ResizeRowColChannelStats( &pStats->grey, cols );
	std::vector<unsigned int> vecMeanTotal( cols );

	for ( unsigned int x=0; x < cols; x++ )
	{
		unsigned int minVal = 0;
		unsigned int maxVal = 0;
		unsigned int accumVal = 0;

		for ( unsigned int y=0; y < rows; y++ )
		{
			unsigned int currPixVal = 0;

			if ( pixelFormat == PIXEL_FORMAT_MONO8 )
			{
				currPixVal = pData[(y*stride) + x];
			}
			else if ( pixelFormat == PIXEL_FORMAT_MONO16 )
			{
				currPixVal = pData[ y*stride + 2*x + 1 ];
				currPixVal = currPixVal << 8;
				currPixVal |= pData[ y*stride + 2*x ];
			}

			if ( y == 0 )
			{
				minVal = maxVal = currPixVal;
			}

			accumVal += currPixVal;

			if ( minVal > currPixVal )
			{
				minVal = currPixVal;
			}
			else if ( maxVal < currPixVal )
			{
				maxVal = currPixVal;
			}

			pStats->grey.vecMax[x] = maxVal;
			pStats->grey.vecMin[x] = minVal;
			pStats->grey.vecMean[x] = accumVal / rows;


		}
	}
}

void RowColPlotPage::CalculateRowColStatsMonoRow(Image* pImage,RowColStats* pStats )
{
	unsigned int rows, cols, stride;
	pImage->GetDimensions( &rows, &cols, &stride );

	PixelFormat pixelFormat = pImage->GetPixelFormat();

	ClearRowColChannelStats( &pStats->red );
	ClearRowColChannelStats( &pStats->green );
	ClearRowColChannelStats( &pStats->blue );

	unsigned char* pData = pImage->GetData();

	ResizeRowColChannelStats( &pStats->grey, rows );
	std::vector<unsigned int> vecMeanTotal( rows );

	for ( unsigned int y=0; y < rows; y++ )
	{
		unsigned int minVal = 0;
		unsigned int maxVal = 0;
		unsigned int accumVal = 0;

		for ( unsigned int x=0; x < cols; x++ )
		{
			unsigned int currPixVal = 0;

			if ( pixelFormat == PIXEL_FORMAT_MONO8 )
			{
				currPixVal = pData[(y*stride) + x];
			}
			else if ( pixelFormat == PIXEL_FORMAT_MONO16 )
			{
				currPixVal = pData[ y*stride + 2*x + 1 ];
				currPixVal = currPixVal << 8;
				currPixVal |= pData[ y*stride + 2*x ];
			}

			if ( x == 0 )
			{
				minVal = maxVal = currPixVal;
			}

			accumVal += currPixVal;

			if ( minVal > currPixVal )
			{
				minVal = currPixVal;
			}
			else if ( maxVal < currPixVal )
			{
				maxVal = currPixVal;
			}

			pStats->grey.vecMax[y] = maxVal;
			pStats->grey.vecMin[y] = minVal;
			pStats->grey.vecMean[y] = accumVal / cols;
		}
	}
}

void RowColPlotPage::CalculateRowColStatsColor(Image* pImage, RowColStats* pStats )
{
	pStats->numPixelValues = 256;

	if ( m_rowColMode == Histogram::ROWCOL_COLUMN )
	{
		CalculateRowColStatsColorColumn( pImage, pStats );
	}
	else if ( m_rowColMode == Histogram::ROWCOL_ROW )
	{
		CalculateRowColStatsColorRow( pImage, pStats );
	}
}

void RowColPlotPage::CalculateRowColStatsColorColumn(Image* pImage,RowColStats* pStats )
{
	unsigned int rows, cols, stride;
	pImage->GetDimensions( &rows, &cols, &stride );

	unsigned int bytesPerPixel = pImage->GetBitsPerPixel() / 8;

	PixelFormat pixelFormat = pImage->GetPixelFormat();

	ResizeRowColChannelStats( &pStats->grey, cols );
	ResizeRowColChannelStats( &pStats->red, cols );
	ResizeRowColChannelStats( &pStats->green, cols );
	ResizeRowColChannelStats( &pStats->blue, cols );

	unsigned char* pData = pImage->GetData();

	// For the vectors below, assume the order they are in as:
	// 0 - Grey
	// 1 - Red
	// 2 - Green
	// 3 - Blue
	for ( unsigned int x=0; x < cols; x++ )
	{
		std::vector<unsigned int> minVal(4, 0);
		std::vector<unsigned int> maxVal(4, 0);
		std::vector<unsigned int> accumVal(4, 0);

		for ( unsigned int y=0; y < rows; y++ )
		{
			std::vector<unsigned int> currPixVal(4, 0);

			unsigned char* pCurrent = pData + (y*stride) + (bytesPerPixel*x);

			switch( pixelFormat )
			{
				case PIXEL_FORMAT_BGR:
				case PIXEL_FORMAT_BGRU:
					currPixVal[3] = *pCurrent++;
					currPixVal[2] = *pCurrent++;
					currPixVal[1] = *pCurrent;
					break;

				case PIXEL_FORMAT_RGB:
				case PIXEL_FORMAT_RGBU:
					currPixVal[1] = *pCurrent++;
					currPixVal[2] = *pCurrent++;
					currPixVal[3] = *pCurrent;
					break;
				default:
					currPixVal[1] = currPixVal[2] = currPixVal[3] = 0;
			}

			// Calculate the grey value
			currPixVal[0] = ( currPixVal[3] + 6*currPixVal[2] + 3*currPixVal[1] ) / 10;

			if ( y == 0 )
			{
				for ( unsigned int i=0; i < minVal.size(); i++ )
				{
					minVal[i] = maxVal[i] = currPixVal[i];
				}
			}

			for ( unsigned int i=0; i < minVal.size(); i++ )
			{
				accumVal[i] += currPixVal[i];

				if ( minVal[i] > currPixVal[i] )
				{
					minVal[i] = currPixVal[i];
				}
				else if ( maxVal[i] < currPixVal[i] )
				{
					maxVal[i] = currPixVal[i];
				}
			}

			pStats->grey.vecMax[x] = maxVal[0];
			pStats->grey.vecMin[x] = minVal[0];
			pStats->grey.vecMean[x] = accumVal[0] / rows;

			pStats->red.vecMax[x] = maxVal[1];
			pStats->red.vecMin[x] = minVal[1];
			pStats->red.vecMean[x] = accumVal[1] / rows;

			pStats->green.vecMax[x] = maxVal[2];
			pStats->green.vecMin[x] = minVal[2];
			pStats->green.vecMean[x] = accumVal[2] / rows;

			pStats->blue.vecMax[x] = maxVal[3];
			pStats->blue.vecMin[x] = minVal[3];
			pStats->blue.vecMean[x] = accumVal[3] / rows;

		}
	}
}

void RowColPlotPage::CalculateRowColStatsColorRow(Image* pImage, RowColStats* pStats )
{
	unsigned int rows, cols, stride;
	pImage->GetDimensions( &rows, &cols, &stride );

	unsigned int bytesPerPixel = pImage->GetBitsPerPixel() / 8;

	PixelFormat pixelFormat = pImage->GetPixelFormat();

	pStats->numPixelValues = 256;

	ResizeRowColChannelStats( &pStats->grey, rows );
	ResizeRowColChannelStats( &pStats->red, rows );
	ResizeRowColChannelStats( &pStats->green, rows );
	ResizeRowColChannelStats( &pStats->blue, rows );

	std::vector<unsigned int> vecGreyMeanTotal( rows );
	std::vector<unsigned int> vecRedMeanTotal( rows );
	std::vector<unsigned int> vecGreenMeanTotal( rows );
	std::vector<unsigned int> vecBlueMeanTotal( rows );

	unsigned char* pData = pImage->GetData();

	// For the vectors below, assume the order they are in as:
	// 0 - Grey
	// 1 - Red
	// 2 - Green
	// 3 - Blue
	for ( unsigned int y=0; y < rows; y++ )
	{
		std::vector<unsigned int> minVal(4, 0);
		std::vector<unsigned int> maxVal(4, 0);
		std::vector<unsigned int> accumVal(4, 0);

		for ( unsigned int x=0; x < cols; x++ )
		{
			std::vector<unsigned int> currPixVal(4, 0);

			unsigned char* pCurrent = pData + (y*stride) + (bytesPerPixel*x);

			switch( pixelFormat )
			{
				case PIXEL_FORMAT_BGR:
				case PIXEL_FORMAT_BGRU:
					currPixVal[3] = *pCurrent++;
					currPixVal[2] = *pCurrent++;
					currPixVal[1] = *pCurrent;
					break;

				case PIXEL_FORMAT_RGB:
				case PIXEL_FORMAT_RGBU:
					currPixVal[1] = *pCurrent++;
					currPixVal[2] = *pCurrent++;
					currPixVal[3] = *pCurrent;
					break;
				default:
					currPixVal[1] = currPixVal[2] = currPixVal[3] = 0;
			}

			// Calculate the grey value
			currPixVal[0] = ( currPixVal[3] + 6*currPixVal[2] + 3*currPixVal[1] ) / 10;

			if ( x == 0 )
			{
				for ( unsigned int i=0; i < minVal.size(); i++ )
				{
					minVal[i] = maxVal[i] = currPixVal[i];
				}
			}

			for ( unsigned int i=0; i < minVal.size(); i++ )
			{
				accumVal[i] += currPixVal[i];

				if ( minVal[i] > currPixVal[i] )
				{
					minVal[i] = currPixVal[i];
				}
				else if ( maxVal[i] < currPixVal[i] )
				{
					maxVal[i] = currPixVal[i];
				}
			}

			pStats->grey.vecMax[y] = maxVal[0];
			pStats->grey.vecMin[y] = minVal[0];
			pStats->grey.vecMean[y] = accumVal[0] / cols;

			pStats->red.vecMax[y] = maxVal[1];
			pStats->red.vecMin[y] = minVal[1];
			pStats->red.vecMean[y] = accumVal[1] / cols;

			pStats->green.vecMax[y] = maxVal[2];
			pStats->green.vecMin[y] = minVal[2];
			pStats->green.vecMean[y] = accumVal[2] / cols;

			pStats->blue.vecMax[y] = maxVal[3];
			pStats->blue.vecMin[y] = minVal[3];
			pStats->blue.vecMean[y] = accumVal[3] / cols;
		}
	}
}

	BEGIN_MESSAGE_MAP(RowColPlotPage, CDialog)
	ON_BN_CLICKED(IDC_MODE_COL, &RowColPlotPage::OnBnClickedModeColumn)
	ON_BN_CLICKED(IDC_MODE_ROW, &RowColPlotPage::OnBnClickedModeRow)
	ON_BN_CLICKED(IDC_DISPLAY_GREY, &RowColPlotPage::OnControlCheckStateChanged)
	ON_BN_CLICKED(IDC_DISPLAY_RED, &RowColPlotPage::OnControlCheckStateChanged)
	ON_BN_CLICKED(IDC_DISPLAY_GREEN, &RowColPlotPage::OnControlCheckStateChanged)
	ON_BN_CLICKED(IDC_DISPLAY_BLUE, &RowColPlotPage::OnControlCheckStateChanged)
	ON_BN_CLICKED(IDC_FUNCTION_MAX, &RowColPlotPage::OnControlCheckStateChanged)
	ON_BN_CLICKED(IDC_FUNCTION_MIN, &RowColPlotPage::OnControlCheckStateChanged)
	ON_BN_CLICKED(IDC_FUNCTION_MEAN, &RowColPlotPage::OnControlCheckStateChanged)
END_MESSAGE_MAP()


	// RowColPlotPage message handlers

void RowColPlotPage::OnBnClickedModeColumn()
{
	m_rowColMode = Histogram::ROWCOL_COLUMN;
}

void RowColPlotPage::OnBnClickedModeRow()
{
	m_rowColMode = Histogram::ROWCOL_ROW;
}

BOOL RowColPlotPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rowColMode = Histogram::ROWCOL_COLUMN;
	m_showGrey = TRUE;
	m_showRed = FALSE;
	m_showBlue = FALSE;
	m_showGreen = FALSE;
	m_showMax = TRUE;
	m_showMean = TRUE;
	m_showMin = TRUE;
	UpdateData(FALSE);

	CheckRadioButton(IDC_MODE_COL,IDC_MODE_ROW,IDC_MODE_COL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void RowColPlotPage::EnableColorChannelCheckBoxes()
{
	GetDlgItem(IDC_DISPLAY_RED)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISPLAY_GREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISPLAY_BLUE)->EnableWindow(TRUE);
}
void RowColPlotPage::DisableColorChannelCheckBoxes()
{
	GetDlgItem(IDC_DISPLAY_RED)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISPLAY_GREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISPLAY_BLUE)->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_DISPLAY_RED))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_DISPLAY_GREEN))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_DISPLAY_BLUE))->SetCheck(FALSE);
	/*m_showRed = FALSE;
	  m_showBlue = FALSE;
	  m_showGreen = FALSE;
	  UpdateData(FALSE);*/
}
void RowColPlotPage::OnControlCheckStateChanged()
{
	UpdateData(TRUE);
}
