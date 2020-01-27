// ImageRecordingJPG2KPane.cpp : implementation file
//

#include "stdafx.h"
#include "ImageRecordingJPG2KPane.h"

const unsigned int MIN_JPG2K_QUALITY = 1;
const unsigned int MAX_JPG2K_QUALITY = 512;

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif


// CImageRecordingJPG2KPane dialog

IMPLEMENT_DYNAMIC(CImageRecordingJPG2KPane, CDialog)

	CImageRecordingJPG2KPane::CImageRecordingJPG2KPane(CWnd* pParent /*=NULL*/)
: CDialog(CImageRecordingJPG2KPane::IDD, pParent)
{

}

CImageRecordingJPG2KPane::~CImageRecordingJPG2KPane()
{
}

void CImageRecordingJPG2KPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_JPEG2K_COMPRESSION_LEVEL, m_edit_jpg2kCompressionLevel);
	DDX_Control(pDX, IDC_SPIN_JPEG2K_COMPRESSION_LEVEL, m_spin_jpeg2kCompressionLevel);
}


	BEGIN_MESSAGE_MAP(CImageRecordingJPG2KPane, CDialog)
END_MESSAGE_MAP()


	// CImageRecordingJPG2KPane message handlers

BOOL CImageRecordingJPG2KPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_edit_jpg2kCompressionLevel.SetWindowText("16");
	m_spin_jpeg2kCompressionLevel.SetRange(MIN_JPG2K_QUALITY, MAX_JPG2K_QUALITY);
	m_spin_jpeg2kCompressionLevel.SetBuddy(GetDlgItem(IDC_EDIT_JPEG2K_COMPRESSION_LEVEL));
	return TRUE;
}

BOOL CImageRecordingJPG2KPane::GetJPEG2KQuality( unsigned int* quality )
{
	CString qualityTxt;
	m_edit_jpg2kCompressionLevel.GetWindowText(qualityTxt);
	return (!(qualityTxt.IsEmpty())										&&
			FlyCap2RecordingDialog::ConvertToInt(&qualityTxt, quality)	&&
			*quality >= MIN_JPG2K_QUALITY								&&
			*quality <= MAX_JPG2K_QUALITY);
}

// prevent base class from calling EndDialog() if Enter key hit
void CImageRecordingJPG2KPane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CImageRecordingJPG2KPane::OnCancel()
{
}
