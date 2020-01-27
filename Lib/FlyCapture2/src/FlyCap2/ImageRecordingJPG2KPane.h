#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Resource.h"
#include "RecordingDialogCommon.h"

using namespace FlyCapture2;

// CImageRecordingJPG2KPane dialog

class CImageRecordingJPG2KPane : public CDialog
{
	DECLARE_DYNAMIC(CImageRecordingJPG2KPane)

		virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	public:
	CImageRecordingJPG2KPane(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageRecordingJPG2KPane();

	BOOL GetJPEG2KQuality( unsigned int* quality );

	// Dialog Data
	enum { IDD = IDD_PANE_IMAGE_JPG2K };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
		CEdit m_edit_jpg2kCompressionLevel;
	CSpinButtonCtrl m_spin_jpeg2kCompressionLevel;
};
