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
#include <errno.h>
#include <Psapi.h>
#include "FlyCap2_MFC.h"
#include "RecordingDialog.h"


// RecordingDialog dialog

const unsigned int ONE_MEG = 1024 * 1024;
const unsigned int TWO_GIG = ONE_MEG * 1024 * 2;

const char RecordButtonStrings[][MAX_PATH] =
{
	"Start Recording",
	"Stop Recording",
	"Abort Saving",
	"Start Recording",
	"Stopping Recorder"
};

const char StatusOutputStrings[][MAX_PATH] =
{
	"Recording is stopped",
	"Recording is active",
	"Processing buffered images...",
	"Recording is stopped",
	"Stopping. Please Wait..."
};

IMPLEMENT_DYNAMIC(RecordingDialog, CDialog)


	RecordingDialog::RecordingDialog(CWnd* pParent /*=NULL*/)
: CDialog(RecordingDialog::IDD, pParent)
{
	m_intervalExpiredFlag = FALSE;
	m_durationExpiredFlag = FALSE;
	m_recorderTimerDuration = NULL;
	m_recorderTimerInterval = NULL;
	m_saveFrameLoopThread = NULL;
	m_currRecordingState = STOPPED;
}

RecordingDialog::~RecordingDialog()
{

}

void RecordingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NUM_FRAMES, m_edit_NumFrames);
	DDX_Control(pDX, IDC_EDIT_NTH_FRAMES, m_edit_NthFrame);
	DDX_Control(pDX, IDC_EDIT_NUM_SECONDS, m_edit_NumSeconds);
	DDX_Control(pDX, IDC_EDIT_NTH_SECONDS, m_edit_NthSecond);
	DDX_Control(pDX, IDC_STATIC_FRAME_COUNTER, m_static_FrameCounter);
	DDX_Control(pDX, IDC_TAB_OUTPUT_TYPE, m_tabCtrl_OutputType);

	DDX_Control(pDX, IDC_RADIO_NUM_FRAMES, m_radio_NumFrames);
	DDX_Control(pDX, IDC_RADIO_NTH_FRAME, m_radio_NthFrame);
	DDX_Control(pDX, IDC_RADIO_NUM_SECONDS, m_radio_NumSeconds);
	DDX_Control(pDX, IDC_RADIO_NTH_SECONDS, m_radio_NthSecond);
	DDX_Control(pDX, IDC_EDIT_NTH_TOTAL_FRAMES, m_edit_NthTotalFrames);
	DDX_Control(pDX, IDC_EDIT_NTH_TOTAL_SECONDS, m_edit_NthTotalSeconds);
	DDX_Control(pDX, IDC_BUTTON_START_STOP_VIDEO_RECORD, m_btn_StartStop);
	DDX_Control(pDX, IDC_EDIT_SAVE_FILE_PATH, m_edit_SaveFilePath);
	DDX_Control(pDX, IDC_STATIC_SAVE_COUNTER, m_static_savedImageCount);
	DDX_Control(pDX, IDCANCEL, m_btn_close);
	DDX_Control(pDX, IDC_CHK_CAPTURE_CORRUPT_FRAMES, m_chk_captureCorruptFrames);
	DDX_Control(pDX, IDC_STATIC_BUFFERED_COUNTER, m_static_bufferedCounter);
	DDX_Control(pDX, IDC_STATIC_AVAILABLE_MEMORY, m_static_availableMemory);
	DDX_Control(pDX, IDC_STATIC_BUFFERED_MODE_TEXT, m_static_bufferedModeText);
	DDX_Control(pDX, IDC_STATIC_AVAILABLE_MEMORY_TEXT, m_static_AvailableMemText);
	DDX_Control(pDX, IDC_STATIC_TOTAL_MEMORY_TEXT, m_static_TotalMemText);
	DDX_Control(pDX, IDC_STATIC_TOTAL_MEMORY, m_static_totalMemory);
	DDX_Control(pDX, IDC_STATIC_MEMORY_LOAD, m_static_memoryLoad);
	DDX_Control(pDX, IDC_STATIC_STATUS_OUTPUT, m_static_statusOutput);
	DDX_Control(pDX, IDC_RADIO_BUFFERED_MODE, m_radio_bufferedMode);
	DDX_Control(pDX, IDC_RADIO_STREAMING_MODE, m_radio_streamingMode);
	DDX_Control(pDX, IDC_STATIC_CORRUPT_FRAME_COUNTER, m_static_CorruptFrameCounter);
}


	BEGIN_MESSAGE_MAP(RecordingDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &RecordingDialog::OnBnClickedButtonBrowse)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OUTPUT_TYPE, &RecordingDialog::OnTcnSelchangeTabOutputType)
	ON_BN_CLICKED(IDC_RADIO_NUM_FRAMES, &RecordingDialog::OnBnClickedRadioNumFrames)
	ON_BN_CLICKED(IDC_RADIO_NTH_FRAME, &RecordingDialog::OnBnClickedRadioNthFrame)
	ON_BN_CLICKED(IDC_RADIO_NUM_SECONDS, &RecordingDialog::OnBnClickedRadioNumSeconds)
	ON_BN_CLICKED(IDC_RADIO_NTH_SECONDS, &RecordingDialog::OnBnClickedRadioNthSeconds)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_START_STOP_VIDEO_RECORD, &RecordingDialog::OnBnClickedButtonStartStopVideoRecord)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL RecordingDialog::OnInitDialog()
{
	if (!CDialog::OnInitDialog())
	{
		MessageBox("Failed to initialize Recording Dialog");
		return FALSE;
	}

	if (m_tabCtrl_OutputType.InsertItem(0, "Images") == -1)
	{
		MessageBox("Failed to insert Image Type tab page");
		return FALSE;
	}

	if (m_tabCtrl_OutputType.InsertItem(1, "Videos") == -1)
	{
		MessageBox("Failed to insert Video Type tab page");
		return FALSE;
	}

	if (m_imageRecordingPage.Create(IDD_TABPAGE_IMAGE_RECORD, &m_tabCtrl_OutputType) == FALSE)
	{
		MessageBox("Failed to create Image Type tab page");
		return FALSE;
	}

	if (m_videoRecordingPage.Create(IDD_TABPAGE_VIDEO_RECORD, &m_tabCtrl_OutputType) == FALSE)
	{
		MessageBox("Failed to create Video Type tab page");
		return FALSE;
	}

	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	m_tabCtrl_OutputType.GetClientRect(&tabRect);
	m_tabCtrl_OutputType.GetItemRect(0, &itemRect);
	nX  = itemRect.left;
	nY  = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 2;
	nYc = tabRect.bottom - nY - 2;

	m_imageRecordingPage.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	m_videoRecordingPage.SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);

	m_radio_NumFrames.SetCheck(BST_CHECKED);
	m_edit_NumFrames.SetWindowText("0");
	m_edit_SaveFilePath.SetWindowText("C:\\tmp\\fc2_save");

	m_radio_bufferedMode.SetCheck(BST_CHECKED);

	m_frameCounter = 0;
	m_corruptFrameCounter = 0;
	m_streamingFrameCounter = 0;
	m_savedImageCounter = 0;
#ifndef _WIN64
	m_static_bufferedModeText.SetWindowText("Frames are buffered in physical memory while recording. Recording will stop if process memory usage hits 80%");
	m_static_TotalMemText.SetWindowText("Total Process Memory:");
	m_static_AvailableMemText.SetWindowText("Available Process Memory:");
#endif
	UpdateSavingOptions();
	EnableControls();

	return TRUE;
}

// RecordingDialog message handlers

void RecordingDialog::OnBnClickedButtonBrowse()
{
	CFileDialog browseDialog(FALSE, NULL, "fc2_save", 0, NULL, 0);

	if(browseDialog.DoModal() == IDOK)
	{
		m_saveFilename = browseDialog.GetPathName();
		m_edit_SaveFilePath.SetWindowText(m_saveFilename);
	}
}

BOOL RecordingDialog::IsRecordingActive()
{
	RecorderState currState = GetRecorderState();

	return ((currState == STARTED)  ||
			(currState == STOPPING) ||
			(currState == ABORT_SAVING));
}

BOOL RecordingDialog::BufferFrame(Image* image)
{
	if (m_radio_bufferedMode.GetCheck())
	{
		// if memory usage above threshold, stop saving
#ifdef _WIN64
		const float MAX_PERCENT = 95.0;
		MEMORYSTATUSEX memStatus;
		memStatus.dwLength = sizeof(MEMORYSTATUSEX);

		GlobalMemoryStatusEx(&memStatus);
		if (memStatus.dwMemoryLoad >= MAX_PERCENT)
		{
			ChangeState(SAVING);
			return FALSE;
		}
#else
		const float MAX_PERCENT = 0.8;
		HANDLE procHandle = GetCurrentProcess();
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(procHandle, &pmc, sizeof(pmc));

		MEMORYSTATUSEX memStatus;
		memStatus.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memStatus);

		DWORDLONG availMemory_32bit = 0;
		DWORDLONG totalMemory_32bit = 0;

		if (memStatus.ullAvailPhys > (TWO_GIG - pmc.WorkingSetSize))
		{
			totalMemory_32bit = TWO_GIG;
			availMemory_32bit = (TWO_GIG - pmc.WorkingSetSize);
		}
		else
		{
			totalMemory_32bit = (pmc.WorkingSetSize + memStatus.ullAvailPhys);
			availMemory_32bit = memStatus.ullAvailPhys;
		}

		if (((float)(totalMemory_32bit - availMemory_32bit)/(float)totalMemory_32bit) >= MAX_PERCENT)
		{
			ChangeState(SAVING);
			return FALSE;
		}
#endif
	}
	try
	{
		CSingleLock bufferLock(&m_recorderBuffer);
		bufferLock.Lock();
		if((m_grabMode == BUFFER_FRAMES) ||
				((m_grabMode == DROP_FRAMES) && (m_imageBuffer.empty())))
		{
			m_imageBuffer.push_back(*image);
			m_streamingFrameCounter++;

			if (m_imageBuffer.size() == 1)
			{
				SetEvent(m_recordingEvents[DATA_IN_BUFFER]);
			}
		}
	}
	catch (std::exception& e)
	{
		return FALSE;
	}
	return TRUE;
}

void RecordingDialog::OnTcnSelchangeTabOutputType(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch (m_tabCtrl_OutputType.GetCurSel())
	{
		case OUTPUT_TYPE_IMAGE:
			m_videoRecordingPage.ShowWindow(SW_HIDE);
			m_imageRecordingPage.ShowWindow(SW_SHOW);
			break;

		case OUTPUT_TYPE_VIDEO:
			m_imageRecordingPage.ShowWindow(SW_HIDE);
			m_videoRecordingPage.ShowWindow(SW_SHOW);
			break;
		default:
			MessageBox("Unknown page index.");
			break;
	}
	*pResult = 0;
}

void RecordingDialog::OnBnClickedRadioNumFrames()
{
	UpdateSavingOptions();
}

void RecordingDialog::OnBnClickedRadioNthFrame()
{
	UpdateSavingOptions();
}

void RecordingDialog::OnBnClickedRadioNumSeconds()
{
	UpdateSavingOptions();
}

void RecordingDialog::OnBnClickedRadioNthSeconds()
{
	UpdateSavingOptions();
}

void RecordingDialog::UpdateSavingOptions()
{
	m_edit_NumFrames.EnableWindow(m_radio_NumFrames.GetCheck());
	m_edit_NthFrame.EnableWindow(m_radio_NthFrame.GetCheck());
	m_edit_NthTotalFrames.EnableWindow(m_radio_NthFrame.GetCheck());
	m_edit_NumSeconds.EnableWindow(m_radio_NumSeconds.GetCheck());
	m_edit_NthSecond.EnableWindow(m_radio_NthSecond.GetCheck());
	m_edit_NthTotalSeconds.EnableWindow(m_radio_NthSecond.GetCheck());
}

void RecordingDialog::OnBnClickedButtonStartStopVideoRecord()
{
	// Start/Stop/Abort button has been pressed...
	RecorderState currState = GetRecorderState();

	if ( currState == STOPPED ||
			currState == STOPPING )
	{
		StopRecording();
		DisableControls();
		CString errorList;
		if (ValidInput(&errorList))
		{
			time_t rawtime;
			struct tm * timeinfo;
			time( &rawtime );
			timeinfo = localtime( &rawtime );

			char timestamp[64];
			strftime( timestamp, 64, "%Y-%m-%d-%H%M%S", timeinfo );

			GetFilePath(&m_saveFilenameBase);
			m_saveFilenameBase.AppendFormat("_%s", timestamp);

			if(m_radio_bufferedMode.GetCheck())
			{
				m_grabMode = BUFFER_FRAMES;
			}
			else
			{
				m_grabMode = DROP_FRAMES;
			}

			if (CreateRecordingEvents())
			{
				m_isSaveBayerImageSelected = m_imageRecordingPage.GetSaveBayerCheckState();
				StartRecording();
				m_saveFrameLoopThread = AfxBeginThread(
						ThreadSaveFrame,
						this,
						THREAD_PRIORITY_NORMAL,
						0,
						CREATE_SUSPENDED,
						NULL);

				if (m_saveFrameLoopThread != NULL)
				{
					m_saveFrameLoopThread->m_bAutoDelete = FALSE;
					m_saveFrameLoopThread->ResumeThread();
				}
				else
				{
					AfxMessageBox("Saving thread creation failed... Aborting.", MB_OK);
					EnableControls();
				}
			}
			else
			{
				AfxMessageBox("RecordingEvents creation failed... Aborting.", MB_OK);
				EnableControls();
			}
		}
		else
		{
			AfxMessageBox(errorList);
			EnableControls();
		}
	}
	else if (currState == STARTED)
	{
		ChangeState(SAVING);
	}
	else if (currState == SAVING)
	{
		ChangeState(ABORT_SAVING);
	}
}

void RecordingDialog::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case TIMER_DURATION:
			// stop recording
			{
				CSingleLock stateLock(&m_timerExpiredState);
				stateLock.Lock();
				m_durationExpiredFlag = TRUE;
			}
			ChangeState(SAVING);
			break;
		case TIMER_INTERVAL:
			// signal interval
			{
				CSingleLock stateLock(&m_timerExpiredState);
				stateLock.Lock();
				m_intervalExpiredFlag = TRUE;
			}
			CDialog::OnTimer(nIDEvent);
			break;
		default:
			CDialog::OnTimer(nIDEvent);
			break;
	}

}

RecordingDialog::SaveOptionType RecordingDialog::GetSaveType()
{
	if (m_radio_NumFrames.GetCheck())
		return NUMBER_OF_FRAMES;
	else if (m_radio_NthFrame.GetCheck())
		return EVERY_NTH_FRAME;
	else if (m_radio_NumSeconds.GetCheck())
		return NUMBER_OF_SECONDS;
	else if (m_radio_NthSecond.GetCheck())
		return EVERY_NTH_SECOND;

	return NUMBER_OF_FRAMES;
}

BOOL RecordingDialog::GetNumFrames(unsigned int* numFrames)
{
	CString numFramesTxt;
	m_edit_NumFrames.GetWindowText(numFramesTxt);

	return (!(numFramesTxt.IsEmpty()) && ConvertToInt(numFramesTxt, numFrames));
}

BOOL RecordingDialog::GetNthFrame(unsigned int* nthFrame)
{
	CString nthFramesTxt;
	m_edit_NthFrame.GetWindowText(nthFramesTxt);
	return (!(nthFramesTxt.IsEmpty()) && ConvertToInt(nthFramesTxt, nthFrame));
}

BOOL RecordingDialog::GetNthFrameTotal(unsigned int* nthFrameTotal)
{
	CString nthFramesTotalTxt;
	m_edit_NthTotalFrames.GetWindowText(nthFramesTotalTxt);
	return (!(nthFramesTotalTxt.IsEmpty()) && ConvertToInt(nthFramesTotalTxt, nthFrameTotal));
}

BOOL RecordingDialog::GetNumSeconds(unsigned int* numSeconds)
{
	CString numSecondsTxt;
	m_edit_NumSeconds.GetWindowText(numSecondsTxt);
	return (!(numSecondsTxt.IsEmpty()) && ConvertToInt(numSecondsTxt, numSeconds));
}

BOOL RecordingDialog::GetNthSecondsTotal(unsigned int* nthSecondsTotal)
{
	CString nthSecondsTotalTxt;
	m_edit_NthTotalSeconds.GetWindowText(nthSecondsTotalTxt);
	return (!(nthSecondsTotalTxt.IsEmpty()) && ConvertToInt(nthSecondsTotalTxt, nthSecondsTotal));
}

BOOL RecordingDialog::GetNthSecond(unsigned int* nthSecond)
{
	CString nthSecondTxt;
	m_edit_NthSecond.GetWindowText(nthSecondTxt);
	return (!(nthSecondTxt.IsEmpty()) && ConvertToInt(nthSecondTxt, nthSecond));
}

BOOL RecordingDialog::ConvertToInt(CString text, unsigned int* integer )
{
	errno = 0;
	*integer = _ttoi(text.GetBuffer());

	return ((errno == 0) || (*integer != 0));
}

void RecordingDialog::GetFilePath( CString* filename )
{
	m_edit_SaveFilePath.GetWindowText(*filename);
	filename->TrimLeft();
}

RecordingDialog::RecorderState RecordingDialog::GetRecorderState()
{
	CSingleLock stateLock(&m_recordingMutex);
	stateLock.Lock();
	return m_currRecordingState;
}

UINT RecordingDialog::ThreadSaveFrameHelper()
{
	CSingleLock bufferLock(&m_recorderBuffer);

	Error error;
	Image image;

	if (m_tabCtrl_OutputType.GetCurSel() == OUTPUT_TYPE_IMAGE)
	{
		while(GetRecorderState() == STARTED)
		{
			DWORD waitResult = WaitForMultipleObjects(NUM_RECORDING_EVENTS, m_recordingEvents, FALSE, INFINITE);

			if ((waitResult - WAIT_OBJECT_0) == END_LIVE_RECORDING)
			{
				// stop button was hit
				break;
			}

			bufferLock.Lock();
			RetrieveNextImageFromBuffer(&image);

			if (m_imageBuffer.empty())
			{
				ResetEvent(m_recordingEvents[DATA_IN_BUFFER]);
			}
			bufferLock.Unlock();

			try
			{
				SaveImageToFile(&image, &m_imageSettings);
			}
			catch (RecordingException& e)
			{
				CString errMsg;
				errMsg.AppendFormat("%s\nRecording will Stop. Any remaining buffered images will be saved to disk.", e.what());
				AfxMessageBox(errMsg, MB_OK);

				ChangeState(SAVING);
				break;
			}
		}

		// save any remaining frames in buffer
		while(!(m_imageBuffer.empty()) && (GetRecorderState() == SAVING))
		{
			bufferLock.Lock();
			RetrieveNextImageFromBuffer(&image);
			bufferLock.Unlock();

			try
			{
				SaveImageToFile(&image, &m_imageSettings);
			}
			catch (RecordingException& e)
			{
				CString errMsg;
				errMsg.AppendFormat("%s\nStopping.", e.what());
				AfxMessageBox(errMsg, MB_OK);
				break;
			}
		}
	}
	else if (m_tabCtrl_OutputType.GetCurSel() == OUTPUT_TYPE_VIDEO)
	{
		AVIRecorder aviRecorder;

		// Set AVI Split size
		aviRecorder.SetMaximumAVISize(m_videoSettings.aviSize);

		switch (m_videoSettings.videoFormat)
		{
			case VideoRecordingPage::UNCOMPRESSED:
				error = aviRecorder.AVIOpen(m_videoSettings.filename, &(m_videoSettings.aviOption));
				break;
			case VideoRecordingPage::MJPEG:
				error = aviRecorder.AVIOpen(m_videoSettings.filename, &(m_videoSettings.mjpgOption));
				break;
			case VideoRecordingPage::H264:
				error = aviRecorder.AVIOpen(m_videoSettings.filename, &(m_videoSettings.h264Option));
				break;
			default:
				throw RecordingException("Invalid Video Output Type Specified.");
				break;
		}

		if(error != PGRERROR_OK)
		{
			throw RecordingException(error.GetDescription());
		}

		while(GetRecorderState() == STARTED)
		{
			DWORD waitResult = WaitForMultipleObjects(NUM_RECORDING_EVENTS, m_recordingEvents, FALSE, INFINITE);

			if ((waitResult - WAIT_OBJECT_0) == END_LIVE_RECORDING)
			{
				// stop button was hit
				break;
			}

			bufferLock.Lock();
			RetrieveNextImageFromBuffer(&image);

			if (m_imageBuffer.empty())
			{
				ResetEvent(m_recordingEvents[DATA_IN_BUFFER]);
			}
			bufferLock.Unlock();

			try
			{
				SaveImageToVideo(&aviRecorder, &image);
			}
			catch (RecordingException& e)
			{
				CString errMsg;
				errMsg.AppendFormat("%s\nRecording will Stop. Any remaining buffered images will be appended to video.", e.what());
				AfxMessageBox(errMsg, MB_OK);

				ChangeState(SAVING);
				break;
			}
		}

		// process any remaining frames in buffer
		while(!(m_imageBuffer.empty()) && (GetRecorderState() == SAVING))
		{
			bufferLock.Lock();
			RetrieveNextImageFromBuffer(&image);
			bufferLock.Unlock();

			try
			{
				SaveImageToVideo(&aviRecorder, &image);
			}
			catch (RecordingException& e)
			{
				CString errMsg;
				errMsg.AppendFormat("%s\nStopping.", e.what());
				AfxMessageBox(errMsg, MB_OK);
				break;
			}
		}

		// do cleanup
		error = aviRecorder.AVIClose();
		if(error != PGRERROR_OK)
		{
			// display error and quit
			CString errMsg(error.GetDescription());
			AfxMessageBox(errMsg, MB_OK);
		}
	}

	// We cannot restart camera in this thread so we reset the dialog
	// and put the recorder in a stopping state.
	StoppingRecording();
	return 0;
}

UINT RecordingDialog::ThreadSaveFrame( void* pparam )
{
	if (pparam == NULL)
	{
		AfxEndThread(-1);
	}

	RecordingDialog* pDoc = (RecordingDialog*)pparam;

	UINT retVal = 0;

	try
	{
		retVal = pDoc->ThreadSaveFrameHelper();
	}
	catch (RecordingException& e)
	{
		pDoc->StopRecording();

		CString errMsg;
		errMsg.AppendFormat("%s\nStopping.", e.what());
		AfxMessageBox(errMsg, MB_OK);
		AfxEndThread(-1);
	}
	return retVal;
}

void RecordingDialog::DoRecording( Image* rawImage, BOOL isCorruptFrame )
{
	RecorderState currState = GetRecorderState();

	// if recording has started then buffer frame if it is wanted
	if (currState == STARTED)
	{
		if (isCorruptFrame)
		{
			m_corruptFrameCounter++;
		}
		else
		{
			m_frameCounter++;
		}

		if ( (!(m_chk_captureCorruptFrames.GetCheck()) && !isCorruptFrame) ||
				(m_chk_captureCorruptFrames.GetCheck() && isCorruptFrame))
		{
			ProcessCurrentFrame(rawImage);
		}
	}

	if (currState == STOPPING)
	{
		StopRecording();
	}

	UpdateImageCounters();
}

void RecordingDialog::StopRecording()
{
	if (GetRecorderState() == STOPPED)
	{
		return;
	}

	ChangeState(STOPPED);

	DWORD dwRet = WaitForSingleObject( m_saveFrameLoopThread->m_hThread, 1000);
	if ( dwRet == WAIT_TIMEOUT )
	{
		// Timed out while waiting for thread to exit
		TerminateThread(m_saveFrameLoopThread->m_hThread, 0);// Force thread exit
		m_saveFrameLoopThread = NULL;
	}

	Error error;
	FC2Config fc2Config;

	if (m_pCameraRec != NULL)
	{
		error = m_pCameraRec->GetConfiguration(&fc2Config);
	}

	if (fc2Config.grabMode != DROP_FRAMES)
	{
		// restart camera in drop frames mode
		CSingleLock controlLock(&m_startStopControl);
		controlLock.Lock();
		error = m_pCameraRec->StopCapture();
		fc2Config.grabMode = DROP_FRAMES;
		error = m_pCameraRec->SetConfiguration(&fc2Config);
		error = m_pCameraRec->StartCapture();
		controlLock.Unlock();
	}

	CSingleLock bufferLock(&m_recorderBuffer);
	bufferLock.Lock();
	m_imageBuffer.clear();
	bufferLock.Unlock();

	DeleteRecordingEvents();

	if (m_recorderTimerDuration != NULL)
		::KillTimer(m_hWnd, TIMER_DURATION);
	if (m_recorderTimerInterval != NULL)
		::KillTimer(m_hWnd, TIMER_INTERVAL);

	m_recorderTimerDuration = NULL;
	m_recorderTimerInterval = NULL;

	{
		CSingleLock stateLock(&m_timerExpiredState);
		stateLock.Lock();
		m_durationExpiredFlag = FALSE;
		m_intervalExpiredFlag = FALSE;
	}

	EnableControls();
}

void RecordingDialog::StartRecording()
{
	SaveOptionType saveType = GetSaveType();

	if (saveType == NUMBER_OF_SECONDS)
	{
		unsigned int numSeconds;
		GetNumSeconds(&numSeconds);
		m_recorderTimerDuration = ::SetTimer(m_hWnd, TIMER_DURATION, numSeconds, (TIMERPROC)NULL);
	}
	else if (saveType == EVERY_NTH_SECOND)
	{
		unsigned int nthSecondsTotal, nthInterval;
		GetNthSecondsTotal(&nthSecondsTotal);
		GetNthSecond(&nthInterval);
		m_recorderTimerDuration = ::SetTimer(m_hWnd, TIMER_DURATION, nthSecondsTotal, (TIMERPROC)NULL);
		m_recorderTimerInterval = ::SetTimer(m_hWnd, TIMER_INTERVAL, nthInterval, (TIMERPROC)NULL);
	}

	// start the camera in buffered frame mode

	if(m_pCameraRec != NULL)
	{
		m_pCameraRec->StopCapture();
		FC2Config fc2Config;
		m_pCameraRec->GetConfiguration(&fc2Config);
		fc2Config.grabMode = m_grabMode;
		m_pCameraRec->SetConfiguration(&fc2Config);

		m_pCameraRec->StartCapture();
	}

	CSingleLock bufferLock(&m_recorderBuffer);
	bufferLock.Lock();
	m_imageBuffer.clear();
	bufferLock.Unlock();

	m_frameCounter = 0;
	m_corruptFrameCounter = 0;
	m_streamingFrameCounter = 0;
	m_savedImageCounter = 0;

	UpdateImageCounters();

	if (m_tabCtrl_OutputType.GetCurSel() == OUTPUT_TYPE_IMAGE)
	{
		GetImageSettings(&m_imageSettings);
	}
	else if (m_tabCtrl_OutputType.GetCurSel() == OUTPUT_TYPE_VIDEO)
	{
		GetVideoSettings(&m_videoSettings);
	}

	ChangeState(STARTED);
}

void RecordingDialog::StoppingRecording()
{
	CSingleLock bufferLock(&m_recorderBuffer);
	bufferLock.Lock();
	m_imageBuffer.clear();
	bufferLock.Unlock();

	if (m_recorderTimerDuration != NULL)
		::KillTimer(m_hWnd, TIMER_DURATION);
	if (m_recorderTimerInterval != NULL)
		::KillTimer(m_hWnd, TIMER_INTERVAL);

	m_recorderTimerDuration = NULL;
	m_recorderTimerInterval = NULL;

	{
		CSingleLock stateLock(&m_timerExpiredState);
		stateLock.Lock();
		m_durationExpiredFlag = FALSE;
		m_intervalExpiredFlag = FALSE;
	}


	ChangeState(STOPPING);
	EnableControls();
}

void RecordingDialog::ProcessCurrentFrame( Image* rawImage)
{
	Error error;
	SaveOptionType saveType = GetSaveType();

	unsigned int frameCounter = m_frameCounter;

	if (m_chk_captureCorruptFrames.GetCheck())
	{
		frameCounter = m_corruptFrameCounter;
	}

	// if recMode == #ofFrames then
	if (saveType == NUMBER_OF_FRAMES)
	{
		unsigned int numFrames;
		GetNumFrames(&numFrames);

		// push frame onto queue
		Image tmpImage;
		error = tmpImage.DeepCopy(rawImage);
		if(error == PGRERROR_OK)
		{
			BufferFrame(&tmpImage);

			if ((numFrames != 0) &&
					(((m_grabMode == BUFFER_FRAMES) && (frameCounter >= numFrames)) ||
					 ((m_grabMode == DROP_FRAMES) && (m_streamingFrameCounter >= numFrames))))
			{
				ChangeState(SAVING);
			}
		}
	}
	// if recMode == every Nth Frame
	else if (saveType == EVERY_NTH_FRAME)
	{
		// if target not hit then:
		unsigned int nthFrame;
		GetNthFrame(&nthFrame);
		unsigned int nthFramesTotal;
		GetNthFrameTotal(&nthFramesTotal);

		// save last image of each interval
		if ((nthFrame == 1) || (frameCounter % nthFrame == 0))
		{
			// push frame onto queue
			Image tmpImage;
			error = tmpImage.DeepCopy(rawImage);
			if(error == PGRERROR_OK)
			{
				BufferFrame(&tmpImage);
			}
		}
		else
		{
			// do nothing, skip frame
		}

		if ((nthFramesTotal != 0) && (frameCounter >= nthFramesTotal))
		{
			ChangeState(SAVING);
		}
	}
	//    if recMode == # of Seconds
	else if (saveType == NUMBER_OF_SECONDS)
	{
		BOOL bufferImage = FALSE;

		{
			CSingleLock stateLock(&m_timerExpiredState);
			stateLock.Lock();
			bufferImage = !m_durationExpiredFlag;
		}

		if (bufferImage)
		{
			// push frame onto queue
			Image tmpImage;
			error = tmpImage.DeepCopy(rawImage);
			if (error == PGRERROR_OK)
			{
				BufferFrame(&tmpImage);
			}
		}
		else
		{
			// change state to saving
			ChangeState(SAVING);
		}
	}
	else if (saveType == EVERY_NTH_SECOND)
	{
		unsigned int nthTotalSeconds;
		GetNthSecondsTotal(&nthTotalSeconds);

		BOOL durationExpired = FALSE;
		BOOL intervalExpired = FALSE;

		{
			CSingleLock stateLock(&m_timerExpiredState);
			stateLock.Lock();
			durationExpired = m_durationExpiredFlag;
			intervalExpired = m_intervalExpiredFlag;
			m_intervalExpiredFlag = FALSE;
		}

		if ((nthTotalSeconds == 0) || (!durationExpired))
		{
			if (intervalExpired)
			{
				// push frame onto queue
				Image tmpImage;
				error = tmpImage.DeepCopy(rawImage);
				if (error == PGRERROR_OK)
				{
					BufferFrame(&tmpImage);
				}
			}
			else
			{
				// do nothing, skip frame
			}
		}
		else
		{
			// change state to saving
			ChangeState(SAVING);
		}
	}
}

void RecordingDialog::GetImageSettings( ImageRecordingPage::ImageSettings* imageSettings )
{
	strcpy(imageSettings->filename, m_saveFilenameBase);
	m_imageRecordingPage.GetSettings(imageSettings);
}

void RecordingDialog::GetVideoSettings( VideoRecordingPage::VideoSettings* videoSettings )
{
	strcpy(videoSettings->filename, m_saveFilenameBase);
	m_videoRecordingPage.GetSettings(videoSettings);
}

Error RecordingDialog::SaveImage( Image* tmp, ImageRecordingPage::ImageSettings* imageSettings, unsigned int count )
{
	char saveName[MAX_PATH];

	sprintf(saveName, "%s-%04d.%s", imageSettings->filename, count, imageSettings->fileExtension);
	switch (imageSettings->imageFormat)
	{

		case ImageRecordingPage::PGM:
			return tmp->Save(saveName, &(imageSettings->pgmOption));
			break;
		case ImageRecordingPage::PPM:
			return tmp->Save(saveName, &(imageSettings->ppmOption));
			break;
		case ImageRecordingPage::JPEG:
			return tmp->Save(saveName, &(imageSettings->jpgOption));
			break;
		case ImageRecordingPage::JPEG2000:
			return tmp->Save(saveName, &(imageSettings->jpg2Option));
			break;
		case ImageRecordingPage::TIFF:
			return tmp->Save(saveName, &(imageSettings->tiffOption));
			break;
		case ImageRecordingPage::PNG:
			return tmp->Save(saveName, &(imageSettings->pngOption));
			break;
		case ImageRecordingPage::BMP:
			return tmp->Save(saveName, &(imageSettings->bmpOption));
			break;
		case ImageRecordingPage::RAW:
			return tmp->Save(saveName, RAW);
			break;
		default:
			return tmp->Save(saveName, RAW);
			break;
	}
}

void RecordingDialog::StoreCamPtr( CameraBase* pCamera )
{
	m_pCameraRec = pCamera;
	m_videoRecordingPage.StoreCameraPtr(m_pCameraRec);
	m_imageRecordingPage.StoreCameraPtr(m_pCameraRec);
}

void RecordingDialog::UpdateImageCounters()
{
	CString counterString;

	counterString.Format("%d", m_frameCounter);
	m_static_FrameCounter.SetWindowText(counterString);

	counterString.Format("%d", m_corruptFrameCounter);
	m_static_CorruptFrameCounter.SetWindowText(counterString);

	counterString.Format("%d", m_imageBuffer.size());
	m_static_bufferedCounter.SetWindowText(counterString);

	counterString.Format("%d", m_savedImageCounter);
	m_static_savedImageCount.SetWindowText(counterString);

#ifdef _WIN64
	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(MEMORYSTATUSEX);

	if(!GlobalMemoryStatusEx(&memStatus))
	{
		m_static_availableMemory.SetWindowText("N/A");
		m_static_totalMemory.SetWindowText("N/A");
		m_static_memoryLoad.SetWindowText("N/A");
	}
	else
	{
		counterString.Format("%5.2f MB", (float)(memStatus.ullAvailPhys / (float)ONE_MEG));
		m_static_availableMemory.SetWindowText(counterString);

		counterString.Format("%5.2f MB", (float)(memStatus.ullTotalPhys / (float)ONE_MEG));
		m_static_totalMemory.SetWindowText(counterString);

		counterString.Format("%d%%", memStatus.dwMemoryLoad);
		m_static_memoryLoad.SetWindowText(counterString);
	}
#else

	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(MEMORYSTATUSEX);

	HANDLE procHandle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;

	if(!GlobalMemoryStatusEx(&memStatus) || !GetProcessMemoryInfo(procHandle, &pmc, sizeof(pmc)))
	{
		m_static_availableMemory.SetWindowText("N/A");
		m_static_totalMemory.SetWindowText("N/A");
		m_static_memoryLoad.SetWindowText("N/A");
	}
	else
	{
		DWORDLONG availMemory_32bit = 0;
		DWORDLONG totalMemory_32bit = 0;

		if (memStatus.ullAvailPhys > (TWO_GIG - pmc.WorkingSetSize))
		{
			totalMemory_32bit = TWO_GIG;
			availMemory_32bit = (TWO_GIG - pmc.WorkingSetSize);
		}
		else
		{
			totalMemory_32bit = (pmc.WorkingSetSize + memStatus.ullAvailPhys);
			availMemory_32bit = memStatus.ullAvailPhys;
		}

		counterString.Format("%5.2f MB", (float)(availMemory_32bit)/(float)ONE_MEG);
		m_static_availableMemory.SetWindowText(counterString);

		counterString.Format("%5.2f MB", (float)(totalMemory_32bit) / (float)ONE_MEG);
		m_static_totalMemory.SetWindowText(counterString);

		counterString.Format("%3.1f%%",  ((float)(totalMemory_32bit - availMemory_32bit)/(float)totalMemory_32bit) * 100.0);
		m_static_memoryLoad.SetWindowText(counterString);
	}
#endif
}

BOOL RecordingDialog::ValidInput(CString* errorList)
{
	ValidateFileName(errorList);
	ValidateSaveOptions(errorList);

	if (m_tabCtrl_OutputType.GetCurSel() == 0)
	{
		m_imageRecordingPage.ValidateSettings(errorList);
	}
	else
	{
		m_videoRecordingPage.ValidateSettings(errorList);
	}

	return errorList->IsEmpty();
}

void RecordingDialog::ValidateFileName( CString* errorList )
{
	CString filePath;
	CString dir;

	GetFilePath(&filePath);

	if (filePath.IsEmpty())
	{
		errorList->AppendFormat("Save file/path has not been specified\n");
		return;
	}

	unsigned int filePos = filePath.ReverseFind('\\');

	if (filePos != -1)
	{
		if (filePos > 2)
		{
			dir = filePath.Left(filePos+1);

			if (!CreateDirectory(dir, NULL))
			{
				DWORD lastError = GetLastError();

				if ( lastError == ERROR_ALREADY_EXISTS)
				{
					// dir exists
				}
				else
				{
					errorList->AppendFormat("Error creating save directory: 0x%08X\n", lastError);
				}
			}
		}
	}
}

void RecordingDialog::ValidateSaveOptions( CString* errorList )
{
	switch (GetSaveType())
	{
		case NUMBER_OF_FRAMES:

			unsigned int numFrames;
			if(!GetNumFrames(&numFrames))
			{
				errorList->Append("Invalid number of frames specified.\n");
			}
			break;
		case EVERY_NTH_FRAME:

			unsigned int nthFrame;
			unsigned int nthTotalFrames;

			if((!GetNthFrame(&nthFrame))                              ||
					(!GetNthFrameTotal(&nthTotalFrames))                   ||
					((nthTotalFrames != 0) && (nthTotalFrames < nthFrame)) ||
					(nthFrame == 0))
			{
				errorList->Append("Invalid frame interval/duration specified.\n");
			}
			break;
		case NUMBER_OF_SECONDS:
			unsigned int numSeconds;
			if(!GetNumSeconds(&numSeconds))
			{
				errorList->Append("Invalid number of ms specified.\n");
			}
			break;
		case EVERY_NTH_SECOND:
			unsigned int nthSecond;
			unsigned int nthTotalSeconds;

			if((!GetNthSecond(&nthSecond))                             ||
					(!GetNthSecondsTotal(&nthTotalSeconds))                 ||
					((nthTotalSeconds!= 0) &&(nthTotalSeconds < nthSecond)) ||
					(nthSecond == 0))
			{
				errorList->Append("Invalid ms interval/duration specified.\n");
			}
			break;
		default:
			errorList->Append("Unrecognized Save Type Specified.\n");
			break;
	}
}

void RecordingDialog::ValidateImageSettings( CString* errorList )
{
	ImageRecordingPage::ImageSettings imageSettings;

	m_imageRecordingPage.GetSettings(&imageSettings);
}

void RecordingDialog::UpdateModeDependentControls()
{
	m_imageRecordingPage.UpdateModeDependentControls();
	m_videoRecordingPage.UpdateModeDependentControls();
}

void RecordingDialog::EnableControls()
{
	m_edit_SaveFilePath.EnableWindow(TRUE);
	(GetDlgItem(IDC_BUTTON_BROWSE))->EnableWindow(TRUE);

	m_radio_NumFrames.EnableWindow(TRUE);
	m_radio_NthFrame.EnableWindow(TRUE);
	m_radio_NumSeconds.EnableWindow(TRUE);
	m_radio_NthSecond.EnableWindow(TRUE);

	m_chk_captureCorruptFrames.EnableWindow(TRUE);

	UpdateSavingOptions();

	m_radio_bufferedMode.EnableWindow(TRUE);
	m_radio_streamingMode.EnableWindow(TRUE);

	m_tabCtrl_OutputType.EnableWindow(TRUE);
	m_videoRecordingPage.EnableControls(TRUE);
	m_imageRecordingPage.EnableControls(TRUE);

	// counters are enabled opposite of other controls
	m_static_FrameCounter.EnableWindow(FALSE);
	m_static_CorruptFrameCounter.EnableWindow(FALSE);
	m_static_bufferedCounter.EnableWindow(FALSE);
	m_static_savedImageCount.EnableWindow(FALSE);
	m_static_availableMemory.EnableWindow(FALSE);
	m_static_totalMemory.EnableWindow(FALSE);
	m_static_memoryLoad.EnableWindow(FALSE);
}

void RecordingDialog::DisableControls()
{
	m_edit_SaveFilePath.EnableWindow(FALSE);
	(GetDlgItem(IDC_BUTTON_BROWSE))->EnableWindow(FALSE);

	m_radio_NumFrames.EnableWindow(FALSE);
	m_edit_NumFrames.EnableWindow(FALSE);

	m_radio_NthFrame.EnableWindow(FALSE);
	m_edit_NthFrame.EnableWindow(FALSE);
	m_edit_NthTotalFrames.EnableWindow(FALSE);

	m_radio_NumSeconds.EnableWindow(FALSE);
	m_edit_NumSeconds.EnableWindow(FALSE);

	m_radio_NthSecond.EnableWindow(FALSE);
	m_edit_NthSecond.EnableWindow(FALSE);
	m_edit_NthTotalSeconds.EnableWindow(FALSE);

	m_radio_NthFrame.EnableWindow(FALSE);
	m_edit_NthFrame.EnableWindow(FALSE);

	m_radio_bufferedMode.EnableWindow(FALSE);
	m_radio_streamingMode.EnableWindow(FALSE);

	m_chk_captureCorruptFrames.EnableWindow(FALSE);

	m_tabCtrl_OutputType.EnableWindow(FALSE);
	m_videoRecordingPage.EnableControls(FALSE);
	m_imageRecordingPage.EnableControls(FALSE);

	// counters are enabled opposite of other controls
	m_static_FrameCounter.EnableWindow(TRUE);
	m_static_CorruptFrameCounter.EnableWindow(TRUE);
	m_static_bufferedCounter.EnableWindow(TRUE);
	m_static_savedImageCount.EnableWindow(TRUE);
	m_static_availableMemory.EnableWindow(TRUE);
	m_static_totalMemory.EnableWindow(TRUE);
	m_static_memoryLoad.EnableWindow(TRUE);
}

BOOL RecordingDialog::IsCaptureCorrupt()
{
	return m_chk_captureCorruptFrames.GetCheck();
}

void RecordingDialog::RetrieveNextImageFromBuffer( Image* image )
{
	if(m_grabMode == BUFFER_FRAMES)
	{
		*image = m_imageBuffer.front();
		m_imageBuffer.erase(m_imageBuffer.begin());
	}
	else
	{
		*image = m_imageBuffer.back();
		m_imageBuffer.clear();
	}
}

void RecordingDialog::SaveImageToFile(Image* image, ImageRecordingPage::ImageSettings* imageSettings)
{
	Error error;
	PixelFormat pixelFormat = image->GetPixelFormat();

	if ((pixelFormat == PIXEL_FORMAT_RAW8)  ||
			(pixelFormat == PIXEL_FORMAT_RAW12) ||
			(pixelFormat == PIXEL_FORMAT_RAW16))
	{
		ColorProcessingAlgorithm colAlg = Image::GetDefaultColorProcessing();

		if ((colAlg != NO_COLOR_PROCESSING) && !m_isSaveBayerImageSelected)
		{
			Image convertedImage;

			if (image->Convert(PIXEL_FORMAT_BGR, &convertedImage) == PGRERROR_OK)
			{
				error = SaveImage(&convertedImage, imageSettings, m_savedImageCounter);
			}
		}
		else
		{
			error = SaveImage(image, imageSettings, m_savedImageCounter);
		}
	}
	else
	{
		error = SaveImage(image, imageSettings, m_savedImageCounter);
	}

	if(error != PGRERROR_OK)
	{
		throw RecordingException(error.GetDescription());
	}

	if (GetRecorderState() == STOPPED)
	{
		return;
	}
	m_savedImageCounter++;
	UpdateImageCounters();
}

void RecordingDialog::SaveImageToVideo(AVIRecorder* aviRecorder, Image* image )
{
	Error error = aviRecorder->AVIAppend(image);
	if(error != PGRERROR_OK)
	{
		throw RecordingException(error.GetDescription());
	}

	if (GetRecorderState() == STOPPED)
	{
		return;
	}
	m_savedImageCounter++;
	UpdateImageCounters();
}

BOOL RecordingDialog::CreateRecordingEvents()
{
	bool eventCreationSucceeded = TRUE;
	int i = 0;

	for (i = 0; i < NUM_RECORDING_EVENTS; i++)
	{
		m_recordingEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (m_recordingEvents[i] == NULL)
		{
			eventCreationSucceeded = FALSE;
			break;
		}
	}

	if (!eventCreationSucceeded)
	{
		for ( ;i >= 0; i--)
		{
			CloseHandle(m_recordingEvents[i]);
		}
	}

	return eventCreationSucceeded;
}

void RecordingDialog::DeleteRecordingEvents()
{
	for (int i = 0; i < NUM_RECORDING_EVENTS; i++)
	{
		CloseHandle(m_recordingEvents[i]);
		m_recordingEvents[i] = NULL;
	}
}

void RecordingDialog::ChangeState(RecorderState state)
{
	{
		CSingleLock stateLock(&m_recordingMutex);
		stateLock.Lock();

		if (m_currRecordingState == state)
		{
			return;
		}

		switch (m_currRecordingState)
		{
			case STOPPED:
				if (state != STARTED)
				{
					return;
				}
				break;
			case STARTED:
				if ((state != SAVING) && (state != STOPPED))
				{
					return;
				}

				if (m_recorderTimerDuration != NULL)
					::KillTimer(m_hWnd, TIMER_DURATION);
				if (m_recorderTimerInterval != NULL)
					::KillTimer(m_hWnd, TIMER_INTERVAL);
				break;
			case SAVING:
				if ((state != STOPPING) && (state != ABORT_SAVING))
				{
					return;
				}
				break;
			case STOPPING:
				if (state != STOPPED)
				{
					return;
				}
				break;
			case ABORT_SAVING:
				if ((state != STOPPED) && (state != STOPPING))
				{
					return;
				}
			default:
				state = STOPPED;
				break;
		}

		m_currRecordingState = state;
	}

	{
		CSingleLock stateLock(&m_buttonState);
		stateLock.Lock();

		m_btn_StartStop.SetWindowText(RecordButtonStrings[state]);
		m_static_statusOutput.SetWindowText(StatusOutputStrings[state]);

		if (state == ABORT_SAVING)
		{
			m_btn_StartStop.EnableWindow(FALSE);
		}
		else
		{
			m_btn_StartStop.EnableWindow(TRUE);
		}

		if (state == SAVING || state == STOPPED)
		{
			SetEvent(m_recordingEvents[END_LIVE_RECORDING]);
		}
	}
}

BOOL RecordingDialog::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_F9)
			pMsg->wParam=VK_ESCAPE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
