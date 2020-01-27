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
#include "VideoRecordingPage.h"

const char VideoFormatList[][MAX_PATH] =
{
	"Uncompressed",
	"M-JPEG",
	"H.264"
};

const CString VideoRecordingPage::VIDEO_FRAMERATE_DEF = "15.0";
const CString VideoRecordingPage::AVI_FILE_SIZE_DEF = "0";
const float VideoRecordingPage::VIDEO_FRAMERATE_MAX = (float)10000.0;
const float VideoRecordingPage::VIDEO_FRAMERATE_MIN = (float)0.001;



// VideoRecordingPage dialog

IMPLEMENT_DYNAMIC(VideoRecordingPage, CDialog)

	VideoRecordingPage::VideoRecordingPage(CWnd* pParent /*=NULL*/)
: CDialog(VideoRecordingPage::IDD, pParent)
{

}

VideoRecordingPage::~VideoRecordingPage()
{
}

void VideoRecordingPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VIDEO_RECORD_TYPE, m_combo_VideoFormat);
	DDX_Control(pDX, IDC_EDIT_FRAME_RATE, m_edit_frameRate);
	DDX_Control(pDX, IDC_BTN_SET_FRAME_RATE, m_btn_setFrameRate);
	DDX_Control(pDX, IDC_STATIC_COLOR_PROCESS_MSG, m_static_colorProcessMsg);
	DDX_Control(pDX, IDC_EDIT_FILE_SIZE, m_edit_fileSize);
}

	BEGIN_MESSAGE_MAP(VideoRecordingPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_RECORD_TYPE, &VideoRecordingPage::OnCbnSelchangeComboVideoRecordType)
	ON_BN_CLICKED(IDC_BTN_SET_FRAME_RATE, &VideoRecordingPage::OnBnClickedBtnSetFrameRate)
	ON_BN_CLICKED(IDOK, &VideoRecordingPage::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &VideoRecordingPage::OnBnClickedCancel)
END_MESSAGE_MAP()

	// VideoRecordingPage message handlers

BOOL VideoRecordingPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i = 0; i < NUM_VIDEO_FORMATS; i++)
	{
		m_combo_VideoFormat.AddString(VideoFormatList[i]);
	}
	m_combo_VideoFormat.SetCurSel(UNCOMPRESSED);

	// Create mjpeg pane
	if (m_mjpegVideoPane.Create(IDD_PANE_VIDEO_MJPEG, this) == FALSE)
	{
		MessageBox("Failed to create the MJPEG video options pane");
		return FALSE;
	}

	// Create h264 pane
	if (m_h264VideoPane.Create(IDD_PANE_VIDEO_H264, this) == FALSE)
	{
		MessageBox("Failed to create the H264 video options pane");
		return FALSE;
	}

	CRect parentRect, itemRect;
	int nX, nY, nXc, nYc;
	this->GetClientRect(&parentRect);

	RECT parentWindowRect, itemWindowRect;

	this->GetWindowRect(&parentWindowRect);


	CWnd* frameRateCtrl = GetDlgItem(IDC_STATIC_AVI_SIZE);

	frameRateCtrl->GetClientRect(&itemRect);

	frameRateCtrl->GetWindowRect(&itemWindowRect);

	this->ScreenToClient(&itemWindowRect);

	//this->GetItemRect(0, &itemRect);
	nX  = itemWindowRect.left;//parentRect.left + 5;
	nY  = itemWindowRect.bottom + 10;
	nXc = parentRect.right - nX - 5;
	nYc = parentRect.bottom - nY - 5;

	m_mjpegVideoPane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	m_h264VideoPane.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);

	// Frame rate control
	m_edit_frameRate.SetWindowText(VIDEO_FRAMERATE_DEF);
	m_edit_fileSize.SetWindowText(AVI_FILE_SIZE_DEF);
	OnCbnSelchangeComboVideoRecordType();
	return TRUE;
}

void VideoRecordingPage::GetSettings( VideoSettings* videoSettings )
{
	void* formatSettings = NULL;
	float framerate;
	unsigned int aviSize = 0;

	GetFramerate(&framerate);

	GetAVIFileSize(&aviSize);

	videoSettings->aviSize = aviSize;

	switch(m_combo_VideoFormat.GetCurSel())
	{
		case UNCOMPRESSED:
			videoSettings->videoFormat = UNCOMPRESSED;
			videoSettings->aviOption.frameRate = framerate;
			break;
		case MJPEG:
			videoSettings->videoFormat = MJPEG;
			videoSettings->mjpgOption.frameRate = framerate;

			unsigned int quality;
			m_mjpegVideoPane.GetQuality(&quality);
			videoSettings->mjpgOption.quality = quality;
			break;
		case H264:
			videoSettings->videoFormat = H264;
			videoSettings->h264Option.frameRate = framerate;

			unsigned int width, height, bitrate;
			m_h264VideoPane.GetBitrate(&bitrate);
			GetCurrentCameraResolution(&width, &height);

			videoSettings->h264Option.width = width;
			videoSettings->h264Option.height = height;
			videoSettings->h264Option.bitrate = bitrate;
			break;
		default:
			videoSettings->videoFormat = UNCOMPRESSED;
			videoSettings->aviOption.frameRate = framerate;
			break;
	}
}

BOOL VideoRecordingPage::ConvertToInt(CString* text, unsigned int* integer )
{
	errno = 0;
	*integer = _ttoi(text->GetBuffer());
	return ((errno == 0) || (*integer != 0));
}

BOOL VideoRecordingPage::GetFramerate( float* framerate )
{
	CString framerateTxt;
	m_edit_frameRate.GetWindowText(framerateTxt);

	*framerate = (float)atof(framerateTxt);
	return (*framerate != 0.0);
}

void VideoRecordingPage::GetAVIFileSize(unsigned int* fileSize)
{
	CString fileSizeTxt;
	m_edit_fileSize.GetWindowText(fileSizeTxt);

	*fileSize = (unsigned int)atof(fileSizeTxt);
}

void VideoRecordingPage::DisplayMJPEGOptions(BOOL display)
{
	m_mjpegVideoPane.ShowWindow(display);
}

void VideoRecordingPage::DisplayH264Options(BOOL display)
{
	m_h264VideoPane.ShowWindow(display);
}

void VideoRecordingPage::OnCbnSelchangeComboVideoRecordType()
{
	switch (m_combo_VideoFormat.GetCurSel())
	{
		case UNCOMPRESSED:
			DisplayMJPEGOptions(FALSE);
			DisplayH264Options(FALSE);
			m_edit_fileSize.EnableWindow(TRUE);
			break;
		case MJPEG:
			DisplayH264Options(FALSE);
			DisplayMJPEGOptions(TRUE);
			m_edit_fileSize.EnableWindow(TRUE);
			break;
		case H264:
			DisplayMJPEGOptions(FALSE);
			DisplayH264Options(TRUE);
			m_edit_fileSize.EnableWindow(FALSE);
			break;
		default:
			break;
	}
}

void VideoRecordingPage::OnBnClickedBtnSetFrameRate()
{
	Property prop;
	prop.type= FRAME_RATE;
	m_pCameraVid->GetProperty(&prop);
	float frameRateFlt = prop.absValue;

	char frameRateTxt[MAX_PATH];
	sprintf(frameRateTxt, "%4.3f", frameRateFlt);
	m_edit_frameRate.SetWindowText(frameRateTxt);
}

void VideoRecordingPage::StoreCameraPtr( CameraBase* m_pCamera )
{
	m_pCameraVid = m_pCamera;
	UpdateModeDependentControls();
}

void VideoRecordingPage::UpdateModeDependentControls()
{
	if (m_pCameraVid != NULL)
	{
		unsigned int regVal = 0;
		Error error = m_pCameraVid->ReadRegister(0x1040, &regVal);
		if (error != PGRERROR_OK)
		{
			m_static_colorProcessMsg.ShowWindow(FALSE);
		}
		else
		{
			m_static_colorProcessMsg.ShowWindow(regVal != 0x59595959);
		}
	}
}

BOOL VideoRecordingPage::GetCurrentCameraResolution( unsigned int* width, unsigned int* height )
{
	Error error;
	CameraInfo camInfo;


	error = ((Camera*)m_pCameraVid)->GetCameraInfo(&camInfo);

	if (camInfo.interfaceType == INTERFACE_GIGE)
	{
		GigEImageSettings gigeImageSettings;
		error = ((GigECamera*)m_pCameraVid)->GetGigEImageSettings(&gigeImageSettings);
		*width = gigeImageSettings.width;
		*height = gigeImageSettings.height;
	}
	else
	{
		VideoMode videoMode;
		FrameRate frameRate;
		Format7ImageSettings f7ImageSettings;

		error = ((Camera*)m_pCameraVid)->GetVideoModeAndFrameRate(&videoMode, &frameRate );

		switch(videoMode)
		{
			case VIDEOMODE_160x120YUV444:
				*width = 160;
				*height = 120;
				break;
			case VIDEOMODE_320x240YUV422:
				*width = 320;
				*height = 240;
				break;
			case VIDEOMODE_640x480YUV411:
			case VIDEOMODE_640x480YUV422:
			case VIDEOMODE_640x480RGB:
			case VIDEOMODE_640x480Y8:
			case VIDEOMODE_640x480Y16:
				*width = 640;
				*height = 480;
				break;
			case VIDEOMODE_800x600YUV422:
			case VIDEOMODE_800x600RGB:
			case VIDEOMODE_800x600Y8:
			case VIDEOMODE_800x600Y16:
				*width = 800;
				*height = 600;
				break;
			case VIDEOMODE_1024x768YUV422:
			case VIDEOMODE_1024x768RGB:
			case VIDEOMODE_1024x768Y8:
			case VIDEOMODE_1024x768Y16:
				*width = 1024;
				*height = 768;
				break;
			case VIDEOMODE_1280x960YUV422:
			case VIDEOMODE_1280x960RGB:
			case VIDEOMODE_1280x960Y8:
			case VIDEOMODE_1280x960Y16:
				*width = 1280;
				*height = 960;
				break;
			case VIDEOMODE_1600x1200YUV422:
			case VIDEOMODE_1600x1200RGB:
			case VIDEOMODE_1600x1200Y8:
			case VIDEOMODE_1600x1200Y16 :
				*width = 1600;
				*height = 1200;
				break;
			case VIDEOMODE_FORMAT7:
				unsigned int packetSize;
				float percentage;
				((Camera*)m_pCameraVid)->GetFormat7Configuration(&f7ImageSettings, &packetSize, &percentage);
				*width = f7ImageSettings.width;
				*height = f7ImageSettings.height;
				break;
			default:
				break;
		}
	}
	return TRUE;
}

void VideoRecordingPage::ValidateSettings( CString* errorList )
{
	switch(m_combo_VideoFormat.GetCurSel())
	{
		case MJPEG:
			unsigned int quality;
			if (!m_mjpegVideoPane.GetQuality(&quality))
			{
				errorList->Append("Invalid JPEG Quality value specified.\n");
			}
			break;
		case H264:
			unsigned int bitrate;
			if (!m_h264VideoPane.GetBitrate(&bitrate))
			{
				errorList->Append("Invalid H.264 bitrate Quality value specified.\n");
				errorList->AppendFormat("H.264 bitrate Quality value should be between %d and %d.\n", m_h264VideoPane.GetBitrateMin(), m_h264VideoPane.GetBitrateMax());
			}
			break;
		default:
			break;
	}

	float frameRate = 0.0;
	if (!GetFramerate(&frameRate) || (frameRate > VIDEO_FRAMERATE_MAX) || (frameRate < VIDEO_FRAMERATE_MIN))
	{
		errorList->Append("Invalid Frame Rate specified.\n");
		errorList->AppendFormat("Frame Rate value should be between %.3f and %.1f.\n", VIDEO_FRAMERATE_MIN, VIDEO_FRAMERATE_MAX);
	}
}

void VideoRecordingPage::EnableControls(BOOL enable)
{
	m_combo_VideoFormat.EnableWindow(enable);
	m_edit_frameRate.EnableWindow(enable);
	m_btn_setFrameRate.EnableWindow(enable);

	m_mjpegVideoPane.EnableWindow(enable);
	m_h264VideoPane.EnableWindow(enable);

	// File size editbox is only enabled for non-H264 formats
	if (enable)
	{
		switch (m_combo_VideoFormat.GetCurSel())
		{
		case UNCOMPRESSED:
			m_edit_fileSize.EnableWindow(TRUE);
			break;
		case MJPEG:
			m_edit_fileSize.EnableWindow(TRUE);
			break;
		case H264:
			m_edit_fileSize.EnableWindow(FALSE);
			break;
		default:
			break;
		}
	}
	else
	{
		m_edit_fileSize.EnableWindow(FALSE);
	}
}

//Disable OnOK for Enter key
void VideoRecordingPage::OnBnClickedOk()
{
}

//Disable OnCancel for ESC key
void VideoRecordingPage::OnBnClickedCancel()
{
}
