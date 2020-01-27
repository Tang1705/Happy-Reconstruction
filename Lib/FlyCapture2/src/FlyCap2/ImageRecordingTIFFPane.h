#pragma once

#include "afxwin.h"
#include "Resource.h"
#include "RecordingDialogCommon.h"

using namespace FlyCapture2;

// CImageRecordingTIFFPane dialog


const char TIFFCompressionList[][FlyCap2RecordingDialog::MAX_COMBO_STRING] =
{
	"None",
	"Packbits",
	"Deflate",
	"Adobe Deflate",
	"CCITTFAX3",
	"CCITTFAX4",
	"LZW",
	"JPEG"
};


class CImageRecordingTIFFPane : public CDialog
{
	DECLARE_DYNAMIC(CImageRecordingTIFFPane)

	public:
		CImageRecordingTIFFPane(CWnd* pParent = NULL);   // standard constructor
		virtual ~CImageRecordingTIFFPane();

		virtual BOOL OnInitDialog();
		virtual void OnOK();
		virtual void OnCancel();
		BOOL GetTIFFCompression( TIFFOption::CompressionMethod* compression );

		// Dialog Data
		enum { IDD = IDD_PANE_IMAGE_TIFF };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			CComboBox m_combo_tiffCompressionMethod;
};
