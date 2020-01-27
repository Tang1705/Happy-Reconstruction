// ImageRecordingTIFFPane.cpp : implementation file
//

#include "stdafx.h"
#include "ImageRecordingTIFFPane.h"

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif

// CImageRecordingTIFFPane dialog

IMPLEMENT_DYNAMIC(CImageRecordingTIFFPane, CDialog)

	CImageRecordingTIFFPane::CImageRecordingTIFFPane(CWnd* pParent /*=NULL*/)
: CDialog(CImageRecordingTIFFPane::IDD, pParent)
{

}

CImageRecordingTIFFPane::~CImageRecordingTIFFPane()
{
}

void CImageRecordingTIFFPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TIFF_COMPRESSION_METHOD, m_combo_tiffCompressionMethod);
}


	BEGIN_MESSAGE_MAP(CImageRecordingTIFFPane, CDialog)
END_MESSAGE_MAP()


	// CImageRecordingTIFFPane message handlers

BOOL CImageRecordingTIFFPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	for (int i = 0; i < TIFFOption::JPEG; i++)
	{
		m_combo_tiffCompressionMethod.AddString(TIFFCompressionList[i]);
	}
	m_combo_tiffCompressionMethod.SetCurSel(0);
	return TRUE;
}

BOOL CImageRecordingTIFFPane::GetTIFFCompression( TIFFOption::CompressionMethod* compression )
{
	*compression = (TIFFOption::CompressionMethod)(m_combo_tiffCompressionMethod.GetCurSel()+1);
	return TRUE;
}

// prevent base class from calling EndDialog() if Enter key hit
void CImageRecordingTIFFPane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CImageRecordingTIFFPane::OnCancel()
{
}
