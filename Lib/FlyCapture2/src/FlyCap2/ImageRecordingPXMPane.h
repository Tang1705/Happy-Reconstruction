#pragma once
#include "afxwin.h"

#include "Resource.h"

using namespace FlyCapture2;

// CImageRecordingPXMPane dialog

class CImageRecordingPXMPane : public CDialog
{
	DECLARE_DYNAMIC(CImageRecordingPXMPane)

	public:
		CImageRecordingPXMPane(CWnd* pParent = NULL);   // standard constructor
		virtual ~CImageRecordingPXMPane();

		virtual BOOL OnInitDialog();
		virtual void OnOK();
		virtual void OnCancel();
		BOOL GetPxMBinaryFile( BOOL* binaryFile );

		// Dialog Data
		enum { IDD = IDD_PANE_IMAGE_PXM };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
			CButton m_chk_pxmSaveAsBinary;
};
