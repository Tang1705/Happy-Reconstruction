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
#include "afxwin.h"
#include "afxcmn.h"
#include <bitset>

#include "RecordingDialogCommon.h"
#include "ImageRecordingBMPPane.h"
#include "ImageRecordingJPG2KPane.h"
#include "ImageRecordingJPGPane.h"
#include "ImageRecordingPNGPane.h"
#include "ImageRecordingPXMPane.h"
#include "ImageRecordingTIFFPane.h"

using namespace FlyCapture2;

// ImageRecordingPage dialog
class ImageRecordingPage : public CDialog
{
	DECLARE_DYNAMIC(ImageRecordingPage)

	public:

		enum ImageFormatTypes
		{
			PGM,
			PPM,
			BMP,
			JPEG,
			JPEG2000,
			TIFF,
			PNG,
			RAW,
			NUM_IMAGE_FORMATS
		};

		struct ImageSettings
		{
			char filename[MAX_PATH];
			ImageFormatTypes imageFormat;
			PGMOption pgmOption;
			PPMOption ppmOption;
			JPEGOption jpgOption;
			JPG2Option jpg2Option;
			TIFFOption tiffOption;
			PNGOption pngOption;
			BMPOption bmpOption;
			char fileExtension[MAX_PATH];
		};

		ImageRecordingPage(CWnd* pParent = NULL);   // standard constructor
		virtual ~ImageRecordingPage();

		virtual BOOL OnInitDialog();
		void GetSettings( ImageSettings* imageSettings );
		void ValidateSettings( CString* errorList );
		void EnableControls(BOOL enable);
		void StoreCameraPtr( CameraBase* m_pCamera );
		void UpdateModeDependentControls();
		BOOL GetSaveBayerCheckState();

		// Dialog Data
		enum { IDD = IDD_TABPAGE_IMAGE_RECORD };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			afx_msg void OnCbnSelchangeComboImageRecordType();
		afx_msg void OnBnClickedOk();
		afx_msg void OnBnClickedCancel();

		void GetFilePath( char* filename );
		BOOL GetPxMBinaryFile( BOOL* binaryFile );
		BOOL GetJPEGQuality( unsigned int* quality );
		BOOL GetTIFFCompression( TIFFOption::CompressionMethod* compression );
		BOOL GetPNGInterlaced( BOOL* interlaced );
		BOOL GetPNGCompression( unsigned int* compression );
		BOOL GetJPEGProgressive( BOOL* progressive );
		BOOL GetJPEG2KQuality( unsigned int* quality );
		BOOL GetBMP8bitIndexedColor(BOOL* indexedColor);

		void DisplayTIFFOptions(BOOL display);
		void DisplayPNGOptions(BOOL display);
		void DisplayJPEGOptions(BOOL display);
		void DisplayJPG2kOptions(BOOL display);
		void DisplayPxMOptions(BOOL display);
		void DisplayBMPOptions(BOOL display);

		unsigned int GetValidImageFormatSelection();

	protected:

		CComboBox m_combo_ImageFormat;

		CButton m_chk_saveBayerTile;

		CImageRecordingBMPPane m_bmpImagePane;
		CImageRecordingJPG2KPane m_jpg2kImagePane;
		CImageRecordingJPGPane m_jpgImagePane;
		CImageRecordingPNGPane m_pngImagePane;
		CImageRecordingPXMPane m_pxmImagePane;
		CImageRecordingTIFFPane m_tiffImagePane;

		std::bitset<NUM_IMAGE_FORMATS> m_validFormats;

		PixelFormat m_currPixelFormat;

		CameraBase* m_pCameraImg;
};
