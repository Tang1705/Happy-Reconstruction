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
#include "ImageRecordingPage.h"
#include "RecordingDialogCommon.h"

const char ImageFormatList[][FlyCap2RecordingDialog::MAX_COMBO_STRING] =
{
	"PGM",
	"PPM",
	"BMP",
	"JPEG",
	"JPEG2000",
	"TIFF",
	"PNG",
	"RAW"
};

// ImageRecordingPage dialog

IMPLEMENT_DYNAMIC(ImageRecordingPage, CDialog)

	ImageRecordingPage::ImageRecordingPage(CWnd* pParent /*=NULL*/)
: CDialog(ImageRecordingPage::IDD, pParent)
{

}

ImageRecordingPage::~ImageRecordingPage()
{
}

void ImageRecordingPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE_RECORD_TYPE, m_combo_ImageFormat);
	DDX_Control(pDX, IDC_CHK_SAVE_BAYER_IMAGE, m_chk_saveBayerTile);
}

	BEGIN_MESSAGE_MAP(ImageRecordingPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_IMAGE_RECORD_TYPE, &ImageRecordingPage::OnCbnSelchangeComboImageRecordType)
	ON_BN_CLICKED(IDOK, &ImageRecordingPage::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ImageRecordingPage::OnBnClickedCancel)
END_MESSAGE_MAP()

	// ImageRecordingPage message handlers
BOOL ImageRecordingPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i = 0; i < NUM_IMAGE_FORMATS; i++)
	{
		m_combo_ImageFormat.AddString(ImageFormatList[i]);
	}
	m_combo_ImageFormat.SetCurSel(PGM);
	m_validFormats.set();
	// Create bmp pane
	if (m_bmpImagePane.Create(IDD_PANE_IMAGE_BMP, this) == FALSE)
	{
		MessageBox("Failed to create the BMP image options pane");
		return FALSE;
	}

	// Create jpg2k pane
	if (m_jpg2kImagePane.Create(IDD_PANE_IMAGE_JPG2K, this) == FALSE)
	{
		MessageBox("Failed to create the JPEG 2000 image options pane");
		return FALSE;
	}

	// Create jpg pane
	if (m_jpgImagePane.Create(IDD_PANE_IMAGE_JPG, this) == FALSE)
	{
		MessageBox("Failed to create the JPEG image options pane");
		return FALSE;
	}

	// Create png pane
	if (m_pngImagePane.Create(IDD_PANE_IMAGE_PNG, this) == FALSE)
	{
		MessageBox("Failed to create the PNG image options pane");
		return FALSE;
	}

	// Create pxm pane
	if (m_pxmImagePane.Create(IDD_PANE_IMAGE_PXM, this) == FALSE)
	{
		MessageBox("Failed to create the PGM/PPM image options pane");
		return FALSE;
	}

	// Create tiff pane
	if (m_tiffImagePane.Create(IDD_PANE_IMAGE_TIFF, this) == FALSE)
	{
		MessageBox("Failed to create the TIFF image options pane");
		return FALSE;
	}

	CRect parentRect, itemRect;
	int nX, nY, nXc, nYc;

	this->GetClientRect(&parentRect);
	RECT parentWindowRect, itemWindowRect;
	this->GetWindowRect(&parentWindowRect);

	CWnd* frameRateCtrl = GetDlgItem(IDC_STATIC_IMAGE_FORMAT);
	frameRateCtrl->GetClientRect(&itemRect);
	frameRateCtrl->GetWindowRect(&itemWindowRect);
	this->ScreenToClient(&itemWindowRect);

	//this->GetItemRect(0, &itemRect);
	nX  = itemWindowRect.left;//parentRect.left + 5;
	nY  = itemWindowRect.bottom + 10;
	nXc = parentRect.right - nX - 5;
	nYc = parentRect.bottom - nY - 5;

	// Add panes to parent
	m_bmpImagePane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	m_jpg2kImagePane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	m_jpgImagePane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	m_pngImagePane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	m_pxmImagePane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	m_tiffImagePane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);

	OnCbnSelchangeComboImageRecordType();
	return TRUE;
}

void ImageRecordingPage::StoreCameraPtr( CameraBase* m_pCamera )
{
	m_pCameraImg = m_pCamera;
	UpdateModeDependentControls();
}

void ImageRecordingPage::UpdateModeDependentControls()
{
	if (m_pCameraImg != NULL)
	{
		unsigned int regVal = 0;
		Error error = m_pCameraImg->ReadRegister(0x1040, &regVal);
		if (error != PGRERROR_OK)
		{
			m_chk_saveBayerTile.ShowWindow(FALSE);
		}
		else
		{
			m_chk_saveBayerTile.ShowWindow(regVal != 0x59595959);
		}
	}
}

BOOL ImageRecordingPage::GetSaveBayerCheckState()
{
	return m_chk_saveBayerTile.GetCheck() && m_chk_saveBayerTile.IsWindowVisible();
}

void ImageRecordingPage::GetSettings( ImageSettings* imageSettings )
{
	void* formatSettings = NULL;

	BOOL binaryFile;
	unsigned int quality;
	BOOL progressive;
	TIFFOption::CompressionMethod compressionMethod;
	BOOL interlaced;
	unsigned int compression;
	BOOL indexedColor;

	switch (GetValidImageFormatSelection())
	{
		case PGM:
			imageSettings->imageFormat = PGM;
			strcpy(imageSettings->fileExtension, "pgm");

			m_pxmImagePane.GetPxMBinaryFile(&binaryFile);
			imageSettings->pgmOption.binaryFile = (binaryFile != 0);
			break;
		case PPM:
			imageSettings->imageFormat = PPM;
			strcpy(imageSettings->fileExtension, "ppm");


			m_pxmImagePane.GetPxMBinaryFile(&binaryFile);
			imageSettings->ppmOption.binaryFile = (binaryFile != 0);

			break;
		case BMP:
			imageSettings->imageFormat = BMP;
			strcpy(imageSettings->fileExtension, "bmp");

			m_bmpImagePane.GetBMP8bitIndexedColor(&indexedColor);
			imageSettings->bmpOption.indexedColor_8bit = (indexedColor != 0);
			break;

		case JPEG:
			imageSettings->imageFormat = JPEG;
			strcpy(imageSettings->fileExtension, "jpg");

			m_jpgImagePane.GetJPEGQuality(&quality);
			m_jpgImagePane.GetJPEGProgressive(&progressive);
			imageSettings->jpgOption.quality = quality;
			imageSettings->jpgOption.progressive = (progressive != 0);
			break;
		case JPEG2000:
			imageSettings->imageFormat = JPEG2000;
			strcpy(imageSettings->fileExtension, "jp2");

			m_jpg2kImagePane.GetJPEG2KQuality(&quality);
			imageSettings->jpg2Option.quality = quality;
			break;
		case TIFF:
			imageSettings->imageFormat = TIFF;
			strcpy(imageSettings->fileExtension, "tif");

			m_tiffImagePane.GetTIFFCompression(&compressionMethod);
			imageSettings->tiffOption.compression = (TIFFOption::CompressionMethod)compressionMethod;
			break;
		case PNG:
			imageSettings->imageFormat = PNG;
			strcpy(imageSettings->fileExtension, "png");

			m_pngImagePane.GetPNGInterlaced(&interlaced);
			m_pngImagePane.GetPNGCompression(&compression);
			imageSettings->pngOption.compressionLevel = compression;
			imageSettings->pngOption.interlaced = (interlaced != 0);
			break;
		case RAW:
			imageSettings->imageFormat = RAW;
			strcpy(imageSettings->fileExtension, "raw");
			break;
		default:
			imageSettings->imageFormat = RAW;
			strcpy(imageSettings->fileExtension, "raw");
			break;
	}
}

void ImageRecordingPage::DisplayTIFFOptions(BOOL display)
{
	m_tiffImagePane.ShowWindow(display);
}

void ImageRecordingPage::DisplayPNGOptions(BOOL display)
{
	m_pngImagePane.ShowWindow(display);
}

void ImageRecordingPage::DisplayJPEGOptions(BOOL display)
{
	m_jpgImagePane.ShowWindow(display);
}

void ImageRecordingPage::DisplayJPG2kOptions(BOOL display)
{
	m_jpg2kImagePane.ShowWindow(display);
}

void ImageRecordingPage::DisplayPxMOptions(BOOL display)
{
	m_pxmImagePane.ShowWindow(display);
}

void ImageRecordingPage::DisplayBMPOptions(BOOL display)
{
	m_bmpImagePane.ShowWindow(display);
}

void ImageRecordingPage::OnCbnSelchangeComboImageRecordType()
{
	switch (GetValidImageFormatSelection())
	{
		case PGM:
		case PPM:
			DisplayJPEGOptions(FALSE);
			DisplayJPG2kOptions(FALSE);
			DisplayPNGOptions(FALSE);
			DisplayTIFFOptions(FALSE);
			DisplayBMPOptions(FALSE);
			DisplayPxMOptions(TRUE);
			break;
		case BMP:
			DisplayJPEGOptions(FALSE);
			DisplayJPG2kOptions(FALSE);
			DisplayPNGOptions(FALSE);
			DisplayTIFFOptions(FALSE);
			DisplayPxMOptions(FALSE);
			DisplayBMPOptions(TRUE);
			break;
		case RAW:
			DisplayJPEGOptions(FALSE);
			DisplayJPG2kOptions(FALSE);
			DisplayPNGOptions(FALSE);
			DisplayTIFFOptions(FALSE);
			DisplayPxMOptions(FALSE);
			DisplayBMPOptions(FALSE);
			break;
		case JPEG:
			DisplayJPG2kOptions(FALSE);
			DisplayPNGOptions(FALSE);
			DisplayTIFFOptions(FALSE);
			DisplayPxMOptions(FALSE);
			DisplayBMPOptions(FALSE);
			DisplayJPEGOptions(TRUE);
			break;
		case JPEG2000:
			DisplayJPEGOptions(FALSE);
			DisplayPNGOptions(FALSE);
			DisplayTIFFOptions(FALSE);
			DisplayPxMOptions(FALSE);
			DisplayBMPOptions(FALSE);
			DisplayJPG2kOptions(TRUE);
			break;
		case TIFF:
			DisplayJPEGOptions(FALSE);
			DisplayPNGOptions(FALSE);
			DisplayPxMOptions(FALSE);
			DisplayJPG2kOptions(FALSE);
			DisplayBMPOptions(FALSE);
			DisplayTIFFOptions(TRUE);
			break;
		case PNG:
			DisplayJPEGOptions(FALSE);
			DisplayPxMOptions(FALSE);
			DisplayJPG2kOptions(FALSE);
			DisplayTIFFOptions(FALSE);
			DisplayBMPOptions(FALSE);
			DisplayPNGOptions(TRUE);
			break;
		default:
			break;
	}
}

void ImageRecordingPage::ValidateSettings( CString* errorList )
{
	unsigned int quality;
	switch(GetValidImageFormatSelection())
	{
		case JPEG:
			if(!m_jpgImagePane.GetJPEGQuality(&quality))
			{
				errorList->Append("Invalid JPEG Quality value specified.\n");
			}
			break;
		case JPEG2000:
			if (!m_jpg2kImagePane.GetJPEG2KQuality(&quality))
			{
				errorList->Append("Invalid JPEG2000 Quality value specified.\n");
			}
			break;
		default:
			break;
	}
}

void ImageRecordingPage::EnableControls(BOOL enable)
{
	m_combo_ImageFormat.EnableWindow(enable);

	m_bmpImagePane.EnableWindow(enable);
	m_jpg2kImagePane.EnableWindow(enable);
	m_jpgImagePane.EnableWindow(enable);
	m_pngImagePane.EnableWindow(enable);
	m_pxmImagePane.EnableWindow(enable);
	m_tiffImagePane.EnableWindow(enable);
}

unsigned int ImageRecordingPage::GetValidImageFormatSelection()
{
	unsigned int selection = m_combo_ImageFormat.GetCurSel();
	unsigned int index = 0;

	for (unsigned int i = 0; i < NUM_IMAGE_FORMATS; i++)
	{
		if (m_validFormats.test(i))
		{
			if (index == selection)
			{
				index = i;
				break;
			}
			else
			{
				index++;
			}
		}
	}
	return index;
}

//Disable OnOK for Enter key
void ImageRecordingPage::OnBnClickedOk()
{
}

//Disable OnCancel for ESC key
void ImageRecordingPage::OnBnClickedCancel()
{
}
