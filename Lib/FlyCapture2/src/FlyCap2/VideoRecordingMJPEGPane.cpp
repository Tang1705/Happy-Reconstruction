// VideoRecordingMJPEGPane.cpp : implementation file
//

#include "stdafx.h"
#include "VideoRecordingMJPEGPane.h"

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif


// CVideoRecordingMJPEGPane dialog

const CString CVideoRecordingMJPEGPane::MJPEG_QUALITY_DEF = "75";


IMPLEMENT_DYNAMIC(CVideoRecordingMJPEGPane, CDialog)

	CVideoRecordingMJPEGPane::CVideoRecordingMJPEGPane(CWnd* pParent /*=NULL*/)
: CDialog(CVideoRecordingMJPEGPane::IDD, pParent)
{

}

CVideoRecordingMJPEGPane::~CVideoRecordingMJPEGPane()
{
}

void CVideoRecordingMJPEGPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MJPEG_COMPRESSION, m_edit_mjpegCompressionLevel);
	DDX_Control(pDX, IDC_SPIN_MJPEG_COMPRESSION, m_spin_mjpegCompressionLevel);
}


	BEGIN_MESSAGE_MAP(CVideoRecordingMJPEGPane, CDialog)
END_MESSAGE_MAP()


	// CVideoRecordingMJPEGPane message handlers

BOOL CVideoRecordingMJPEGPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_edit_mjpegCompressionLevel.SetWindowText(MJPEG_QUALITY_DEF);
	m_spin_mjpegCompressionLevel.SetRange(MJPEG_QUALITY_MIN, MJPEG_QUALITY_MAX);
	m_spin_mjpegCompressionLevel.SetBuddy(GetDlgItem(IDC_EDIT_MJPEG_COMPRESSION));



	return TRUE;
}

BOOL CVideoRecordingMJPEGPane::GetQuality(unsigned int* quality)
{
	CString qualityTxt;
	m_edit_mjpegCompressionLevel.GetWindowText(qualityTxt);
	unsigned int qualityInt = atoi(qualityTxt);
	*quality = qualityInt;
	return ((*quality >= MJPEG_QUALITY_MIN) && (*quality <= MJPEG_QUALITY_MAX));
	//return (quality != 0);
}

// prevent base class from calling EndDialog() if Enter key hit
void CVideoRecordingMJPEGPane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CVideoRecordingMJPEGPane::OnCancel()
{
}
