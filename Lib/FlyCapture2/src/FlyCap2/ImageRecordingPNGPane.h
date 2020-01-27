#pragma once
#include "afxwin.h"

#include "Resource.h"

using namespace FlyCapture2;

// CImageRecordingPNGPane dialog

//const unsigned int MAX_COMBO_STRING = 64;

class CImageRecordingPNGPane : public CDialog
{
	DECLARE_DYNAMIC(CImageRecordingPNGPane)

	public:
		CImageRecordingPNGPane(CWnd* pParent = NULL);   // standard constructor
		virtual ~CImageRecordingPNGPane();

		virtual BOOL OnInitDialog();
		virtual void OnOK();
		virtual void OnCancel();
		BOOL GetPNGInterlaced( BOOL* interlaced );
		BOOL GetPNGCompression( unsigned int* compression );

		// Dialog Data
		enum { IDD = IDD_PANE_IMAGE_PNG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			CButton m_chk_pngInterleaved;
		CComboBox m_combo_pngCompressionLevel;
};
