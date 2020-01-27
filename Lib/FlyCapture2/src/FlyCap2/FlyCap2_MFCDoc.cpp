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
#include "FlyCap2_MFCDoc.h"
#include "FlyCap2_MFCView.h"
#include "SaveImageFileDialog.h"
using namespace FlyCapture2;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFlyCap2_MFCDoc

IMPLEMENT_DYNCREATE(CFlyCap2_MFCDoc, CDocument)

	BEGIN_MESSAGE_MAP(CFlyCap2_MFCDoc, CDocument)
	ON_COMMAND(ID_CAMERACONTROL_TOGGLECAMERACONTROL, &CFlyCap2_MFCDoc::OnToggleCameraControl)
	ON_COMMAND(ID_FILE_SAVE_AS, &CFlyCap2_MFCDoc::OnFileSaveAs)
	ON_COMMAND(ID_FILE_STARTIMAGETRANSFER, &CFlyCap2_MFCDoc::OnStartImageTransfer)
	ON_COMMAND(ID_FILE_STOPIMAGETRANSFER, &CFlyCap2_MFCDoc::OnStopImageTransfer)
	ON_COMMAND(ID_COLORPROCESSINGALGORITHM_NONE, &CFlyCap2_MFCDoc::OnColorAlgorithmNone)
	ON_COMMAND(ID_COLORPROCESSINGALGORITHM_NEARESTNEIGHBOR, &CFlyCap2_MFCDoc::OnColorAlgorithmNearestNeighbor)
	ON_COMMAND(ID_COLORPROCESSINGALGORITHM_EDGESENSING, &CFlyCap2_MFCDoc::OnColorAlgorithmEdgeSensing)
	ON_COMMAND(ID_COLORPROCESSINGALGORITHM_HQLINEAR, &CFlyCap2_MFCDoc::OnColorAlgorithmHQLinear)
	ON_COMMAND(ID_COLORPROCESSINGALGORITHM_DIRECTIONALFILTER, &CFlyCap2_MFCDoc::OnColorAlgorithmDirectionalFilter)
	ON_COMMAND(ID_COLORPROCESSINGALGORITHM_WEIGHTEDDIRECTIONALFILTER, &CFlyCap2_MFCDoc::OnColorAlgorithmWeightedDirectionalFilter)
	ON_COMMAND(ID_COLORPROCESSINGALGORITHM_RIGOROUS, &CFlyCap2_MFCDoc::OnColorAlgorithmRigorous)
ON_COMMAND(ID_COLORPROCESSINGALGORITHM_IPP, &CFlyCap2_MFCDoc::OnColorAlgorithmIPP)

	ON_UPDATE_COMMAND_UI(ID_FILE_STARTIMAGETRANSFER, &CFlyCap2_MFCDoc::OnUpdateStartImageTransferBtn)
	ON_UPDATE_COMMAND_UI(ID_FILE_STOPIMAGETRANSFER, &CFlyCap2_MFCDoc::OnUpdateFileStopImageTransferBtn)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICMODE_OPENGL, &CFlyCap2_MFCDoc::OnUpdateViewEnableOpenGL)
	ON_COMMAND(ID_HISTGRAM_BTN, &CFlyCap2_MFCDoc::OnToggleHistgram)
	ON_COMMAND(ID_FILE_GRAB_AVI, &CFlyCap2_MFCDoc::OnToggleRecorder)
	ON_COMMAND(ID_VIEW_EVENTSTAT, &CFlyCap2_MFCDoc::OnViewEventStat)
	ON_UPDATE_COMMAND_UI(ID_CAMERACONTROL_TOGGLECAMERACONTROL, &CFlyCap2_MFCDoc::OnUpdateCameraControlToggleButton)
	ON_UPDATE_COMMAND_UI(ID_HISTGRAM_BTN, &CFlyCap2_MFCDoc::OnUpdateHistgramBtn)
	ON_UPDATE_COMMAND_UI(ID_FILE_GRAB_AVI, &CFlyCap2_MFCDoc::OnUpdateRecordingBtn)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EVENTSTAT, &CFlyCap2_MFCDoc::OnUpdateEventStatsBtn)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CFlyCap2_MFCDoc::OnUpdateSaveAsBtn)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICMODE_GDI, &CFlyCap2_MFCDoc::OnUpdateMenuItemGDI)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICMODE_DIRECT2D, &CFlyCap2_MFCDoc::OnUpdateMenuItemDirect2D)
	ON_COMMAND(ID_SETTINGS_TOGGLECAMERAPROPERTYGRID, &CFlyCap2_MFCDoc::OnSettingsTogglecamerapropertygrid)
	ON_COMMAND(ID_SETTINGS_SETXMLPATH, &CFlyCap2_MFCDoc::OnSettingsSetxmlpath)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_TOGGLECAMERAPROPERTYGRID, &CFlyCap2_MFCDoc::OnUpdateSettingsTogglecamerapropertygrid)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_SETXMLPATH, &CFlyCap2_MFCDoc::OnUpdateSettingsSetxmlpath)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_NONE, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmNone)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_NEARESTNEIGHBOR, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmNearestneighbor)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_EDGESENSING, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmEdgesensing)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_HQLINEAR, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmHqlinear)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_DIRECTIONALFILTER, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmDirectionalfilter)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_WEIGHTEDDIRECTIONALFILTER, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmWeightedDirectionalfilter)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_RIGOROUS, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmRigorous)
	ON_UPDATE_COMMAND_UI(ID_COLORPROCESSINGALGORITHM_IPP, &CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmIpp)
	ON_COMMAND(ID_FILE_PAUSEIMAGETRANSFER, &CFlyCap2_MFCDoc::OnPauseimagetransfer)
	ON_UPDATE_COMMAND_UI(ID_FILE_PAUSEIMAGETRANSFER, &CFlyCap2_MFCDoc::OnUpdatePauseimagetransfer)
END_MESSAGE_MAP()


	// CFlyCap2_MFCDoc construction/destruction

CFlyCap2_MFCDoc::CFlyCap2_MFCDoc()
{
	InitBitmapStruct( _DEFAULT_WINDOW_X, _DEFAULT_WINDOW_Y );

	m_continueGrabThread = false;
	m_threadDoneEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_threadImDoneTooEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_uiFilterIndex = 0;

	//EnableOpenGL(false);
	EnableGDI();
	m_componentsInitialized = false;
	m_isSelectingNewCamera = false;
	m_isColorCamera = false;
	m_grabLoopThread = NULL;
	m_pCamera = NULL;
	RegisterCallbacks();
}

CFlyCap2_MFCDoc::~CFlyCap2_MFCDoc()
{
	CloseHandle( m_threadDoneEvent );
	CloseHandle( m_threadImDoneTooEvent );
	m_eventStatDlg.DestroyWindow();
	m_histogramDlg.DestroyWindow();
	m_recordingDlg.DestroyWindow();

	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}
	UnregisterCallbacks();
}
void CFlyCap2_MFCDoc::InitializeComponents()
{
	if (m_componentsInitialized == true)
	{
		m_eventStatDlg.ShowWindow(SW_HIDE);
		m_histogramDlg.ShowWindow(SW_HIDE);
		m_eventStatDlg.CleanUpCounters();
		m_histogramDlg.StopUpdate();
		m_recordingDlg.ShowWindow(SW_HIDE);
#ifdef GENICAM
		m_xmlPathDlg.ShowWindow(SW_HIDE);
		m_xmlPathDlg.InitializeControls();
		m_propGridDlg.Hide();
		m_propGridDlg.Disconnect();
#endif
		return;
	}
	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView(pos); //Get current view
	if (m_eventStatDlg.Create(EventStatDialog::IDD, pView) == FALSE)
	{
		TRACE0("Failed to create event statistics dialog box\n");
		CString csMessage;
		csMessage.Format(
				"Failed to create event statistics dialog box.");
		AfxMessageBox( csMessage, MB_ICONSTOP );
		m_componentsInitialized = false;
		return;
	}
	if (m_histogramDlg.Create(HistogramDialog::IDD, pView) == FALSE)
	{
		TRACE0("Failed to create histogram dialog box\n");
		CString csMessage;
		csMessage.Format(
				"Failed to create histogram dialog box.");
		AfxMessageBox( csMessage, MB_ICONSTOP );
		m_componentsInitialized = false;
		return;
	}
	if (m_recordingDlg.Create(RecordingDialog::IDD, pView) == FALSE)
	{
		TRACE0("Failed to create recording dialog box\n");
		CString csMessage;
		csMessage.Format(
				"Failed to create recording dialog box.");
		AfxMessageBox( csMessage, MB_ICONSTOP );
		m_componentsInitialized = false;
		return;
	}

#ifdef GENICAM
	if (m_xmlPathDlg.Create(XMLPathDlg::IDD, pView) == FALSE)
	{
		TRACE0("Failed to create XML Path dialog box\n");
		CString csMessage;
		csMessage.Format(
				"Failed to create XML Path dialog box.");
		AfxMessageBox( csMessage, MB_ICONSTOP );
		m_componentsInitialized = false;
		return;
	}
#endif
	m_componentsInitialized = true;
}


void CFlyCap2_MFCDoc::InitBitmapStruct( int cols, int rows )
{
	BITMAPINFOHEADER* pheader = &m_bitmapInfo.bmiHeader;

	// Initialize permanent data in the bitmapinfo header.
	pheader->biSize          = sizeof( BITMAPINFOHEADER );
	pheader->biPlanes        = 1;
	pheader->biCompression   = BI_RGB;
	pheader->biXPelsPerMeter = 100;
	pheader->biYPelsPerMeter = 100;
	pheader->biClrUsed       = 0;
	pheader->biClrImportant  = 0;

	// Set a default window size.
	pheader->biWidth    = cols;
	pheader->biHeight   = -rows;
	pheader->biBitCount = 32;

	m_bitmapInfo.bmiHeader.biSizeImage = 0;
}

bool CFlyCap2_MFCDoc::EnableEmbeddedTimeStamp(FlyCapture2::CameraBase* cam)
{
	if(cam != NULL && cam->IsConnected())
	{
		Error error = cam->GetEmbeddedImageInfo(&m_embeddedInfo);
		if( error != PGRERROR_OK )
		{
			return false;
		}

		if(m_embeddedInfo.timestamp.available && !m_embeddedInfo.timestamp.onOff)
		{
			m_embeddedInfo.timestamp.onOff = true;
			error = cam->SetEmbeddedImageInfo(&m_embeddedInfo);
			if( error != PGRERROR_OK )
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool CFlyCap2_MFCDoc::DisableEmbeddedTimeStamp(FlyCapture2::CameraBase* cam)
{
	if(cam != NULL && cam->IsConnected())
	{
		m_embeddedInfo.timestamp.onOff = false;
		Error error = cam->SetEmbeddedImageInfo(&m_embeddedInfo);
		if( error != PGRERROR_OK )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

BOOL CFlyCap2_MFCDoc::OnNewDocument()
{
	m_isSelectingNewCamera = true;
	Error error;
	if (!CDocument::OnNewDocument())
		return FALSE;
	// (SDI documents will reuse this document)

	// Set the default image processing parameters
	//Image::SetDefaultColorProcessing( NEAREST_NEIGHBOR );
	Image::SetDefaultOutputFormat( PIXEL_FORMAT_BGRU );

	//reset previous camera event counters
	m_previousTransmitFailures = 0;
	m_previousRecoveryCount = 0;
	m_previousLinkerErrorCount = 0;
	m_previousSkippedImages = 0;
	m_previousPacketResendRequested = 0;
	m_previousPacketResendReceived = 0;

	// If entering this function from File->New Camera, stop the grab thread
	// first before doing anything else
	if ( m_continueGrabThread == true )
	{
		m_continueGrabThread = false;

		if (m_pCamera->IsConnected())
		{
			m_pCamera->StopCapture();
			SetEvent(m_threadImDoneTooEvent);
		}

		DWORD dwRet = WaitForSingleObject( m_threadDoneEvent, 5000 );
		if ( dwRet == WAIT_TIMEOUT )
		{
			// Timed out while waiting for thread to exit
			//m_grabLoopThread->PostThreadMessageA( WM_QUIT,0,0);// Force thread exit
			TerminateThread(m_grabLoopThread->m_hThread,0);// Force thread exit
			TRACE("Grab thread - force exit\n");
			delete m_grabLoopThread;
			m_grabLoopThread = NULL;
		}

		if(m_disableEmbeddedTimeStamp)
		{
			DisableEmbeddedTimeStamp(m_pCamera);
		}

		m_pCamera->Disconnect();

		m_processedImage.ReleaseBuffer();
	}

	m_camCtlDlg.Hide();
	m_camCtlDlg.Disconnect();

#ifdef GENICAM
	m_propGridDlg.Hide();
	m_propGridDlg.Disconnect();
#endif
	//initialize components
	InitializeComponents();

	// Let the user select a camera
	bool okSelected;
	PGRGuid arGuid[64];
	unsigned int size = 64;
	CameraSelectionDlg camSlnDlg;
	camSlnDlg.ShowModal( &okSelected, arGuid, &size );
	if ( okSelected != true )
	{
		return FALSE;
	}

	if (Start(arGuid[0]) == false)
	{
		return FALSE;
	}

	// Fix for Bug 21703
	if(AfxGetMainWnd() != NULL)
	{
		// Update Windows title when VIEW has already been created
		AfxGetMainWnd()->SetWindowText(GetTitleString());
	}

	m_cameraIsPaused = false;
	m_isSelectingNewCamera = false;
	return TRUE;
}

CString CFlyCap2_MFCDoc::GetTitleString()
{
	CString title;
	if (m_pCamera == NULL)
	{
		title.Format("FlyCap2");
	}
	else
	{
		title.Format(
				"FlyCap2 %s - %s %s (%u)",
				GetVersionString(),
				m_cameraInfo.vendorName,
				m_cameraInfo.modelName,
				m_cameraInfo.serialNumber );
	}

	return title;
}

CString CFlyCap2_MFCDoc::GetVersionString()
{
	FC2Version version;
	const Error errorVer = Utilities::GetLibraryVersion(&version);
	if (errorVer != PGRERROR_OK)
	{
		return "0.0.0.0";
	}

	CString verStr;
	verStr.Format(
			"%u.%u.%u.%u",
			version.major,
			version.minor,
			version.type,
			version.build);
	return verStr;
}

void CFlyCap2_MFCDoc::OnCloseDocument(void)
{
	m_histogramDlg.StopUpdate();
	if(m_recordingDlg.IsRecordingActive())
	{
		m_recordingDlg.StopRecording();
	}

	m_continueGrabThread = false;

	if (m_pCamera != NULL && m_pCamera->IsConnected())
	{
		m_pCamera->StopCapture();
		SetEvent(m_threadImDoneTooEvent);
	}

	if (m_grabLoopThread != NULL)
	{
		DWORD dwRet = WaitForSingleObject( m_grabLoopThread->m_hThread, 5000 );
		if ( dwRet == WAIT_TIMEOUT )
		{
			// Timed out while waiting for thread to exit
			//m_grabLoopThread->PostThreadMessageA( WM_QUIT,0,0);// Force thread exit
			TerminateThread(m_grabLoopThread->m_hThread,0);// Force thread exit
			m_pCamera->StopCapture();//camera might not stop due to force exit thread
			SetEvent(m_threadImDoneTooEvent);
			delete m_grabLoopThread;
			m_grabLoopThread = NULL;
		}
	}

	m_camCtlDlg.Hide();
	m_camCtlDlg.Disconnect();

#ifdef GENICAM
	m_propGridDlg.Hide();
	m_propGridDlg.Disconnect();
#endif

	if (m_pCamera != NULL)
	{
		m_pCamera->Disconnect();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	CDocument::OnCloseDocument();
}

void CFlyCap2_MFCDoc::UpdateHistogramWindow()
{
	if ( m_histogramDlg.IsWindowVisible() == TRUE )
	{
		CSingleLock dataLock(&m_csRawImageData);
		if (dataLock.IsLocked())
		{
			return;
		}
		if ( dataLock.Lock() ==TRUE)
		{
			m_histogramDlg.SetImageForStatistics(m_rawImage);
			dataLock.Unlock();
		}

	}
}

UINT CFlyCap2_MFCDoc::ThreadGrabImage( void* pparam )
{
	TRACE("Grab thread - start\n");

	CFlyCap2_MFCDoc* pDoc = ((CFlyCap2_MFCDoc*)pparam);
	const UINT uiRetval = pDoc->DoGrabLoop();
	if( uiRetval != 0 )
	{
		CString csMessage;
		csMessage.Format(
				"The grab thread has encountered a problem and had to terminate." );
		AfxMessageBox( csMessage, MB_ICONSTOP );

		// Signal that the thread has died.
		SetEvent( pDoc->m_threadDoneEvent );
	}

	TRACE("Grab thread - exit\n");

	return uiRetval;
}


	UINT
CFlyCap2_MFCDoc::DoGrabLoop()
{
	Error error;
	CString csMessage;
	BOOL isCorruptFrame = FALSE;

	PixelFormat pixFormat = UNSPECIFIED_PIXEL_FORMAT, pixFormatPrev = UNSPECIFIED_PIXEL_FORMAT;
	unsigned int cols = 0, rows = 0, colsPrev = 0, rowsPrev = 0;

	m_disableEmbeddedTimeStamp = EnableEmbeddedTimeStamp(m_pCamera);

	// Store current image settings. Used to detect a mode change while recording
	GetCamResolutionAndPixelFormat(&rowsPrev, &colsPrev, &pixFormatPrev);

	// Start of main grab loop
	while( m_continueGrabThread )
	{
		if(!GetPauseStatus())
		{
			Image buffImage;
			error = m_pCamera->RetrieveBuffer( &buffImage );
			if (error != PGRERROR_OK)
			{
				if (error == PGRERROR_IMAGE_CONSISTENCY_ERROR)
				{
					AddEvent(IMAGE_CONSISTENCY_ERRORS);

					if(m_recordingDlg.IsRecordingActive())
					{
						m_recordingDlg.DoRecording(&buffImage, true);
					}
				}
				else
				{
					time_t rawtime;
					struct tm * timeinfo;
					time( &rawtime );
					timeinfo = localtime( &rawtime );

					char currTimeStr[128];
					sprintf(currTimeStr, "%s", asctime(timeinfo));
					currTimeStr[strlen(currTimeStr) - 1] = '\0';

					char errorMsg[1024];
					sprintf(
							errorMsg,
							"%s: Grab loop had an error: %s\n",
							currTimeStr,
							error.GetDescription() );
					TRACE(errorMsg);
				}
				continue;
			}

			rows = buffImage.GetRows();
			cols = buffImage.GetCols();
			pixFormat = buffImage.GetPixelFormat();
			m_rawPixelFormat = pixFormat;

			BOOL modeChangeDetected = (rows != rowsPrev) || (cols != colsPrev) || ((PixelFormat)pixFormat != pixFormatPrev);
			if (m_recordingDlg.IsRecordingActive())
			{
				if (modeChangeDetected)
				{
					m_recordingDlg.StopRecording();
					AfxMessageBox( "A mode change was detected while recording. Recording will stop.", MB_ICONSTOP );

					rowsPrev = rows;
					colsPrev = cols;
					pixFormatPrev = pixFormat;
					m_recordingDlg.UpdateModeDependentControls();
				}
				else
				{
					m_recordingDlg.DoRecording(&buffImage, false);
				}
			}
			else if (modeChangeDetected && m_recordingDlg.IsWindowVisible())
			{
				rowsPrev = rows;
				colsPrev = cols;
				pixFormatPrev = pixFormat;
				m_recordingDlg.UpdateModeDependentControls();
			}

			CSingleLock dataLock(&m_csRawImageData);
			dataLock.Lock();
			m_rawImage = buffImage;
			dataLock.Unlock();
			AddEvent(TOTAL_NUMBER_OF_FRAMES);
		}
		else
		{
			// Make sure image was not re-pained too fast
			// when camera was paused(stopped).
			// Re-paint is necessary to refresh the View
			Sleep(200);
		}

		// Check to see if the thread should die.
		if (!m_continueGrabThread)
		{
			break;
		}

		// Update current framerate.
		if(!GetPauseStatus())
		{
			m_processedFrameRate.NewFrame();
			m_receivedFrameRate.NewFrame(&m_rawImage.GetTimeStamp());
		}
		// We try to detect whether the view is getting behind on servicing
		// the invalidate requests we send to it.  If there is still an
		// invalid area, don't bother color processing this frame.
		bool skipProcessing = false;
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			if (GetUpdateRect(GetNextView(pos)->GetSafeHwnd(), NULL, FALSE) != 0)
			{
				skipProcessing = true;
			}
		}

		// Check to see if the thread should die.
		if( !m_continueGrabThread )
		{
			break;
		}

		if (!skipProcessing)
		{
			if (!GetPauseStatus())
			{
				// Do post processing on the image.
				unsigned int rows,cols,stride;
				PixelFormat format;
				m_rawImage.GetDimensions(&rows, &cols, &stride, &format);

				CSingleLock dataLock(&m_csData);
				dataLock.Lock();

				if (m_enableOpenGL)
				{
					error = m_rawImage.Convert(PIXEL_FORMAT_BGR, &m_processedImage);
				}
				else
				{
					error = m_rawImage.Convert(PIXEL_FORMAT_BGRU, &m_processedImage);
				}

				if (error != PGRERROR_OK)
				{
					AddEvent(IMAGE_CONVERSION_ERRORS);
					csMessage.Format(
							"Convert Failure: %s", error.GetDescription());
					continue;
				}
				dataLock.Unlock();
			}
			InitBitmapStruct(cols, rows);
			RedrawAllViews();
		}
	}

	if(m_disableEmbeddedTimeStamp)
	{
		DisableEmbeddedTimeStamp(m_pCamera);
	}

	// End of main grab loop
	SetEvent(m_threadDoneEvent);

	//WAIT
	WaitForSingleObject(m_threadImDoneTooEvent, INFINITE);

	return 0;
}

void CFlyCap2_MFCDoc::GetCamResolutionAndPixelFormat(unsigned int* rows, unsigned int* cols, PixelFormat* pixelFmt)
{
	// get the current source-image settings
	Error error;
	VideoMode videoMode;
	FrameRate frameRate;
	CameraInfo camInfo;

	error = m_pCamera->GetCameraInfo(&camInfo);

	if (camInfo.interfaceType == INTERFACE_GIGE)
	{
		GigECamera* gigeCam = static_cast<GigECamera*>(m_pCamera);
		GigEImageSettings gigeImageSettings;
		error = gigeCam->GetGigEImageSettings(&gigeImageSettings);
		*cols = gigeImageSettings.width;
		*rows = gigeImageSettings.height;
		*pixelFmt = gigeImageSettings.pixelFormat;
	}
	else
	{
		Camera* cam = static_cast<Camera*>(m_pCamera);
		error = cam->GetVideoModeAndFrameRate(&videoMode, &frameRate);

		bool isStippled = false;

		if (videoMode == VIDEOMODE_FORMAT7)
		{
			Format7ImageSettings f7ImageSettings;
			unsigned int packetSize;
			float percentage;

			error = cam->GetFormat7Configuration(&f7ImageSettings, &packetSize, &percentage);

			*cols = f7ImageSettings.width;
			*rows = f7ImageSettings.height;
			*pixelFmt = f7ImageSettings.pixelFormat;
		}
		else
		{
			// if white balance property is present then stippled is true. This detects
			// when camera is in Y8/Y16 and raw bayer output is enabled
			PropertyInfo propInfo;
			propInfo.type = WHITE_BALANCE;

			m_pCamera->GetPropertyInfo(&propInfo);

			if (propInfo.present)
			{
				isStippled = true;
			}

			if (!GetPixelFormatFromVideoMode(videoMode, isStippled, pixelFmt))
			{
				*pixelFmt = PIXEL_FORMAT_RAW8;
			}
			GetDimensionsFromVideoMode(videoMode, rows, cols);
		}
	}
}


BOOL CFlyCap2_MFCDoc::GetDimensionsFromVideoMode(VideoMode mode, unsigned int* rows, unsigned int* cols)
{
	if (rows == NULL || cols == NULL)
	{
		return FALSE;
	}

	switch(mode)
	{
		case VIDEOMODE_160x120YUV444:
			*cols = 160;
			*rows = 120;
			break;
		case VIDEOMODE_320x240YUV422:
			*cols = 320;
			*rows = 240;
			break;
		case VIDEOMODE_640x480YUV411:
		case VIDEOMODE_640x480YUV422:
		case VIDEOMODE_640x480RGB:
		case VIDEOMODE_640x480Y8:
		case VIDEOMODE_640x480Y16:
			*cols = 640;
			*rows = 480;
			break;
		case VIDEOMODE_800x600YUV422:
		case VIDEOMODE_800x600RGB:
		case VIDEOMODE_800x600Y8:
		case VIDEOMODE_800x600Y16:
			*cols = 800;
			*rows = 600;
			break;
		case VIDEOMODE_1024x768YUV422:
		case VIDEOMODE_1024x768RGB:
		case VIDEOMODE_1024x768Y8:
		case VIDEOMODE_1024x768Y16:
			*cols = 1024;
			*rows = 768;
			break;
		case VIDEOMODE_1280x960YUV422:
		case VIDEOMODE_1280x960RGB:
		case VIDEOMODE_1280x960Y8:
		case VIDEOMODE_1280x960Y16:
			*cols = 1280;
			*rows = 960;
			break;
		case VIDEOMODE_1600x1200YUV422:
		case VIDEOMODE_1600x1200RGB:
		case VIDEOMODE_1600x1200Y8:
		case VIDEOMODE_1600x1200Y16:
			*cols = 1600;
			*rows = 1200;
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

// CFlyCap2_MFCDoc diagnostics

#ifdef _DEBUG
void CFlyCap2_MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlyCap2_MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFlyCap2_MFCDoc commands

void CFlyCap2_MFCDoc::RedrawAllViews()
{
	POSITION pos = GetFirstViewPosition();
	while ( pos != NULL )
	{
		InvalidateRect( GetNextView( pos )->GetSafeHwnd(), NULL, TRUE );
	}
	if (m_histogramDlg.IsWindowVisible() == TRUE)
	{
		m_histogramDlg.InvalidateRect(NULL,TRUE);
	}
}

double CFlyCap2_MFCDoc::GetProcessedFrameRate()
{
	return m_processedFrameRate.GetFrameRate();
}

double CFlyCap2_MFCDoc::GetReceivedFrameRate()
{
	return m_receivedFrameRate.GetFrameRate();
}

double CFlyCap2_MFCDoc::GetRequestedFrameRate()
{
	// Set up the frame rate data
	Property prop;
	prop.type = FRAME_RATE;
	if ( m_pCamera == NULL)
	{
		return 0.0;
	}
	else
	{
		Error error = m_pCamera->GetProperty( &prop );
		return (error == PGRERROR_OK) ? prop.absValue : 0.0;
	}
}

unsigned char* CFlyCap2_MFCDoc::GetProcessedPixels()
{
	return m_processedImage.GetData();
}

void CFlyCap2_MFCDoc::GetImageSize( unsigned int* pWidth, unsigned int* pHeight )
{
	/*
	//this sometimes return a expired information, so get rid of this
	 *pWidth = abs(m_bitmapInfo.bmiHeader.biWidth);
	 *pHeight = abs(m_bitmapInfo.bmiHeader.biHeight);
	 */

	//This will be called in update status bar function (in MainFrm.cpp),
	//so it must be locked before use.
	CSingleLock dataLock(&m_csRawImageData);
	dataLock.Lock();
	*pWidth = m_rawImage.GetCols();
	*pHeight = m_rawImage.GetRows();
	dataLock.Unlock();
}


Image CFlyCap2_MFCDoc::GetConvertedImage()
{
	return m_processedImage;
}

bool CFlyCap2_MFCDoc::IsGrabThreadRunning()
{
	return m_continueGrabThread;
}

void CFlyCap2_MFCDoc::OnToggleCameraControl()
{
	if ( m_camCtlDlg.IsVisible() == true )
	{
		m_camCtlDlg.Hide();
	}
	else
	{
		m_camCtlDlg.Show();
	}
}

void CFlyCap2_MFCDoc::OnFileSaveAs()
{
	Image tempImage;

	CSingleLock dataLock(&m_csRawImageData);
	dataLock.Lock();
	tempImage.DeepCopy(&m_rawImage);
	dataLock.Unlock();

	// Define the list of filters to include in the SaveAs dialog.
	const unsigned int uiNumFilters = 9;
	const CString arcsFilter[uiNumFilters] = {
		"Portable Greymap (raw image) (*.pgm)|*.pgm" ,
		"Portable Pixelmap (*.ppm)|*.ppm" ,
		"Windows Bitmap (*.bmp)|*.bmp" ,
		"Independent JPEG Group (*.jpg, *.jpeg)|*.jpg; *.jpeg" ,
		"Independent JPEG Group 2000(*.jp2)|*.jp2" ,
		"Tagged Image File Format (*.tif)|*.tif" ,
		"Portable Network Graphics (*.png)|*.png" ,
		"Raw data (*.raw)|*.raw" ,
		"All Files (*.*)|*.*" };

	CString arcsFilterToUse[uiNumFilters];

	const unsigned int MAX_COMBO_STRING = 64;
	const char ImageFormatList[uiNumFilters-1][MAX_COMBO_STRING] =
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

	CString csFilters;
	CString csTemp;
	// Keep track of which filter should be selected as default.
	// m_uiFilterIndex is set to what was previously used (0 if this is first time).
	for ( int i = 0; i < (uiNumFilters - 1); i++ )
	{
		csTemp = arcsFilter[(m_uiFilterIndex + i) % (uiNumFilters - 1)];
		if(csTemp != "")
		{
			csFilters += csTemp;
			csFilters += "|";
		}
	}
	// Always finish with All Files and a ||.
	csFilters += arcsFilter[uiNumFilters - 1];
	csFilters += "||";

	time_t rawtime;
	struct tm * timeinfo;
	time( &rawtime );
	timeinfo = localtime( &rawtime );

	char timestamp[64];
	strftime( timestamp, 64, "%Y-%m-%d-%H%M%S", timeinfo );

	char tempFilename[128];
	sprintf( tempFilename, "%u-%s", m_cameraInfo.serialNumber, timestamp );

	CSaveImageFileDialog fileDialog(
			FALSE,
			"jpeg",
			tempFilename,
			OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT,
			csFilters,
			AfxGetMainWnd() );

	PixelFormat pixelFormat = tempImage.GetPixelFormat();

	if ((pixelFormat == PIXEL_FORMAT_RAW8)  ||
			(pixelFormat == PIXEL_FORMAT_RAW12) ||
			(pixelFormat == PIXEL_FORMAT_RAW16))
	{
		if (Image::GetDefaultColorProcessing() != NO_COLOR_PROCESSING)
		{
			fileDialog.IsRawImage(true);
		}
	}

	if( fileDialog.DoModal() == IDOK )
	{
		Error error;
		Image saveImage = tempImage;

		if ((pixelFormat == PIXEL_FORMAT_RAW8)  ||
				(pixelFormat == PIXEL_FORMAT_RAW12) ||
				(pixelFormat == PIXEL_FORMAT_RAW16))
		{
			if (Image::GetDefaultColorProcessing() != NO_COLOR_PROCESSING && !fileDialog.IsSaveBayerTileSelected())
			{
				error = tempImage.Convert(PIXEL_FORMAT_BGR, &saveImage);
			}
		}

		ImageFileFormat saveImageFormat;
		CString csExt = fileDialog.GetFileExt();

		// Check file extension
		if( csExt.CompareNoCase("bmp") == 0 )
		{
			BMPOption option;
			m_uiFilterIndex = 2;
			error = saveImage.Save( fileDialog.GetPathName(), &option );
		}
		else if( csExt.CompareNoCase("ppm") == 0 )
		{
			PPMOption option;
			m_uiFilterIndex = 1;
			error = saveImage.Save( fileDialog.GetPathName(), &option );
		}
		else if( csExt.CompareNoCase("pgm") == 0 )
		{
			PGMOption option;
			m_uiFilterIndex = 0;
			error = saveImage.Save( fileDialog.GetPathName(), &option );

		}
		else if( csExt.CompareNoCase("jpeg") == 0 || csExt.CompareNoCase("jpg") == 0 )
		{
			JPEGOption option;
			m_uiFilterIndex = 3;
			error = saveImage.Save( fileDialog.GetPathName(), &option );
		}
		else if( csExt.CompareNoCase("jp2") == 0 )
		{
			JPG2Option option;
			m_uiFilterIndex = 4;
			error = saveImage.Save( fileDialog.GetPathName(), &option );
		}
		else if( csExt.CompareNoCase("tif") == 0 )
		{
			TIFFOption option;
			option.compression = TIFFOption::NONE;
			m_uiFilterIndex = 5;
			error = saveImage.Save( fileDialog.GetPathName(), &option );
		}
		else if( csExt.CompareNoCase("png") == 0 )
		{
			PNGOption option;
			m_uiFilterIndex = 6;
			error = saveImage.Save( fileDialog.GetPathName(), &option );
		}
		else if( csExt.CompareNoCase("raw") == 0 )
		{
			m_uiFilterIndex = 7;
			error = saveImage.Save( fileDialog.GetPathName(), FlyCapture2::RAW );
		}
		else
		{
			AfxMessageBox( "Invalid file type" );
		}

		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Failed to save image", error );
		}
	}
}

BOOL CFlyCap2_MFCDoc::GetPixelFormatFromVideoMode(
		VideoMode mode,
		bool stippled,
		PixelFormat* pixFormat)
{
	switch(mode)
	{
		case VIDEOMODE_640x480Y8:
		case VIDEOMODE_800x600Y8:
		case VIDEOMODE_1024x768Y8:
		case VIDEOMODE_1280x960Y8:
		case VIDEOMODE_1600x1200Y8:
			if( stippled )
			{
				*pixFormat = PIXEL_FORMAT_RAW8;
			}
			else
			{
				*pixFormat = PIXEL_FORMAT_MONO8;
			}
			break;
		case VIDEOMODE_640x480Y16:
		case VIDEOMODE_800x600Y16:
		case VIDEOMODE_1024x768Y16:
		case VIDEOMODE_1280x960Y16:
		case VIDEOMODE_1600x1200Y16:
			if( stippled )
			{
				*pixFormat = PIXEL_FORMAT_RAW16;
			}
			else
			{
				*pixFormat = PIXEL_FORMAT_MONO16;
			}
			break;
		case VIDEOMODE_640x480RGB:
		case VIDEOMODE_800x600RGB:
		case VIDEOMODE_1024x768RGB:
		case VIDEOMODE_1280x960RGB:
		case VIDEOMODE_1600x1200RGB:
			*pixFormat = PIXEL_FORMAT_RGB8;
			break;
		case VIDEOMODE_320x240YUV422:
		case VIDEOMODE_640x480YUV422:
		case VIDEOMODE_800x600YUV422:
		case VIDEOMODE_1024x768YUV422:
		case VIDEOMODE_1280x960YUV422:
		case VIDEOMODE_1600x1200YUV422:
			*pixFormat = PIXEL_FORMAT_422YUV8;
			break;
		case VIDEOMODE_160x120YUV444:
			*pixFormat = PIXEL_FORMAT_444YUV8;
			break;
		case VIDEOMODE_640x480YUV411:
			*pixFormat = PIXEL_FORMAT_411YUV8;
			break;
		case VIDEOMODE_FORMAT7:
			return FALSE;
		default:
			return FALSE;
	}
	return TRUE;
}

unsigned int CFlyCap2_MFCDoc::GetBppFromPixelFormat( PixelFormat pixelFormat )
{
	switch(pixelFormat)
	{
		case PIXEL_FORMAT_MONO8:
		case PIXEL_FORMAT_RAW8:
			return 8;
			break;
		case PIXEL_FORMAT_411YUV8:
		case PIXEL_FORMAT_MONO12:
		case PIXEL_FORMAT_RAW12:
			return 12;
			break;
		case PIXEL_FORMAT_MONO16:
		case PIXEL_FORMAT_S_MONO16:
		case PIXEL_FORMAT_422YUV8:
		case PIXEL_FORMAT_RAW16:
			return 16;
			break;
		case PIXEL_FORMAT_444YUV8:
		case PIXEL_FORMAT_RGB8:
		case PIXEL_FORMAT_BGR:
			return 24;
			break;
		case PIXEL_FORMAT_BGRU:
		case PIXEL_FORMAT_RGBU:
			return 32;
			break;
		case PIXEL_FORMAT_S_RGB16:
		case PIXEL_FORMAT_RGB16:
		case PIXEL_FORMAT_BGR16:
			return 48;
			break;
		default:
			return 0;
			break;
	}
}

void CFlyCap2_MFCDoc::OnStartImageTransfer()
{
	if ( m_pCamera->IsConnected() != true )
	{
		OnNewDocument();
		return;
	}
	Error error = m_pCamera->StartCapture();
	if( error != PGRERROR_OK )
	{
		CString csMessage;
		csMessage.Format(
				"StartCapture Failure: %s", error.GetDescription() );
		AfxMessageBox( csMessage, MB_ICONSTOP );
		return;
	}

	// Reset flag
	m_cameraIsPaused = false;

	// Start the grab thread
	m_continueGrabThread = true;
	ResetEvent(m_threadImDoneTooEvent);
	m_grabLoopThread = AfxBeginThread( ThreadGrabImage, this );

}

void CFlyCap2_MFCDoc::OnStopImageTransfer()
{
	Stop();
	m_processedImage.ReleaseBuffer();
	RedrawAllViews();//refresh screen and show PRG logo
}

bool CFlyCap2_MFCDoc::Start( PGRGuid guid )
{
	m_guid = guid;
	InterfaceType ifType;
	Error error = m_busMgr.GetInterfaceTypeFromGuid( &guid, &ifType );
	if ( error != PGRERROR_OK )
	{
		return false;
	}
	if (m_pCamera !=NULL)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if ( ifType == INTERFACE_GIGE )
	{
		m_pCamera = new GigECamera;
	}
	else
	{
		m_pCamera = new Camera;
	}

	// Connect to selected camera
	error = m_pCamera->Connect( &guid );
	if( error != PGRERROR_OK )
	{
		CString csMessage;
		csMessage.Format(
				"Connect Failure: %s", error.GetDescription() );
		AfxMessageBox( csMessage, MB_ICONSTOP );
		return false;
	}

	error = m_pCamera->GetCameraInfo( &m_cameraInfo );
	if( error != PGRERROR_OK )
	{
		CString csMessage;
		csMessage.Format(
				"CameraInfo Failure: %s", error.GetDescription() );
		AfxMessageBox( csMessage, MB_ICONSTOP );

		return false;
	}

	m_recordingDlg.StoreCamPtr(m_pCamera);

	if(m_cameraInfo.bayerTileFormat != BayerTileFormat::NONE)
	{
		// Color camera
		m_isColorCamera = true;
	}
	else
	{
		// B/W camera
		m_isColorCamera = false;
	}


	// Connect the camera control dialog to the camera object
	m_camCtlDlg.Connect( m_pCamera );

	//RegisterCallbacks();
	ForcePGRY16Mode();

	OnStartImageTransfer();


	return true;
}

bool CFlyCap2_MFCDoc::Stop()
{
	if (m_continueGrabThread == false)
	{
		return false;
	}

	if (m_recordingDlg.IsRecordingActive())
	{
		m_recordingDlg.StopRecording();
	}

	// Stop the image capture
	m_continueGrabThread=false;

	DWORD dw = WaitForSingleObject(m_threadDoneEvent,1000);
	if (dw != WAIT_OBJECT_0)
	{
		HRESULT hResult = ERROR_SUCCESS;

		if (dw == WAIT_TIMEOUT)
		{
			bool bYouAreTermiated = false;
			bYouAreTermiated = TerminateThread(m_grabLoopThread->m_hThread,0);// Force thread exit
			if ( !bYouAreTermiated )
				hResult = ::GetLastError();
			TRACE("Grab thread - force exit\n");
		}
		else
		{
			TRACE("Grab thread - has an error\n");
		}

		if ( hResult != ERROR_INVALID_HANDLE )
		{
			delete m_grabLoopThread;
		}

		m_grabLoopThread = NULL;
	}

	ASSERT(m_pCamera != NULL);
	if (m_pCamera->IsConnected())
	{
		Error error = m_pCamera->StopCapture();
		Sleep( 25 );
		SetEvent(m_threadImDoneTooEvent);
		if( error != PGRERROR_OK)
		{
			// This may fail when the camera was removed, so don't show
			// an error message

			/*csMessage.Format(
			  "Stop Failure: %s", error.GetDescription() );
			  AfxMessageBox( csMessage, MB_ICONSTOP );*/
		}

		// Reset flag
		m_cameraIsPaused = false;
	}

	RedrawAllViews();// Refresh drawing area to show the PGR logo

	// Hide the camera control dialog
	m_camCtlDlg.Hide();

	if (m_histogramDlg.IsWindowVisible() == TRUE)
	{
		m_histogramDlg.ShowWindow(SW_HIDE);
	}

	if (m_eventStatDlg.IsWindowVisible() == TRUE)
	{
		m_eventStatDlg.ShowWindow(SW_HIDE);
	}

	if (m_recordingDlg.IsWindowVisible())
	{
		m_recordingDlg.ShowWindow(SW_HIDE);
	}

	return true;
}
void CFlyCap2_MFCDoc::RegisterCallbacks()
{
	Error error;

	// Register arrival callbacks
	error = m_busMgr.RegisterCallback( &CFlyCap2_MFCDoc::OnBusArrival, ARRIVAL, this, &m_cbArrivalHandle );
	if ( error != PGRERROR_OK )
	{
		ShowErrorMessageDialog( "Failed to register callback", error );
	}

	// Register removal callbacks
	error = m_busMgr.RegisterCallback( &CFlyCap2_MFCDoc::OnBusRemoval, REMOVAL, this, &m_cbRemovalHandle );
	if ( error != PGRERROR_OK )
	{
		ShowErrorMessageDialog( "Failed to register callback", error );
	}

	// Register reset callbacks
	error = m_busMgr.RegisterCallback( &CFlyCap2_MFCDoc::OnBusReset, BUS_RESET, this, &m_cbResetHandle );
	if ( error != PGRERROR_OK )
	{
		ShowErrorMessageDialog( "Failed to register callback", error );
	}
}
void CFlyCap2_MFCDoc::UnregisterCallbacks()
{
	Error error;

	// Unregister arrival callback
	error = m_busMgr.UnregisterCallback( m_cbArrivalHandle );
	if ( error != PGRERROR_OK )
	{
		ShowErrorMessageDialog( "Failed to unregister callback", error );
	}

	// Unregister removal callback
	error = m_busMgr.UnregisterCallback( m_cbRemovalHandle );
	if ( error != PGRERROR_OK )
	{
		ShowErrorMessageDialog( "Failed to unregister callback", error );
	}

	// Unregister reset callback
	error = m_busMgr.UnregisterCallback( m_cbResetHandle );
	if ( error != PGRERROR_OK )
	{
		ShowErrorMessageDialog( "Failed to unregister callback", error );
	}
}


void CFlyCap2_MFCDoc::OnBusReset( void* pParam, unsigned int serialNumber )
{
	CFlyCap2_MFCDoc* pDoc =  static_cast<CFlyCap2_MFCDoc*>(pParam);
	pDoc->AddEvent(NUMBER_OF_BUS_RESETS);
}

void CFlyCap2_MFCDoc::OnBusArrival( void* pParam, unsigned int serialNumber )
{
	CFlyCap2_MFCDoc* pDoc =  static_cast<CFlyCap2_MFCDoc*>(pParam);
	pDoc->m_arrQueue.push(serialNumber);
	pDoc->OnBusArrivalEvent();
}


void CFlyCap2_MFCDoc::OnBusRemoval( void* pParam , unsigned int serialNumber)
{
	CFlyCap2_MFCDoc* pDoc =  static_cast<CFlyCap2_MFCDoc*>(pParam);
	pDoc->m_remQueue.push(serialNumber);
	pDoc->OnBusRemovalEvent();
}

void CFlyCap2_MFCDoc::OnBusRemovalEvent()
{
	unsigned int serialNumber;
	serialNumber = m_remQueue.front();
	m_remQueue.pop();
	if( m_cameraInfo.serialNumber == serialNumber )
	{
		Stop();
		m_pCamera->Disconnect();
	}
	AddEvent(NUMBER_OF_BUS_REMOVALS);
}

void CFlyCap2_MFCDoc::OnBusArrivalEvent()
{
	unsigned int serialNumber;
	serialNumber = m_arrQueue.front();
	m_arrQueue.pop();
	AddEvent(NUMBER_OF_BUS_ARRIVALS);
	// Currently on Arrival all camera handles get updated.
	// We need to stop the stream just like in the OnBusRemoval.
	// TODO: once proper bus reset handlign is implemented we can
	// remove this stop here.
}

void CFlyCap2_MFCDoc::ForcePGRY16Mode()
{
	Error error;
	const unsigned int k_imageDataFmtReg = 0x1048;
	unsigned int value = 0;
	error = m_pCamera->ReadRegister( k_imageDataFmtReg, &value );
	if ( error != PGRERROR_OK )
	{
		// Error
	}

	value &= ~(0x1 << 0);

	error = m_pCamera->WriteRegister( k_imageDataFmtReg, value );
	if ( error != PGRERROR_OK )
	{
		// Error
	}
}

bool CFlyCap2_MFCDoc::IsOpenGLEnabled()
{
	return m_enableOpenGL;
}

bool CFlyCap2_MFCDoc::IsGDIEnabled()
{
	return m_enableGDI;
}

bool CFlyCap2_MFCDoc::IsD2DEnabled()
{
	return m_enableD2D;
}

unsigned int CFlyCap2_MFCDoc::GetBytePerPixel()
{
	return (m_processedImage.GetBitsPerPixel() / 8);
}

void CFlyCap2_MFCDoc::ShowErrorMessageDialog(char* mainTxt, Error error, bool detailed)
{
	char tempStr[1024];
	if ( detailed == true )
	{
		sprintf(
				tempStr,
				"Source: %s(%u) Built: %s - %s\n",
				error.GetFilename(),
				error.GetLine(),
				error.GetBuildDate(),
				error.GetDescription() );

		Error cause = error.GetCause();
		while( cause.GetType() != PGRERROR_UNDEFINED )
		{
			sprintf(
					tempStr,
					"+-> From: %s(%d) Built: %s - %s\n",
					cause.GetFilename(),
					cause.GetLine(),
					cause.GetBuildDate(),
					cause.GetDescription() );
			cause = cause.GetCause();
		}
	}
	else
	{
		sprintf(tempStr,error.GetDescription());
	}
	CString csMessage;
	csMessage.Format(
			"%s: %s", mainTxt,tempStr  );
	AfxMessageBox( csMessage, MB_ICONSTOP );
}

void CFlyCap2_MFCDoc::UncheckAllColorProcessingAlgorithm()
{
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	//Go to color processing algorithm menu
	pMenu = pMenu->GetSubMenu(2); //go to setting menu
#ifdef _DEBUG
	//validate position
	if (pMenu == NULL)
	{
		//Bug: Menu item not found
		//It means the menu item has been changed by others
		//this will cause some problems of updating menu item
		//to resolve this you need you open resource view of IDR_MAINFRAME
		//put the "Color processing algorithm" position to the first in setting menu
		//and put the "Setting" position to the 3rd in main menu
		DebugBreak();
	}
#endif
	pMenu = pMenu->GetSubMenu(0); //go to color processing algorithm menu
#ifdef _DEBUG
	//validate menu item is right or not
	if (pMenu == NULL || pMenu->GetMenuItemID(0) != ID_COLORPROCESSINGALGORITHM_NONE)
	{
		//Bug: this item is not color processing algorithm
		//It means the menu item has been changed by others
		//this will cause some problems of updating menu item
		//to resolve this you need you open resource view of IDR_MAINFRAME
		//put the "Color processing algorithm" position to the first in setting menu
		//and put the "Setting" position to the 3rd in main menu
		DebugBreak();
	}
#endif
	for (int i = 0; i < 7;i++)
	{
		pMenu->CheckMenuItem(i,MF_UNCHECKED | MF_BYPOSITION);
	}
}

void CFlyCap2_MFCDoc::RefreshColorProcessingAlgorithm()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();

	FlyCapture2::ColorProcessingAlgorithm currentAlgorithm = Image::GetDefaultColorProcessing();

	switch (currentAlgorithm)
	{
		case NO_COLOR_PROCESSING:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_NONE,MF_CHECKED | MF_BYCOMMAND);
			break;
		case NEAREST_NEIGHBOR:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_NEARESTNEIGHBOR,MF_CHECKED | MF_BYCOMMAND);
			break;
		case EDGE_SENSING:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_EDGESENSING,MF_CHECKED | MF_BYCOMMAND);
			break;
		case HQ_LINEAR:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_HQLINEAR,MF_CHECKED | MF_BYCOMMAND);
			break;
		case DIRECTIONAL_FILTER:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_DIRECTIONALFILTER,MF_CHECKED | MF_BYCOMMAND);
			break;
		case WEIGHTED_DIRECTIONAL_FILTER:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_WEIGHTEDDIRECTIONALFILTER, MF_CHECKED | MF_BYCOMMAND);
			break;
		case RIGOROUS:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_RIGOROUS,MF_CHECKED | MF_BYCOMMAND);
			break;
		case IPP:
			pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_IPP,MF_CHECKED | MF_BYCOMMAND);
			break;
		default:
			break;
	}
}

void CFlyCap2_MFCDoc::OnColorAlgorithmNone()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_NONE,MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(NO_COLOR_PROCESSING);
}

void CFlyCap2_MFCDoc::OnColorAlgorithmNearestNeighbor()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_NEARESTNEIGHBOR,MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(NEAREST_NEIGHBOR);
}

void CFlyCap2_MFCDoc::OnColorAlgorithmEdgeSensing()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_EDGESENSING,MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(EDGE_SENSING);
}

void CFlyCap2_MFCDoc::OnColorAlgorithmHQLinear()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_HQLINEAR,MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(HQ_LINEAR);
}

void CFlyCap2_MFCDoc::OnColorAlgorithmDirectionalFilter()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_DIRECTIONALFILTER,MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(DIRECTIONAL_FILTER);
}

void CFlyCap2_MFCDoc::OnColorAlgorithmWeightedDirectionalFilter()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_WEIGHTEDDIRECTIONALFILTER, MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(WEIGHTED_DIRECTIONAL_FILTER);
}

void CFlyCap2_MFCDoc::OnColorAlgorithmRigorous()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_RIGOROUS,MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(RIGOROUS);
}

void CFlyCap2_MFCDoc::OnColorAlgorithmIPP()
{
	UncheckAllColorProcessingAlgorithm();
	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->CheckMenuItem(ID_COLORPROCESSINGALGORITHM_IPP,MF_CHECKED | MF_BYCOMMAND);
	Image::SetDefaultColorProcessing(IPP);
}
void CFlyCap2_MFCDoc::OnUpdateStartImageTransferBtn(CCmdUI *pCmdUI)
{
	if (m_isSelectingNewCamera == false)
	{
		pCmdUI->Enable(m_continueGrabThread ? FALSE : TRUE );
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CFlyCap2_MFCDoc::OnUpdateFileStopImageTransferBtn(CCmdUI *pCmdUI)
{
	if (m_isSelectingNewCamera == false)
	{
		pCmdUI->Enable(m_continueGrabThread ? TRUE : FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CFlyCap2_MFCDoc::EnableOpenGL()
{
	m_enableOpenGL = true;
	m_enableGDI = false;
	m_enableD2D = false;
}

void CFlyCap2_MFCDoc::EnableGDI()
{
	m_enableGDI = true;
	m_enableD2D = false;
	m_enableOpenGL = false;
}

void CFlyCap2_MFCDoc::EnableD2D()
{
	m_enableD2D = true;
	m_enableOpenGL = false;
	m_enableGDI = false;
}

void  CFlyCap2_MFCDoc::SetD2DSupport(bool isSupported)
{
	m_supportD2D = isSupported;
}

void CFlyCap2_MFCDoc::OnUpdateViewEnableOpenGL(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_enableOpenGL ? TRUE:FALSE);
}

void CFlyCap2_MFCDoc::OnUpdateMenuItemGDI(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_enableGDI ? TRUE:FALSE);
}

void CFlyCap2_MFCDoc::OnUpdateMenuItemDirect2D(CCmdUI *pCmdUI)
{
#ifdef DIRECT2D_SUPPORT
	if (m_supportD2D == false)
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->Enable(FALSE);
		pCmdUI->SetText("Direct2D (Requires Windows 7 and up)");
	}
	else
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_enableD2D ? TRUE:FALSE);
		pCmdUI->SetText("Direct2D");
	}
#else
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
	pCmdUI->SetText("Direct2D (Requires Windows 7 and up)");
#endif
}

InformationPane::InformationPaneStruct CFlyCap2_MFCDoc::GetRawImageInformation()
{
	Error error;
	InformationPane::InformationPaneStruct infoStruct;
	infoStruct.fps.requestedFrameRate = GetRequestedFrameRate();
	infoStruct.fps.processedFrameRate = GetProcessedFrameRate();
	infoStruct.fps.receivedFrameRate = GetReceivedFrameRate();
	if (m_pCamera == NULL)
	{
		return infoStruct;
	}

	CSingleLock dataLock(&m_csRawImageData);
	dataLock.Lock();

	// Set up the timestamp data
	infoStruct.timestamp = m_rawImage.GetTimeStamp();

	// Set up the image info data
	m_rawImage.GetDimensions(
			&infoStruct.imageInfo.height,
			&infoStruct.imageInfo.width,
			&infoStruct.imageInfo.stride,
			&infoStruct.imageInfo.pixFmt );

	// Set up the embedded image info data
	const unsigned int k_frameInfoReg = 0x12F8;
	unsigned int frameInfoRegVal = 0;
	error = m_pCamera->ReadRegister( k_frameInfoReg, &frameInfoRegVal );
	if (error == PGRERROR_OK &&
			(frameInfoRegVal >> 31) != 0)
	{
		ImageMetadata metadata = m_rawImage.GetMetadata();
		dataLock.Unlock();

		const int k_numEmbeddedInfo = 10;
		unsigned int* pEmbeddedInfo = infoStruct.embeddedInfo.arEmbeddedInfo;

		for (int i=0; i < k_numEmbeddedInfo; i++)
		{
			switch (i)
			{
				case 0: pEmbeddedInfo[i] = metadata.embeddedTimeStamp; break;
				case 1: pEmbeddedInfo[i] = metadata.embeddedGain; break;
				case 2: pEmbeddedInfo[i] = metadata.embeddedShutter; break;
				case 3: pEmbeddedInfo[i] = metadata.embeddedBrightness; break;
				case 4: pEmbeddedInfo[i] = metadata.embeddedExposure; break;
				case 5: pEmbeddedInfo[i] = metadata.embeddedWhiteBalance; break;
				case 6: pEmbeddedInfo[i] = metadata.embeddedFrameCounter; break;
				case 7: pEmbeddedInfo[i] = metadata.embeddedStrobePattern; break;
				case 8: pEmbeddedInfo[i] = metadata.embeddedGPIOPinState; break;
				case 9: pEmbeddedInfo[i] = metadata.embeddedROIPosition; break;
			}
		}
	}
	else
	{
		dataLock.Unlock();
	}

	// Set up the diagnostics info
	const unsigned int k_frameSkippedReg = 0x12C0;
	unsigned int frameSkippedRegVal = 0;
	error = m_pCamera->ReadRegister( k_frameSkippedReg, &frameSkippedRegVal );
	if (error != PGRERROR_OK  ||
			m_cameraInfo.interfaceType != INTERFACE_USB3 ||
			m_cameraInfo.iidcVer < 132 ||
			(m_cameraInfo.iidcVer >= 132 && (frameSkippedRegVal & 0x80000000) == 0))
	{
		infoStruct.diagnostics.skippedFrames = -1;
	}
	else
	{
		int skippedImages = frameSkippedRegVal & 0x7FFFFFFF;
		infoStruct.diagnostics.skippedFrames = skippedImages;
		int newEvents = skippedImages - m_previousSkippedImages;
		if (newEvents > 0)
		{
			for (int i = 0; i < newEvents; i++)
			{
				AddEvent(SKIPPED_IMAGES);
			}
		}
		m_previousSkippedImages = skippedImages;
	}

	// Query Linker Errors from host
	const unsigned int k_linkerErrorCountReg = 0x12C4;
	unsigned int linkerErrorRegVal = 0;
	error = m_busMgr.GetUsbLinkInfo(m_guid, &linkerErrorRegVal);
	if (error != PGRERROR_OK  || m_cameraInfo.interfaceType != INTERFACE_USB3)
	{
		infoStruct.diagnostics.linkerErrors = -1;
	}
	else
	{
		unsigned short int linkerErrorCount = linkerErrorRegVal;
		infoStruct.diagnostics.linkerErrors = linkerErrorCount;
		int newEvents = linkerErrorCount - m_previousLinkerErrorCount;
		if (newEvents > 0)
		{
			for (int i = 0; i < newEvents; i++)
			{
				AddEvent(LINKER_ERRORS);
			}
		}
		m_previousLinkerErrorCount = linkerErrorCount;
	}

	const unsigned int k_linkRecoveryCountReg = 0x12C4;
	unsigned int linkRecoveryCountRegVal = 0;
	error = m_pCamera->ReadRegister( k_linkRecoveryCountReg, &linkRecoveryCountRegVal );
	if (error != PGRERROR_OK  ||
			m_cameraInfo.interfaceType != INTERFACE_USB3 ||
			m_cameraInfo.iidcVer < 132 ||
			(m_cameraInfo.iidcVer >= 132 && (linkRecoveryCountRegVal & 0x80000000) == 0))
	{
		infoStruct.diagnostics.linkRecoveryCount = -1;
	}
	else
	{
		int recoveryCount = linkRecoveryCountRegVal & 0x7FFFFFFF;
		infoStruct.diagnostics.linkRecoveryCount = recoveryCount;
		int newEvents = recoveryCount - m_previousRecoveryCount;
		if (newEvents > 0)
		{
			for (int i = 0; i < newEvents; i++)
			{
				AddEvent(RECOVERY_COUNT);
			}
		}
		m_previousRecoveryCount = recoveryCount;
	}

	const unsigned int k_transmitFailureReg = 0x12FC;
	unsigned int transmitFailureRegVal = 0;
	error = m_pCamera->ReadRegister( k_transmitFailureReg, &transmitFailureRegVal );
	if ( error != PGRERROR_OK  ||
			(m_cameraInfo.iidcVer >= 132 && (transmitFailureRegVal & 0x80000000) == 0 ))
	{
		infoStruct.diagnostics.transmitFailures = -1;
	}
	else
	{
		int transmitFailuresValue = transmitFailureRegVal & 0x7FFFFFFF;
		infoStruct.diagnostics.transmitFailures = transmitFailuresValue;
		int newFailures = transmitFailuresValue - m_previousTransmitFailures;
		if (newFailures > 0)
		{
			for (int i = 0; i < newFailures; i++)
			{
				AddEvent(TRANSMIT_FAILURES);
			}
		}
		m_previousTransmitFailures = transmitFailuresValue;
	}

	const unsigned int k_initializeTimeReg = 0x12E0;
	unsigned int initializeTimeRegVal = 0;
	error = m_pCamera->ReadRegister( k_initializeTimeReg, &initializeTimeRegVal );
	if ( error != PGRERROR_OK )
	{
		infoStruct.diagnostics.timeSinceInitialization = "";
	}
	else
	{
		unsigned int numHours = 0;
		unsigned int numMins = 0;
		unsigned int numSeconds = 0;

		ParseTimeRegister( initializeTimeRegVal, numHours, numMins, numSeconds );

		char timeStr[512];
		sprintf(
				timeStr,
				"%uh %um %us",
				numHours,
				numMins,
				numSeconds );

		infoStruct.diagnostics.timeSinceInitialization = timeStr;
	}

	const unsigned int k_busResetTimeReg = 0x12E4;
	unsigned int busResetTimeRegVal = 0;
	error = m_pCamera->ReadRegister( k_busResetTimeReg, &busResetTimeRegVal );
	if ( error != PGRERROR_OK )
	{
		infoStruct.diagnostics.timeSinceLastBusReset = "";
	}
	else
	{
		unsigned int numHours = 0;
		unsigned int numMins = 0;
		unsigned int numSeconds = 0;

		ParseTimeRegister( busResetTimeRegVal, numHours, numMins, numSeconds );

		char timeStr[512];
		sprintf(
				timeStr,
				"%uh %um %us",
				numHours,
				numMins,
				numSeconds );

		infoStruct.diagnostics.timeSinceLastBusReset = timeStr;
	}

	// Query and update packet resend requested
	FlyCapture2::CameraStats stats;
	error = m_pCamera->GetStats(&stats);
	if ( error != PGRERROR_OK )
	{
		infoStruct.diagnostics.packetResendReceived = m_previousPacketResendRequested;
	}
	else
	{
		infoStruct.diagnostics.packetResendRequested = stats.numResendPacketsRequested;
		int newEvent = stats.numResendPacketsRequested - m_previousPacketResendRequested;
		if(newEvent > 0)
		{
			for (int i = 0; i < newEvent; i++)
			{
				AddEvent(NUMBER_OF_PACKET_RESEND_REQUESTED);
			}
		}
		m_previousPacketResendRequested = stats.numResendPacketsRequested;
	}

	//Update packet resend received
	if ( error != PGRERROR_OK )
	{
		infoStruct.diagnostics.packetResendReceived = m_previousPacketResendReceived;
	}
	else
	{
		infoStruct.diagnostics.packetResendReceived = stats.numResendPacketsReceived;
		int newEvent = stats.numResendPacketsReceived - m_previousPacketResendReceived;
		if(newEvent > 0)
		{
			for (int i = 0; i < newEvent; i++)
			{
				AddEvent(NUMBER_OF_PACKET_RESEND_RECEIVED);
			}
		}
		m_previousPacketResendReceived = stats.numResendPacketsReceived;
	}
	return infoStruct;
}

void CFlyCap2_MFCDoc::ParseTimeRegister(
		unsigned int timeRegVal,
		unsigned int& hours,
		unsigned int& mins,
		unsigned int& seconds )
{
	hours = timeRegVal / (60 * 60);
	mins = (timeRegVal - (hours * 60 * 60)) / 60;
	seconds = timeRegVal - (hours * 60 * 60) - (mins * 60);
}

void CFlyCap2_MFCDoc::OnViewEventStat()
{
	ToggleEventStatDialog();
}
void CFlyCap2_MFCDoc::ToggleEventStatDialog()
{
	if (m_eventStatDlg.IsWindowVisible() == TRUE)
	{
		m_eventStatDlg.ShowWindow(SW_HIDE);
	}
	else
	{
		m_eventStatDlg.ShowWindow(SW_SHOW);
	}
}

void CFlyCap2_MFCDoc::AddEvent(EventType eventType)
{
	m_eventStatDlg.AddEvent(eventType);
}

void CFlyCap2_MFCDoc::OnToggleHistgram()
{
	if (m_histogramDlg.IsWindowVisible() == TRUE)
	{
		m_histogramDlg.ShowWindow(SW_HIDE);
		m_histogramDlg.StopUpdate();
	}
	else
	{
		m_histogramDlg.StartUpdate();
		m_histogramDlg.ShowWindow(SW_SHOW);
	}
}

void CFlyCap2_MFCDoc::OnToggleRecorder()
{
	if (m_recordingDlg.IsWindowVisible())
	{
		m_recordingDlg.ShowWindow(SW_HIDE);
	}
	else
	{
		if (m_continueGrabThread)
		{
			m_recordingDlg.ShowWindow(SW_SHOW);
			m_recordingDlg.StoreCamPtr(m_pCamera);
		}
		else
		{
			AfxMessageBox( "Please start the camera before opening the recording dialog.", MB_ICONINFORMATION );
		}
	}
}

bool CFlyCap2_MFCDoc::HasBadEventRecently()
{
	if (m_eventStatDlg.IsWindowVisible() == FALSE)
	{
		// if the event data window is visible
		// the update function will be automatically
		// called in EventStatDialog::OnTimer();
		// but if it is not visible, we need to
		// update event data manually in order to
		// check recent bad event
		m_eventStatDlg.UpdateEventsData();
	}
	return m_eventStatDlg.HasBadEventRecently();
}
void CFlyCap2_MFCDoc::OnUpdateCameraControlToggleButton(CCmdUI *pCmdUI)
{
	if ( m_pCamera->IsConnected() == true )
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_camCtlDlg.IsVisible()?TRUE:FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
}

void CFlyCap2_MFCDoc::OnUpdateHistgramBtn(CCmdUI *pCmdUI)
{
	if ( m_pCamera->IsConnected() == true )
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_histogramDlg.IsWindowVisible());
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
}

void CFlyCap2_MFCDoc::OnUpdateRecordingBtn(CCmdUI *pCmdUI)
{
	if (m_pCamera->IsConnected() && m_continueGrabThread && !GetPauseStatus())
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_recordingDlg.IsWindowVisible());
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
}

void CFlyCap2_MFCDoc::OnUpdateEventStatsBtn(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_eventStatDlg.IsWindowVisible());
}

void CFlyCap2_MFCDoc::OnUpdateSaveAsBtn(CCmdUI *pCmdUI)
{
	if (m_pCamera->IsConnected() && m_continueGrabThread)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CFlyCap2_MFCDoc::OnSettingsTogglecamerapropertygrid()
{
#ifdef GENICAM
	// TODO: Add your command handler code here
	if ( m_propGridDlg.IsConnected() && m_propGridDlg.IsVisible() )
	{
		m_propGridDlg.Hide();
	}
	else
	{
		/*if(m_cameraInfo.interfaceType == INTERFACE_USB3)
		  {
		// Special case for USB3 where XML loading from disk is enforced for now
		if( m_xmlPathDlg.m_benableXmlLoading && m_xmlPathDlg.m_xmlpath.GetLength()>0)
		{
		}
		else
		{
		CString csMessage;
		csMessage.Format(
		"Please specify path to XML in advance for USB3 cameras.");
		AfxMessageBox( csMessage, MB_ICONSTOP );
		return;
		}
		}*/

		if( !m_propGridDlg.IsConnected() && (m_cameraInfo.interfaceType == INTERFACE_USB3 || m_cameraInfo.interfaceType == INTERFACE_GIGE))
		{
			if(m_xmlPathDlg.m_benableXmlLoading)
			{
				m_propGridDlg.Connect(m_pCamera, m_xmlPathDlg.m_xmlpath);
			}
			else
			{
				m_propGridDlg.Connect(m_pCamera);
			}
		}
		m_propGridDlg.RefreshProperties();
		m_propGridDlg.SetTitle("");
		m_propGridDlg.Show();
	}
#endif
}


void CFlyCap2_MFCDoc::OnUpdateSettingsTogglecamerapropertygrid(CCmdUI *pCmdUI)
{
#ifdef GENICAM
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && (m_cameraInfo.interfaceType == INTERFACE_USB3 || m_cameraInfo.interfaceType == INTERFACE_GIGE) )
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_propGridDlg.IsVisible()?TRUE:FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
#else
	// remove this menu entry if GENICAM was not supported
	pCmdUI->m_pMenu->DeleteMenu(pCmdUI->m_nID, MF_BYCOMMAND);
#endif
}


void CFlyCap2_MFCDoc::OnSettingsSetxmlpath()
{
#ifdef GENICAM
	// TODO: Add your command handler code here
	if ( m_xmlPathDlg.IsWindowVisible() == true )
	{
		m_xmlPathDlg.ShowWindow(SW_HIDE);
	}
	else
	{
		m_xmlPathDlg.ShowWindow(SW_SHOW);
	}
#endif
}


void CFlyCap2_MFCDoc::OnUpdateSettingsSetxmlpath(CCmdUI *pCmdUI)
{
#ifdef GENICAM
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && (m_cameraInfo.interfaceType == INTERFACE_USB3 || m_cameraInfo.interfaceType == INTERFACE_GIGE) )
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_xmlPathDlg.IsWindowVisible()?TRUE:FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
#else
	// Remove this menu entry if GENICAM was not supported
	pCmdUI->m_pMenu->DeleteMenu(pCmdUI->m_nID, MF_BYCOMMAND);
#endif
}

void CFlyCap2_MFCDoc::CheckCameraPower()
{
	if(IsGrabThreadRunning()&&m_camCtlDlg.IsVisible())
	{
		unsigned int powerReg;
		unsigned int PowerInqReg;

		// Make sure camera supports power control
		Error error = m_pCamera->ReadRegister(0x400, &PowerInqReg);

		// Only proceed if there was no error and power control was supported
		if ((error == PGRERROR_OK) && ((PowerInqReg & 0x00008000) != 0))
		{
			error = m_pCamera->ReadRegister(0x610, &powerReg);
			if(error == PGRERROR_OK)
			{
				powerReg = powerReg>>31;
				if(powerReg == 0)
				{
					Stop();
				}
			}
		}
	}
}

void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmNone(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 ||m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}

}


void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmNearestneighbor(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 ||m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmEdgesensing(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 ||m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmHqlinear(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 ||m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmDirectionalfilter(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 ||m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmWeightedDirectionalfilter(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmRigorous(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 ||m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CFlyCap2_MFCDoc::OnUpdateColorprocessingalgorithmIpp(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_pCamera->IsConnected() == true && m_isColorCamera && m_rawPixelFormat != NULL && (m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW12 || m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW16 ||m_rawPixelFormat == FlyCapture2::PixelFormat::PIXEL_FORMAT_RAW8) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CFlyCap2_MFCDoc::OnPauseimagetransfer()
{
	// TODO: Add your command handler code here
	if( GetPauseStatus() )
	{
		Error err = m_pCamera->StartCapture();
		// Error code is not checked as sometimes
		// although camera was started correctly,
		// an error was returned.
		m_cameraIsPaused = false;
	}
	else
	{
		Error err = m_pCamera->StopCapture();
		// Error code is not checked as sometimes
		// although camera was stopped correctly,
		// an error was returned.
		m_cameraIsPaused = true;
	}
}


void CFlyCap2_MFCDoc::OnUpdatePauseimagetransfer(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_pCamera->IsConnected() && m_continueGrabThread && !m_recordingDlg.IsRecordingActive())
	{
		if(GetPauseStatus())
		{
			pCmdUI->Enable(TRUE);
			pCmdUI->SetCheck(TRUE);
		}
		else
		{
			pCmdUI->Enable(TRUE);
			pCmdUI->SetCheck(FALSE);
		}
	}
	else
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
}

bool CFlyCap2_MFCDoc::GetPauseStatus()
{
	return m_cameraIsPaused;
}
