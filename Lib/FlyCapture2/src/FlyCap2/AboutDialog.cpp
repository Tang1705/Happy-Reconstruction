//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================


#include "stdafx.h"
#include "FlyCap2_MFC.h"
#include "AboutDialog.h"
#include "Utilities.h"


// AboutDialog dialog

IMPLEMENT_DYNAMIC(AboutDialog, CDialog)

	AboutDialog::AboutDialog(CWnd* pParent /*=NULL*/)
: CDialog(AboutDialog::IDD, pParent)
	, m_versionInfo(_T("FlyCapture2"))
	 , m_buildInfo(_T(""))
{
	m_buildInfo.Format(
			"Image acquisition and camera\r\ncontrol application for FlyCapture2.\r\nBuilt: %s %s",
			__DATE__,
			__TIME__ );

	FlyCapture2::FC2Version fc2Version;
	FlyCapture2::Utilities::GetLibraryVersion(&fc2Version);

	m_versionInfo.Format(
			"FlyCapture2 %u.%u.%u.%u",
			fc2Version.major,
			fc2Version.minor,
			fc2Version.type,
			fc2Version.build);
}

AboutDialog::~AboutDialog()
{
	m_licenseDlg.DestroyWindow();
}

void AboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VERSION, m_versionInfo);
	DDX_Text(pDX, IDC_BUILD_INFO, m_buildInfo);
}

	BEGIN_MESSAGE_MAP(AboutDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LICENSE, &AboutDialog::OnButtonLicense)
END_MESSAGE_MAP()


	// AboutDialog message handlers


BOOL AboutDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CFont newFont;
	LOGFONT LogFont;
	LogFont.lfWeight = FW_BOLD;
	newFont.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_VERSION)->SetFont(&newFont);
	if (m_licenseDlg.Create(IDD_LICENSE,this) == FALSE)
	{
		GetDlgItem(IDC_BUTTON_LICENSE)->EnableWindow(FALSE);
		MessageBox("Error creating license dialog box.","Error",MB_OK);
	}

	return TRUE;
}

void AboutDialog::OnButtonLicense()
{
	m_licenseDlg.ShowWindow(SW_SHOW);
}
