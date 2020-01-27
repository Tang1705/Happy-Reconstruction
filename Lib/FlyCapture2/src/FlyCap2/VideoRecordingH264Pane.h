#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "Resource.h"

using namespace FlyCapture2;

// CVideoRecordingH264Pane dialog

class CVideoRecordingH264Pane : public CDialog
{
	DECLARE_DYNAMIC(CVideoRecordingH264Pane)

	public:
		CVideoRecordingH264Pane(CWnd* pParent = NULL);   // standard constructor
		virtual ~CVideoRecordingH264Pane();

		virtual BOOL OnInitDialog();
		virtual void OnOK();
		virtual void OnCancel();

		BOOL GetBitrate(unsigned int*);
		unsigned int GetBitrateMin();
		unsigned int GetBitrateMax();



		// Dialog Data
		enum { IDD = IDD_PANE_VIDEO_H264 };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()

			static const unsigned int H264_BITRATE_MIN = 1000;
		static const unsigned int H264_BITRATE_MAX = 1000000000;
		static const CString H264_BITRATE_DEF;

		CEdit m_edit_h264Bitrate;
		CSpinButtonCtrl m_spin_h264Bitrate;
};

