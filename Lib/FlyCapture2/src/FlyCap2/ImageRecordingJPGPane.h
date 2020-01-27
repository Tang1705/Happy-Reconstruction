#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "RecordingDialogCommon.h"
#include "Resource.h"

using namespace FlyCapture2;

// CImageRecordingJPGPane dialog

class CImageRecordingJPGPane : public CDialog
{
	DECLARE_DYNAMIC(CImageRecordingJPGPane)

	public:
		CImageRecordingJPGPane(CWnd* pParent = NULL);   // standard constructor
		virtual ~CImageRecordingJPGPane();

		virtual BOOL OnInitDialog();
		virtual void OnOK();
		virtual void OnCancel();
		BOOL GetJPEGQuality( unsigned int* quality );
		BOOL GetJPEGProgressive( BOOL* progressive );

		// Dialog Data
		enum { IDD = IDD_PANE_IMAGE_JPG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			CButton m_chk_jpegProgressive;
		CEdit m_edit_jpegCompression;
		CSpinButtonCtrl m_spin_jpegCompression;

		//BOOL ConvertToInt(CString* text, unsigned int* integer);
};
