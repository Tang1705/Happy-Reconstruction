// ImageRecordingJPGPane.cpp : implementation file
//

#include "stdafx.h"
#include "ImageRecordingJPGPane.h"


const unsigned int MIN_JPG_QUALITY = 1;
const unsigned int MAX_JPG_QUALITY = 100;

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif


// CImageRecordingJPGPane dialog

IMPLEMENT_DYNAMIC(CImageRecordingJPGPane, CDialog)

	CImageRecordingJPGPane::CImageRecordingJPGPane(CWnd* pParent /*=NULL*/)
: CDialog(CImageRecordingJPGPane::IDD, pParent)
{

}

CImageRecordingJPGPane::~CImageRecordingJPGPane()
{
}

void CImageRecordingJPGPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_JPEG_SAVE_PROGRESSIVE, m_chk_jpegProgressive);
	DDX_Control(pDX, IDC_EDIT_JPEG_COMPRESSION, m_edit_jpegCompression);
	DDX_Control(pDX, IDC_SPIN_JPEG_COMPRESSION, m_spin_jpegCompression);
}


	BEGIN_MESSAGE_MAP(CImageRecordingJPGPane, CDialog)
END_MESSAGE_MAP()


	// CImageRecordingJPGPane message handlers

BOOL CImageRecordingJPGPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_chk_jpegProgressive.SetCheck(FALSE);
	m_edit_jpegCompression.SetWindowText("75");
	m_spin_jpegCompression.SetRange(MIN_JPG_QUALITY, MAX_JPG_QUALITY);
	m_spin_jpegCompression.SetBuddy(GetDlgItem(IDC_EDIT_JPEG_COMPRESSION));
	return TRUE;
}

BOOL CImageRecordingJPGPane::GetJPEGQuality( unsigned int* quality )
{
	CString qualityTxt;
	m_edit_jpegCompression.GetWindowText(qualityTxt);
	return (!(qualityTxt.IsEmpty())										&&
			FlyCap2RecordingDialog::ConvertToInt(&qualityTxt, quality)	&&
			*quality >= MIN_JPG_QUALITY									&&
			*quality <= MAX_JPG_QUALITY);
}

BOOL CImageRecordingJPGPane::GetJPEGProgressive( BOOL* progressive )
{
	*progressive = m_chk_jpegProgressive.GetCheck();
	return TRUE;
}

// prevent base class from calling EndDialog() if Enter key hit
void CImageRecordingJPGPane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CImageRecordingJPGPane::OnCancel()
{
}
