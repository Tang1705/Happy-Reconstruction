#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "Resource.h"

using namespace FlyCapture2;

// CVideoRecordingMJPEGPane dialog

class CVideoRecordingMJPEGPane : public CDialog
{
	DECLARE_DYNAMIC(CVideoRecordingMJPEGPane)

	public:
		CVideoRecordingMJPEGPane(CWnd* pParent = NULL);   // standard constructor
		virtual ~CVideoRecordingMJPEGPane();

		virtual BOOL OnInitDialog();
		virtual void OnOK();
		virtual void OnCancel();

		BOOL GetQuality(unsigned int*);


		// Dialog Data
		enum { IDD = IDD_PANE_VIDEO_MJPEG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()


			static const unsigned int  MJPEG_QUALITY_MIN = 1;
		static const unsigned int MJPEG_QUALITY_MAX = 100;
		static const CString MJPEG_QUALITY_DEF;

		CEdit m_edit_mjpegCompressionLevel;
		CSpinButtonCtrl m_spin_mjpegCompressionLevel;
};
