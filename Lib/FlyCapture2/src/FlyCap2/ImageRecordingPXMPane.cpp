// ImageRecordingPXMPane.cpp : implementation file
//

#include "stdafx.h"
#include "ImageRecordingPXMPane.h"

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif


// CImageRecordingPXMPane dialog

IMPLEMENT_DYNAMIC(CImageRecordingPXMPane, CDialog)

	CImageRecordingPXMPane::CImageRecordingPXMPane(CWnd* pParent /*=NULL*/)
: CDialog(CImageRecordingPXMPane::IDD, pParent)
{

}

CImageRecordingPXMPane::~CImageRecordingPXMPane()
{
}

void CImageRecordingPXMPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_PXM_SAVE_AS_BINARY, m_chk_pxmSaveAsBinary);
}


	BEGIN_MESSAGE_MAP(CImageRecordingPXMPane, CDialog)
END_MESSAGE_MAP()


	// CImageRecordingPXMPane message handlers

BOOL CImageRecordingPXMPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_chk_pxmSaveAsBinary.SetCheck(TRUE);
	return TRUE;
}

BOOL CImageRecordingPXMPane::GetPxMBinaryFile( BOOL* binaryFile )
{
	*binaryFile = m_chk_pxmSaveAsBinary.GetCheck();
	return TRUE;
}

// prevent base class from calling EndDialog() if Enter key hit
void CImageRecordingPXMPane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CImageRecordingPXMPane::OnCancel()
{
}
