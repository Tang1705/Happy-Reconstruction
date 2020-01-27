// CImageRecordingBMPPane.cpp : implementation file
//

#include "stdafx.h"
#include "ImageRecordingBMPPane.h"

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif


// CImageRecordingBMPPane dialog

IMPLEMENT_DYNAMIC(CImageRecordingBMPPane, CDialog)

	CImageRecordingBMPPane::CImageRecordingBMPPane(CWnd* pParent /*=NULL*/)
: CDialog(CImageRecordingBMPPane::IDD, pParent)
{

}

CImageRecordingBMPPane::~CImageRecordingBMPPane()
{
}

void CImageRecordingBMPPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_BMP_8BIT_INDEXED_COLOR, m_chk_8bitColorIndexed);
}


	BEGIN_MESSAGE_MAP(CImageRecordingBMPPane, CDialog)
END_MESSAGE_MAP()


	// CImageRecordingBMPPane message handlers

BOOL CImageRecordingBMPPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_chk_8bitColorIndexed.SetCheck(FALSE);
	return TRUE;
}

BOOL CImageRecordingBMPPane::GetBMP8bitIndexedColor( BOOL* indexedColor )
{
	*indexedColor = m_chk_8bitColorIndexed.GetCheck();
	return TRUE;
}

// prevent base class from calling EndDialog() if Enter key hit
void CImageRecordingBMPPane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CImageRecordingBMPPane::OnCancel()
{
}
