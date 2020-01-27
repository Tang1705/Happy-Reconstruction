// VideoRecordingH264Pane.cpp : implementation file
//

#include "stdafx.h"
#include "VideoRecordingH264Pane.h"

//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
#include "afxdlgs.h"
#else
#include "afxdialogex.h"
#endif


// CVideoRecordingH264Pane dialog

const CString CVideoRecordingH264Pane::H264_BITRATE_DEF = "1000000";

IMPLEMENT_DYNAMIC(CVideoRecordingH264Pane, CDialog)

	CVideoRecordingH264Pane::CVideoRecordingH264Pane(CWnd* pParent /*=NULL*/)
: CDialog(CVideoRecordingH264Pane::IDD, pParent)
{

}

CVideoRecordingH264Pane::~CVideoRecordingH264Pane()
{
}

void CVideoRecordingH264Pane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_H264_BITRATE, m_edit_h264Bitrate);
	DDX_Control(pDX, IDC_SPIN_H264_BITRATE, m_spin_h264Bitrate);
}


	BEGIN_MESSAGE_MAP(CVideoRecordingH264Pane, CDialog)
END_MESSAGE_MAP()


	// CVideoRecordingH264Pane message handlers

BOOL CVideoRecordingH264Pane::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_edit_h264Bitrate.SetWindowText(H264_BITRATE_DEF);
	m_spin_h264Bitrate.SetRange32(H264_BITRATE_MIN, H264_BITRATE_MAX);
	m_spin_h264Bitrate.SetBuddy(GetDlgItem(IDC_EDIT_H264_BITRATE));



	return TRUE;
}

BOOL CVideoRecordingH264Pane::GetBitrate(unsigned int* bitrate)
{
	CString bitrateTxt;
	m_edit_h264Bitrate.GetWindowText(bitrateTxt);
	bitrateTxt.Remove(',');
	unsigned int bitrateInt = atoi(bitrateTxt);
	*bitrate = bitrateInt;
	return ((*bitrate >= H264_BITRATE_MIN) && (*bitrate <= H264_BITRATE_MAX));
	//return (bitrate != 0);
}

unsigned int CVideoRecordingH264Pane::GetBitrateMin()
{
	return H264_BITRATE_MIN;
}

unsigned int CVideoRecordingH264Pane::GetBitrateMax()
{
	return H264_BITRATE_MAX;
}

// prevent base class from calling EndDialog() if Enter key hit
void CVideoRecordingH264Pane::OnOK()
{
}

// prevent base class from calling EndDialog() if Esc key hit
void CVideoRecordingH264Pane::OnCancel()
{
}
