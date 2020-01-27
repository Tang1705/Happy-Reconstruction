// ImageRecordingPNGPane.cpp : implementation file
//

#include "stdafx.h"
#include "ImageRecordingPNGPane.h"
#include "RecordingDialogCommon.h"

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif


// CImageRecordingPNGPane dialog

IMPLEMENT_DYNAMIC(CImageRecordingPNGPane, CDialog)

	CImageRecordingPNGPane::CImageRecordingPNGPane(CWnd* pParent /*=NULL*/)
: CDialog(CImageRecordingPNGPane::IDD, pParent)
{

}

CImageRecordingPNGPane::~CImageRecordingPNGPane()
{
}

void CImageRecordingPNGPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_PNG_INTERLEAVED, m_chk_pngInterleaved);
	DDX_Control(pDX, IDC_COMBO_PNG_COMPRESSION_LEVEL, m_combo_pngCompressionLevel);
}


	BEGIN_MESSAGE_MAP(CImageRecordingPNGPane, CDialog)
END_MESSAGE_MAP()


	// CImageRecordingPNGPane message handlers

BOOL CImageRecordingPNGPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	char temp[FlyCap2RecordingDialog::MAX_COMBO_STRING];
	for (int i = 0; i < 10; i++)
	{
		sprintf(temp, "%d", i);
		m_combo_pngCompressionLevel.AddString(temp);
	}
	m_combo_pngCompressionLevel.SetCurSel(6);
	m_chk_pngInterleaved.SetCheck(FALSE);
	return TRUE;
}

BOOL CImageRecordingPNGPane::GetPNGInterlaced( BOOL* interlaced )
{
	*interlaced = m_chk_pngInterleaved.GetCheck();
	return TRUE;
}

BOOL CImageRecordingPNGPane::GetPNGCompression( unsigned int* compression )
{
	*compression = m_combo_pngCompressionLevel.GetCurSel();
	return TRUE;
}

// prevent base class from calling EndDialog() if Enter key hit
void CImageRecordingPNGPane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CImageRecordingPNGPane::OnCancel()
{
}
