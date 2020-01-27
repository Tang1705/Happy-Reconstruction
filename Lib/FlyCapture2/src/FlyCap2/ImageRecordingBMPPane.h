#pragma once

#include "Resource.h"
#include "afxwin.h"

// CImageRecordingBMPPane dialog

class CImageRecordingBMPPane : public CDialog
{
	DECLARE_DYNAMIC(CImageRecordingBMPPane)

	public:
		CImageRecordingBMPPane(CWnd* pParent = NULL);   // standard constructor
		virtual ~CImageRecordingBMPPane();

		virtual BOOL OnInitDialog();
		virtual void OnOK();
		virtual void OnCancel();
		BOOL GetBMP8bitIndexedColor(BOOL* indexedColor);

		// Dialog Data
		enum { IDD = IDD_PANE_IMAGE_BMP };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()

			//CButton m_chk_8bitColorIndexed;
			CButton m_chk_8bitColorIndexed;
};
