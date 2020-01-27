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
//=============================================================================
// $Id: FlyCap2MFCDoc.cpp,v 1.27 2010-09-22 22:49:37 soowei Exp $
//=============================================================================

#include "stdafx.h"
#include "FlyCap2MFC.h"
#include "FlyCap2MFCDoc.h"

using namespace FlyCapture2;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFlyCap2MFCDoc

IMPLEMENT_DYNCREATE(CFlyCap2MFCDoc, CDocument)

	BEGIN_MESSAGE_MAP(CFlyCap2MFCDoc, CDocument)
	ON_COMMAND(ID_CAMERACONTROL_TOGGLECAMERACONTROL, &CFlyCap2MFCDoc::OnToggleCameraControl)
	ON_COMMAND(ID_FILE_SAVE_AS, &CFlyCap2MFCDoc::OnFileSaveAs)
END_MESSAGE_MAP()

CFlyCap2MFCDoc::CFlyCap2MFCDoc()
{
	InitBitmapStruct( _DEFAULT_WINDOW_X, _DEFAULT_WINDOW_Y );

	m_continueGrabThread = false;
	m_heventThreadDone = CreateEvent( NULL, FALSE, FALSE, NULL );

	m_uiFilterIndex = 0;

	m_beingSaved = false;

	m_pCamera = NULL;
}

CFlyCap2MFCDoc::~CFlyCap2MFCDoc()
{
	CloseHandle( m_heventThreadDone );

	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}
}

void CFlyCap2MFCDoc::InitBitmapStruct( int cols, int rows )
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

BOOL CFlyCap2MFCDoc::OnNewDocument()
{
	Error error;
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}
	CWinApp* theApp = AfxGetApp();
	CWnd* mainWnd;
	if( theApp )
	{
		mainWnd = theApp->m_pMainWnd;
		if( mainWnd )
		{
			mainWnd->ShowWindow(SW_HIDE);
		}
	}

	// Set the default image processing parameters
	Image::SetDefaultColorProcessing( NEAREST_NEIGHBOR );
	Image::SetDefaultOutputFormat( PIXEL_FORMAT_BGRU );

	// If entering this function from File->New Camera, stop the grab thread
	// first before doing anything else
	if ( m_continueGrabThread == true )
	{
		m_continueGrabThread = false;

		DWORD dwRet = WaitForSingleObject( m_heventThreadDone, 5000 );
		if ( dwRet == WAIT_TIMEOUT )
		{
			// Timed out while waiting for thread to exit
		}

		m_camCtlDlg.Hide();
		m_camCtlDlg.Disconnect();
		m_pCamera->Disconnect();
	}

	// Let the user select a camera
	bool okSelected;
	PGRGuid arGuid[64];
	unsigned int size = 64;
	CameraSelectionDlg camSlnDlg;
	camSlnDlg.ShowModal( &okSelected, arGuid, &size );
	if ( okSelected != true )
	{
		if (m_pCamera != NULL)
		{
			OnCloseDocument();
		}
		return FALSE;
	}

	BusManager busMgr;
	InterfaceType ifType;
	error = busMgr.GetInterfaceTypeFromGuid( &arGuid[0], &ifType );
	if ( error != PGRERROR_OK )
	{
		return FALSE;
	}

	if ( ifType == INTERFACE_GIGE )
	{
		m_pCamera = new GigECamera;
	}
	else
	{
		m_pCamera = new Camera;
	}

	// Connect to the 0th selected camera
	error = m_pCamera->Connect( &arGuid[0] );
	if( error != PGRERROR_OK )
	{
		CString csMessage;
		csMessage.Format(
				"Connect Failure: %s", error.GetDescription() );
		AfxMessageBox( csMessage, MB_ICONSTOP );

		return FALSE;
	}

	error = m_pCamera->GetCameraInfo( &m_cameraInfo );
	if( error != PGRERROR_OK )
	{
		CString csMessage;
		csMessage.Format(
				"CameraInfo Failure: %s", error.GetDescription() );
		AfxMessageBox( csMessage, MB_ICONSTOP );

		return FALSE;
	}

	// Connect the camera control dialog to the camera object
	m_camCtlDlg.Connect( m_pCamera );

	// Start the grab thread
	m_continueGrabThread = true;
	AfxBeginThread( ThreadGrabImage, this );

	return TRUE;
}

void CFlyCap2MFCDoc::OnCloseDocument(void)
{
	m_continueGrabThread = false;

	DWORD dwRet = WaitForSingleObject( m_heventThreadDone, 5000 );
	if ( dwRet == WAIT_TIMEOUT )
	{
		// Timed out while waiting for thread to exit
	}

	m_camCtlDlg.Hide();
	m_camCtlDlg.Disconnect();

	if (m_pCamera != NULL)
	{
		m_pCamera->Disconnect();
	}

	CDocument::OnCloseDocument();
}

	UINT
CFlyCap2MFCDoc::ThreadGrabImage( void* pparam )
{
	CFlyCap2MFCDoc* pDoc = ((CFlyCap2MFCDoc*)pparam);
	UINT uiRetval = pDoc->DoGrabLoop();
	if( uiRetval != 0 )
	{
		CString csMessage;
		csMessage.Format(
				"The grab thread has encountered a problem and had to terminate." );
		AfxMessageBox( csMessage, MB_ICONSTOP );

		//
		// Signal that the thread has died.
		//
		SetEvent( pDoc->m_heventThreadDone );

		//
		// Bring up the camera selection dialog again
		// if we can get a pointer to the main window.
		//
		/*
		   CWinApp* theApp = AfxGetApp();
		   CWnd* mainWnd;
		   if( theApp )
		   {
		   mainWnd = theApp->m_pMainWnd;
		   if( mainWnd )
		   mainWnd->PostMessage( WM_COMMAND, ID_FILE_NEW, NULL );
		   }
		   */
	}

	return uiRetval;
}

	UINT
CFlyCap2MFCDoc::DoGrabLoop()
{
	Error error;
	CString csMessage;

	error = m_pCamera->StartCapture();
	if( error != PGRERROR_OK )
	{
		csMessage.Format(
				"StartCapture Failure: %s", error.GetDescription() );
		AfxMessageBox( csMessage, MB_ICONSTOP );
		return 0;
	}

	//
	// Start of main grab loop
	//
	while( m_continueGrabThread )
	{
		error = m_pCamera->RetrieveBuffer( &m_rawImage );
		if( error != PGRERROR_OK )
		{
			csMessage.Format(
					"RetrieveBuffer Failure: %s", error.GetDescription() );

			continue;
		}

		// Keep a reference to image so that we can save it
		// Doing this only when m_saveImage is not being saved
		if( m_beingSaved == false )
		{
			m_saveImage = m_rawImage;
		}

		//
		// Check to see if the thread should die.
		//
		if( !m_continueGrabThread )
		{
			break;
		}

		//
		// Update current framerate.
		//
		m_processedFrameRate.NewFrame();

		//
		// We try to detect whether the view is getting behind on servicing
		// the invalidate requests we send to it.  If there is still an
		// invalid area, don't bother color processing this frame.
		//
		bool skipProcessing = false;

		POSITION pos = GetFirstViewPosition();
		while ( pos != NULL )
		{
			if( GetUpdateRect( GetNextView( pos )->GetSafeHwnd(), NULL, FALSE ) != 0 )
			{
				skipProcessing = true;
			}
		}

		if( !skipProcessing )
		{
			//
			// Do post processing on the image.
			//
			unsigned int rows,cols,stride;
			PixelFormat format;
			m_rawImage.GetDimensions( &rows, &cols, &stride, &format );

			CSingleLock dataLock( &m_csData );
			dataLock.Lock();

			error = m_rawImage.Convert( PIXEL_FORMAT_BGR, &m_processedImage );
			if( error != PGRERROR_OK )
			{
				csMessage.Format(
						"Convert Failure: %s", error.GetDescription() );
				continue;
			}

			dataLock.Unlock();

			InitBitmapStruct( cols, rows );

			RedrawAllViews();
		}
	}

	error = m_pCamera->StopCapture();
	if( error != PGRERROR_OK )
	{
		csMessage.Format(
				"Stop Failure: %s", error.GetDescription() );
		AfxMessageBox( csMessage, MB_ICONSTOP );
	}

	//
	// End of main grab loop
	//
	SetEvent( m_heventThreadDone );

	return 0;
}

// CFlyCap2MFCDoc diagnostics

#ifdef _DEBUG
void CFlyCap2MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlyCap2MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFlyCap2MFCDoc commands

void CFlyCap2MFCDoc::RedrawAllViews()
{
	POSITION pos = GetFirstViewPosition();
	while ( pos != NULL )
	{
		InvalidateRect( GetNextView( pos )->GetSafeHwnd(), NULL, FALSE );
	}
}

double CFlyCap2MFCDoc::GetProcessedFrameRate()
{
	return m_processedFrameRate.GetFrameRate();
}

unsigned char* CFlyCap2MFCDoc::GetProcessedPixels()
{
	return m_processedImage.GetData();
}

void CFlyCap2MFCDoc::GetImageSize( unsigned int* pWidth, unsigned int* pHeight )
{
	//m_rawImage.GetDimensions( puiHeight, puiWidth );
	*pWidth = abs(m_bitmapInfo.bmiHeader.biWidth);
	*pHeight = abs(m_bitmapInfo.bmiHeader.biHeight);
}

void CFlyCap2MFCDoc::OnToggleCameraControl()
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

void CFlyCap2MFCDoc::OnFileSaveAs()
{
	Error   error;
	CString csMessage;
	JPEGOption JPEG_Save_Option;
	PNGOption  PNG_Save_Option;

	m_beingSaved = true;

	// Define the list of filters to include in the SaveAs dialog.
	const unsigned int uiNumFilters = 8;
	const CString arcsFilter[uiNumFilters] = {
		"Windows Bitmap (*.bmp)|*.bmp" ,
		"Portable Pixelmap (*.ppm)|*.ppm" ,
		"Portable Greymap (raw image) (*.pgm)|*.pgm" ,
		"Independent JPEG Group (*.jpg, *.jpeg)|*.jpg; *.jpeg" ,
		"Tagged Image File Format (*.tiff)|*.tiff" ,
		"Portable Network Graphics (*.png)|*.png" ,
		"Raw data (*.raw)|*.raw" ,
		"All Files (*.*)|*.*" };

	CString csFilters;

	// Keep track of which filter should be selected as default.
	// m_uiFilterIndex is set to what was previously used (0 if this is first time).
	for ( int i = 0; i < (uiNumFilters - 1); i++ )
	{
		csFilters += arcsFilter[(m_uiFilterIndex + i) % (uiNumFilters - 1)];
		csFilters += "|";
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

	CFileDialog fileDialog(
			FALSE,
			"bmp",
			tempFilename,
			OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT,
			csFilters,
			AfxGetMainWnd() );

	if( fileDialog.DoModal() == IDOK )
	{
		PixelFormat tempPixelFormat = m_saveImage.GetPixelFormat();
		Error rawError;
		ImageFileFormat saveImageFormat;
		CString csExt = fileDialog.GetFileExt();

		// Check file extension
		if( csExt.CompareNoCase("bmp") == 0 )
		{
			saveImageFormat = FlyCapture2::BMP;
		}
		else if( csExt.CompareNoCase("ppm") == 0 )
		{
			saveImageFormat = FlyCapture2::PPM;
		}
		else if( csExt.CompareNoCase("pgm") == 0 )
		{
			saveImageFormat = FlyCapture2::PGM;
		}
		else if( csExt.CompareNoCase("jpeg") == 0 || csExt.CompareNoCase("jpg") == 0 )
		{
			saveImageFormat = FlyCapture2::JPEG;
			JPEG_Save_Option.progressive = false;
			JPEG_Save_Option.quality = 100; //Superb quality.
		}
		else if( csExt.CompareNoCase("tiff") == 0 )
		{
			saveImageFormat = FlyCapture2::TIFF;
		}
		else if( csExt.CompareNoCase("png") == 0 )
		{
			saveImageFormat = FlyCapture2::PNG;
			PNG_Save_Option.interlaced = false;
			PNG_Save_Option.compressionLevel = 9; //Best compression
		}
		else if( csExt.CompareNoCase("raw") == 0 )
		{
			saveImageFormat = FlyCapture2::RAW;
		}
		else
		{
			AfxMessageBox( "Invalid file type" );
		}

		if ( saveImageFormat == FlyCapture2::RAW )
		{
			rawError = m_saveImage.Save( fileDialog.GetPathName(), FlyCapture2::RAW );
			if ( rawError != PGRERROR_OK )
			{
				AfxMessageBox(  "Failed to save image.", MB_ICONSTOP );
			}
		}
		else if ( saveImageFormat == FlyCapture2::PGM )
		{
			PixelFormat tempPixelFormat = m_saveImage.GetPixelFormat();
			if (tempPixelFormat == PIXEL_FORMAT_MONO8 ||
					tempPixelFormat == PIXEL_FORMAT_MONO12 ||
					tempPixelFormat == PIXEL_FORMAT_MONO16 ||
					tempPixelFormat == PIXEL_FORMAT_RAW8 ||
					tempPixelFormat == PIXEL_FORMAT_RAW12 ||
					tempPixelFormat == PIXEL_FORMAT_RAW16)
			{
				Error error = m_saveImage.Save( fileDialog.GetPathName(), saveImageFormat );
				if ( error != PGRERROR_OK )
				{
					AfxMessageBox( "Failed to convert image", MB_ICONSTOP );
				}
			}
			else
			{
				AfxMessageBox( "Invalid file format.\r\nNon mono / raw images cannot be saved as PGM.", MB_ICONSTOP );
			}
		}
		else
		{
			Error conversionError;
			Image convertedImage;
			conversionError = m_saveImage.Convert( &convertedImage );
			if ( conversionError != PGRERROR_OK )
			{
				AfxMessageBox( "Failed to convert image", MB_ICONSTOP );
				return;
			}

			Error convertedError;
			convertedError = convertedImage.Save( fileDialog.GetPathName(), saveImageFormat );
			if ( convertedError != PGRERROR_OK )
			{
				AfxMessageBox( "Failed to save image", MB_ICONSTOP );
			}
		}
	}
	m_beingSaved = false;

}
