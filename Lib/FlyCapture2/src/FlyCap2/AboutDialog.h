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

#include "LicenseDialog.h"
#pragma once


// AboutDialog dialog

class AboutDialog : public CDialog
{
	DECLARE_DYNAMIC(AboutDialog)

	public:
		AboutDialog(CWnd* pParent = NULL);   // standard constructor
		virtual ~AboutDialog();

		// Dialog Data
		enum { IDD = IDD_ABOUTBOX };

	protected:
		LicenseDialog m_licenseDlg;
		CString m_versionInfo;
		CString m_buildInfo;
		virtual BOOL OnInitDialog();
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		DECLARE_MESSAGE_MAP()
	public:
			afx_msg void OnButtonLicense();
};
