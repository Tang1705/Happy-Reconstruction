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

#ifndef RECORDING_DIALOG_H
#define RECORDING_DIALOG_H

#include "afxcmn.h"
#include "ImageRecordingPage.h"
#include "VideoRecordingPage.h"
#include "afxwin.h"



using namespace FlyCapture2;

// RecordingDialog dialog
class RecordingDialog : public CDialog
{
	DECLARE_DYNAMIC(RecordingDialog)

	public:

		// RecordingException
		class RecordingException : public std::runtime_error
	{
		public:
			RecordingException(const std::string& error) : std::runtime_error(error){}
	};

		// Dialog Data
		enum { IDD = IDD_DIALOG_IMG_VID_RECORD };

		enum OutputType
		{
			OUTPUT_TYPE_IMAGE,
			OUTPUT_TYPE_VIDEO
		};

		enum SaveOptionType
		{
			NUMBER_OF_FRAMES,
			EVERY_NTH_FRAME,
			NUMBER_OF_SECONDS,
			EVERY_NTH_SECOND
		} ;

		enum RecorderState
		{
			STOPPED,
			STARTED,
			SAVING,
			STOPPING,
			ABORT_SAVING
		};

		enum RecordingEvents
		{
			END_LIVE_RECORDING,
			DATA_IN_BUFFER,
			NUM_RECORDING_EVENTS
		};

		RecordingDialog(CWnd* pParent = NULL);   // standard constructor
		virtual ~RecordingDialog();

		virtual BOOL OnInitDialog();
		void DoRecording( Image* rawImage, BOOL isCorruptFrame );
		BOOL IsRecordingActive();
		void StoreCamPtr( CameraBase* pCamera );
		void StopRecording();
		BOOL IsCaptureCorrupt();
		void UpdateModeDependentControls();

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			afx_msg void OnBnClickedButtonBrowse();
		afx_msg void OnTcnSelchangeTabOutputType(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnBnClickedRadioNumFrames();
		afx_msg void OnBnClickedRadioNthFrame();
		afx_msg void OnBnClickedRadioNumSeconds();
		afx_msg void OnBnClickedRadioNthSeconds();
		afx_msg void OnBnClickedButtonStartStopVideoRecord();
		afx_msg void OnTimer(UINT_PTR nIDEvent);

		static UINT ThreadSaveFrame( void* pparam );
		UINT ThreadSaveFrameHelper();

		void RetrieveNextImageFromBuffer(Image* image);

		void StartRecording();
		void StoppingRecording();
		void ProcessCurrentFrame( Image* rawImage);
		Error SaveImage( Image* tmp, ImageRecordingPage::ImageSettings* imageSettings, unsigned int count );
		BOOL BufferFrame(Image* image);
		void UpdateImageCounters();

		SaveOptionType GetSaveType();
		void GetFilePath( CString* filename );
		void GetImageSettings( ImageRecordingPage::ImageSettings* imageSettings );
		void GetVideoSettings( VideoRecordingPage::VideoSettings* videoSettings );
		BOOL GetNumFrames(unsigned int* numFrames);
		BOOL GetNthFrame(unsigned int* nthFrame);
		BOOL GetNthFrameTotal(unsigned int* nthFrameTotal);
		BOOL GetNumSeconds(unsigned int* numSeconds);
		BOOL GetNthSecondsTotal(unsigned int* nthSecondsTotal);
		BOOL GetNthSecond(unsigned int* nthSecond);

		BOOL ValidInput(CString* errorList);
		void ValidateFileName( CString* errorList );
		void ValidateSaveOptions( CString* errorList );
		void ValidateImageSettings( CString* errorList );

		void DisableControls();
		void EnableControls();
		void EnableSaveBayerTileCheckBox();
		void UpdateSavingOptions();

		BOOL ConvertToInt(CString text, unsigned int* integer );
		void SaveImageToFile(Image* image, ImageRecordingPage::ImageSettings* imageSettings);
		void SaveImageToVideo(AVIRecorder* aviRecorder, Image* image );
		BOOL CreateRecordingEvents();
		void DeleteRecordingEvents();
		void ChangeState(RecorderState state);
		RecorderState GetRecorderState();
		BOOL PreTranslateMessage(MSG* pMsg);

	protected:
		// Image saving options tab
		ImageRecordingPage m_imageRecordingPage;
		ImageRecordingPage::ImageSettings m_imageSettings;

		// Video saving options tab
		VideoRecordingPage m_videoRecordingPage;
		VideoRecordingPage::VideoSettings m_videoSettings;

		// Saving thread
		CWinThread* m_saveFrameLoopThread;
		HANDLE m_recordingEvents[NUM_RECORDING_EVENTS];

		// Save filename
		CString m_saveFilename;
		CString m_saveFilenameBase;

		// image buffer
		std::vector<Image> m_imageBuffer;
		CCriticalSection m_recorderBuffer;
		CCriticalSection m_startStopControl;
		CCriticalSection m_buttonState;

		CEdit m_edit_SaveFilePath;

		CButton m_radio_NumFrames;
		CEdit m_edit_NumFrames;

		CButton m_radio_NthFrame;
		CEdit m_edit_NthFrame;
		CEdit m_edit_NthTotalFrames;

		CButton m_radio_NumSeconds;
		CEdit m_edit_NumSeconds;

		CButton m_radio_NthSecond;
		CEdit m_edit_NthSecond;
		CEdit m_edit_NthTotalSeconds;

		CButton m_chk_captureCorruptFrames;

		CTabCtrl m_tabCtrl_OutputType;

		CStatic m_static_FrameCounter;
		CStatic m_static_CorruptFrameCounter;
		unsigned int m_frameCounter;
		unsigned int m_corruptFrameCounter;
		CStatic m_static_savedImageCount;
		unsigned int m_savedImageCounter;
		CStatic m_static_bufferedCounter;
		unsigned int m_streamingFrameCounter;

		CStatic m_static_availableMemory;
		CStatic m_static_totalMemory;
		CStatic m_static_memoryLoad;

		CStatic m_static_statusOutput;

		CStatic m_static_bufferedModeText;
		CStatic m_static_AvailableMemText;
		CStatic m_static_TotalMemText;

		CButton m_btn_close;
		CButton m_btn_StartStop;

		enum TimerID{ TIMER_DURATION, TIMER_INTERVAL };
		UINT_PTR m_recorderTimerDuration;
		UINT_PTR m_recorderTimerInterval;
		BOOL m_durationExpiredFlag;
		BOOL m_intervalExpiredFlag;
		CCriticalSection m_timerExpiredState;

		RecorderState m_currRecordingState;
		CCriticalSection m_recordingMutex;

		CameraBase* m_pCameraRec;

		CButton m_radio_bufferedMode;
		CButton m_radio_streamingMode;
		GrabMode m_grabMode;

		BOOL m_isSaveBayerImageSelected;
};
#endif
