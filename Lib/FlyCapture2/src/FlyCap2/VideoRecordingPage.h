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

#include "VideoRecordingMJPEGPane.h"
#include "VideoRecordingH264Pane.h"

using namespace FlyCapture2;

// VideoRecordingPage dialog
class VideoRecordingPage : public CDialog
{
	DECLARE_DYNAMIC(VideoRecordingPage)

	public:

		enum VideoFormatTypes
		{
			UNCOMPRESSED,
			MJPEG,
			H264,
			NUM_VIDEO_FORMATS
		};

		struct VideoSettings
		{
			char filename[MAX_PATH];
			VideoFormatTypes videoFormat;
			AVIOption aviOption;
			MJPGOption mjpgOption;
			H264Option h264Option;
			char fileExtension[MAX_PATH];
			unsigned int aviSize;
		};

		VideoRecordingPage(CWnd* pParent = NULL);   // standard constructor
		virtual ~VideoRecordingPage();

		virtual BOOL OnInitDialog();

		void GetSettings( VideoSettings* videoSettings );
		void ValidateSettings( CString* errorList );
		void EnableControls(BOOL enable);
		void StoreCameraPtr( CameraBase* m_pCamera );
		void UpdateModeDependentControls();

		// Dialog Data
		enum { IDD = IDD_TABPAGE_VIDEO_RECORD };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			afx_msg void OnCbnSelchangeComboVideoRecordType();
		afx_msg void OnBnClickedBtnSetFrameRate();
		afx_msg void OnBnClickedOk();
		afx_msg void OnBnClickedCancel();

		BOOL GetCurrentCameraResolution( unsigned int* width, unsigned int* height );
		BOOL GetBitrate(unsigned int* bitrate);
		void GetFilePath( char* filename );
		BOOL GetQuality( unsigned int* quality );
		BOOL GetFramerate( float* framerate );
		void GetAVIFileSize(unsigned int* fileSize);
		void DisplayMJPEGOptions(BOOL display);
		void DisplayH264Options(BOOL display);

		BOOL ConvertToInt(CString* text, unsigned int* integer );

	protected:
		CComboBox m_combo_VideoFormat;

		CEdit m_edit_frameRate;
		CEdit m_edit_fileSize;
		CButton m_btn_setFrameRate;

		CVideoRecordingMJPEGPane m_mjpegVideoPane;
		CVideoRecordingH264Pane m_h264VideoPane;

		CameraBase* m_pCameraVid;

		static const float VIDEO_FRAMERATE_MAX;
		static const float VIDEO_FRAMERATE_MIN;
		static const CString VIDEO_FRAMERATE_DEF;
		static const CString AVI_FILE_SIZE_DEF;
		CStatic m_static_colorProcessMsg;
};
