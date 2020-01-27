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

#include "FrameRateCounter.h"
#include "InformationPane.h"
#include "EventStatDialog.h"
#include "HistogramDialog.h"
#include "RecordingDialog.h"
#include "ReceivedFrameRateCounter.h"
#ifdef GENICAM
#include "XMLPathDlg.h";
#endif
//
// Size of the window when it the application first starts.
//
#define _DEFAULT_WINDOW_X  640
#define _DEFAULT_WINDOW_Y  480

#pragma once

class CFlyCap2_MFCDoc : public CDocument
{
	protected: // create from serialization only
		CFlyCap2_MFCDoc();
		DECLARE_DYNCREATE(CFlyCap2_MFCDoc)
			// Implementation
	public:
			virtual ~CFlyCap2_MFCDoc();
#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
#endif

			// Critical section to protect access to the processed image
			CCriticalSection m_csData;

			// Structure used to draw to the screen.
			BITMAPINFO        m_bitmapInfo;

			// Get the processed frame rate
			double GetProcessedFrameRate();

			// Get the requested frame rate
			double GetRequestedFrameRate();

			// Get the received frame rate
			double GetReceivedFrameRate();

			// Get the data pointer to the image
			unsigned char* GetProcessedPixels();

			// Get the dimensions of the image
			void GetImageSize( unsigned int* pWidth, unsigned int* pHeight );

			// Initialize the bitmap struct used for drawing.
			void InitBitmapStruct( int cols, int rows );

			// The image grab thread.
			static UINT ThreadGrabImage( void* pparam );

			void DoRecordingStuff();

			void GetCamResolutionAndPixelFormat(unsigned int* rows, unsigned int* cols, PixelFormat* pixelFmt);

			BOOL GetDimensionsFromVideoMode(VideoMode mode, unsigned int* rows, unsigned int* cols);

			void CheckCameraPower();

			// The object grab image loop.  Only executed from within the grab thread.
			UINT DoGrabLoop();

			// Redraw all the views in the application
			void RedrawAllViews();

			bool IsGrabThreadRunning();

			void EnableOpenGL();
			void EnableGDI();
			void EnableD2D();
			bool IsOpenGLEnabled();
			bool IsGDIEnabled();
			bool IsD2DEnabled();
			void SetD2DSupport(bool isSupported);
			unsigned int GetBytePerPixel();
			InformationPane::InformationPaneStruct GetRawImageInformation();
			bool GetPauseStatus();

			/*void OnStartImageTransfer();
			  void OnStopImageTransfer();*/
			CString GetTitleString();
			CString GetVersionString();
			FlyCapture2::Image GetConvertedImage();
			void AddEvent(EventType eventType);
			void UpdateHistogramWindow();
			bool HasBadEventRecently();
			void ToggleEventStatDialog();
			void RefreshColorProcessingAlgorithm();
			virtual BOOL OnNewDocument();
			virtual void OnCloseDocument(void);

	protected:
			bool m_componentsInitialized;
			FlyCapture2::CameraControlDlg m_camCtlDlg;
#ifdef GENICAM
			FlyCapture2::PropertyGridDlg m_propGridDlg;
			XMLPathDlg m_xmlPathDlg;
#endif
			EventStatDialog m_eventStatDlg;
			HistogramDialog m_histogramDlg;
			FlyCapture2::CameraBase* m_pCamera;
			FlyCapture2::CameraInfo m_cameraInfo;
			FlyCapture2::Image m_rawImage;

			RecordingDialog  m_recordingDlg;

			//Image m_outputImage;
			FlyCapture2::Image m_processedImage;

			//Raw image pixel format
			FlyCapture2::PixelFormat m_rawPixelFormat;

			// Critical section to protect access to the raw image
			CCriticalSection m_csRawImageData;

			void InitializeComponents();

			void UncheckAllColorProcessingAlgorithm();

			/** Bus manager. Used for registering and unregistering callbacks.*/
			FlyCapture2::BusManager m_busMgr;

			/** Camera arrival callback handle. */
			FlyCapture2::CallbackHandle m_cbArrivalHandle;

			/** Camera removal callback handle. */
			FlyCapture2::CallbackHandle m_cbRemovalHandle;

			/** Camera reset callback handle. */
			FlyCapture2::CallbackHandle m_cbResetHandle;

			/** Register all relevant callbacks with the library. */
			void RegisterCallbacks();

			/** Unregister all relevant callbacks with the library. */
			void UnregisterCallbacks();

			/**
			 * Bus arrival handler that is passed to BusManager::RegisterCallback().
			 * This simply emits a signal that calls the real handler.
			 *
			 * @param pParam The parameter passed to the BusManager::RegisterCallback().
			 */
			static void OnBusArrival( void* pParam, unsigned int serialNumber );

			/**
			 * Bus removal handler that is passed to BusManager::RegisterCallback().
			 * This simply emits a signal that calls the real handler.
			 *
			 * @param pParam The parameter passed to the BusManager::RegisterCallback().
			 */
			static void OnBusRemoval( void* pParam, unsigned int serialNumber );

			static void OnBusReset( void* pParam, unsigned int serialNumber );


			/** Queue that will store serial numbers of arrival cams. */
			std::queue<unsigned int> m_arrQueue;

			/** Queue that will store serial numbers of arrival cams. */
			std::queue<unsigned int> m_remQueue;

			void OnBusRemovalEvent();
			void OnBusArrivalEvent();

			bool m_continueGrabThread;
			bool m_isSelectingNewCamera;
			bool m_disableEmbeddedTimeStamp;
			EmbeddedImageInfo m_embeddedInfo;
			int m_previousTransmitFailures;
			int m_previousRecoveryCount;
			int m_previousLinkerErrorCount;
			int m_previousSkippedImages;
			int m_previousPacketResendRequested;
			int m_previousPacketResendReceived;

			CWinThread* m_grabLoopThread;

			HANDLE m_threadDoneEvent;
			HANDLE m_threadImDoneTooEvent;

			FrameRateCounter m_processedFrameRate;
			ReceivedFrameRateCounter m_receivedFrameRate;

			bool Start( FlyCapture2::PGRGuid guid );

			bool Stop();

			void ForcePGRY16Mode();

			bool EnableEmbeddedTimeStamp(FlyCapture2::CameraBase* cam);

			bool DisableEmbeddedTimeStamp(FlyCapture2::CameraBase* cam);

			void ShowErrorMessageDialog(char* mainTxt, FlyCapture2::Error error, bool detailed = true);

			BOOL CFlyCap2_MFCDoc::GetPixelFormatFromVideoMode(VideoMode mode, bool stippled, PixelFormat* pixFormat);

			unsigned int CFlyCap2_MFCDoc::GetBppFromPixelFormat( PixelFormat pixelFormat );

	private:
			unsigned int m_prevWidth;
			unsigned int m_prevHeight;
			bool m_enableOpenGL;
			bool m_enableGDI;
			bool m_enableD2D;
			bool m_supportD2D;
			bool m_cameraIsPaused;
			bool m_isColorCamera;
			PGRGuid m_guid;

			// Keeps track of the last filter index used for image saving.
			unsigned int m_uiFilterIndex;
			/**
			 * Parse the time register in hours, minutes and seconds.
			 *
			 * @param timeRegVal Value of the time register.
			 * @param hours Parsed hours.
			 * @param mins Parsed minutes.
			 * @param seconds Parsed seconds.
			 */
			static void ParseTimeRegister(
					unsigned int timeRegVal,
					unsigned int& hours,
					unsigned int& mins,
					unsigned int& seconds );

			// Generated message map functions
	protected:
			DECLARE_MESSAGE_MAP()
	public:
				afx_msg void OnToggleCameraControl();
				afx_msg void OnFileSaveAs();
				afx_msg void OnStartImageTransfer();
				afx_msg void OnStopImageTransfer();
				afx_msg void OnUpdateStartImageTransfer(CCmdUI *pCmdUI);
				afx_msg void OnColorAlgorithmNone();
				afx_msg void OnColorAlgorithmNearestNeighbor();
				afx_msg void OnColorAlgorithmEdgeSensing();
				afx_msg void OnColorAlgorithmHQLinear();
				afx_msg void OnColorAlgorithmDirectionalFilter();
				afx_msg void OnColorAlgorithmWeightedDirectionalFilter();
				afx_msg void OnColorAlgorithmRigorous();
				afx_msg void OnColorAlgorithmIPP();
				afx_msg void OnUpdateStartImageTransferBtn(CCmdUI *pCmdUI);
				afx_msg void OnUpdateFileStopImageTransferBtn(CCmdUI *pCmdUI);
				afx_msg void OnUpdateViewEnableOpenGL(CCmdUI *pCmdUI);
				afx_msg void OnViewEventStat();
				afx_msg void OnToggleHistgram();
				afx_msg void OnToggleRecorder();
				afx_msg void OnUpdateCameraControlToggleButton(CCmdUI *pCmdUI);
				afx_msg void OnUpdateHistgramBtn(CCmdUI *pCmdUI);
				afx_msg void OnUpdateRecordingBtn(CCmdUI *pCmdUI);
				afx_msg void OnUpdateEventStatsBtn(CCmdUI *pCmdUI);
				afx_msg void OnUpdateSaveAsBtn(CCmdUI *pCmdUI);
				afx_msg void OnUpdateMenuItemGDI(CCmdUI *pCmdUI);
				afx_msg void OnUpdateMenuItemDirect2D(CCmdUI *pCmdUI);
				afx_msg void OnSettingsTogglecamerapropertygrid();
				afx_msg void OnUpdateSettingsTogglecamerapropertygrid(CCmdUI *pCmdUI);
				afx_msg void OnSettingsSetxmlpath();
				afx_msg void OnUpdateSettingsSetxmlpath(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmNone(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmNearestneighbor(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmEdgesensing(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmHqlinear(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmDirectionalfilter(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmWeightedDirectionalfilter(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmRigorous(CCmdUI *pCmdUI);
				afx_msg void OnUpdateColorprocessingalgorithmIpp(CCmdUI *pCmdUI);
				afx_msg void OnPauseimagetransfer();
				afx_msg void OnUpdatePauseimagetransfer(CCmdUI *pCmdUI);
};


