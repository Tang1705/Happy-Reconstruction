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
#include "LicenseDialog.h"


// LicenseDialog dialog

IMPLEMENT_DYNAMIC(LicenseDialog, CDialog)

	LicenseDialog::LicenseDialog(CWnd* pParent /*=NULL*/)
: CDialog(LicenseDialog::IDD, pParent)
	, m_licenseContent(_T(""))
{
	m_licenseContent = "The FlyCapture Software Development Kit (the \"Software\") is owned and copyrighted by FLIR Integrated Imaging Solutions, Inc.  All rights are reserved.\r\n";
	m_licenseContent += "The Original Purchaser is granted a license to use the Software subject to the following restrictions and limitations.\r\n";
	m_licenseContent += "1.	The license is to the Original Purchaser only, and is nontransferable unless you have received written permission of FLIR Integrated Imaging Solutions, Inc.\r\n";
	m_licenseContent += "2.	The Original Purchaser may use the Software only with FLIR Integrated Imaging Solutions, Inc. cameras owned by the Original Purchaser, including but not limited to, Flea, Flea2, Firefly2, Firefly MV, Dragonfly, Dragonfly2, Dragonfly Express or Scorpion Camera Modules.\r\n";
	m_licenseContent += "3.	The Original Purchaser may make back-up copies of the Software for his or her own use only, subject to the use limitations of this license.\r\n";
	m_licenseContent += "4.	Subject to s.5 below, the Original Purchaser may not engage in, nor permit third parties to engage in, any of the following:\r\n";
	m_licenseContent += "a)	Providing or disclosing the Software to third parties.\r\n";
	m_licenseContent += "b)	Making alterations or copies of any kind of the Software (except as specifically permitted in s.3 above).\r\n";
	m_licenseContent += "c)	Attempting to un-assemble, de-compile or reverse engineer the Software in any way.\r\n";
	m_licenseContent += "Granting sublicenses, leases or other rights in the Software to others.\r\n";
	m_licenseContent += "5.	Original Purchasers who are Original Equipment Manufacturers may make Derivative Products with the Software. Derivative Products are new software products developed, in whole or in part, using the Software and other FLIR Integrated Imaging Solutions, Inc. products.\r\n";
	m_licenseContent += "FLIR Integrated Imaging Solutions, Inc. hereby grants a license to Original Equipment Manufacturers to incorporate and distribute the libraries found in the Software with the Derivative Products.\r\n";
	m_licenseContent += "The components of any Derivative Product that contain the Software libraries may only be used with FLIR Integrated Imaging Solutions, Inc. products, or images derived from such products.\r\n";
	m_licenseContent += "5.1	By the distribution of the Software libraries with Derivative Products, Original Purchasers agree to:\r\n";
	m_licenseContent += "a)	not permit further redistribution of the Software libraries by end-user customers;\r\n";
	m_licenseContent += "b)	include a valid copyright notice on any Derivative Product; and\r\n";
	m_licenseContent += "c)	indemnify, hold harmless, and defend FLIR Integrated Imaging Solutions, Inc. from and against any claims or lawsuits, including attorney's fees, that arise or result from the use or distribution of any Derivative Product.\r\n";
	m_licenseContent += "6.	FLIR Integrated Imaging Solutions, Inc. reserves the right to terminate this license if there are any violations of its terms or if there is a default committed by the Original Purchaser.\r\n";
	m_licenseContent += "Upon termination, for any reason, all copies of the Software must be immediately returned to FLIR Integrated Imaging Solutions, Inc. and the Original Purchaser shall be liable to FLIR Integrated Imaging Solutions, Inc. for any and all damages suffered as a result of the violation or default.\r\n";

}

LicenseDialog::~LicenseDialog()
{
}

void LicenseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LICENSE_CONTENT, m_licenseContent);
}


	BEGIN_MESSAGE_MAP(LicenseDialog, CDialog)
END_MESSAGE_MAP()


	// LicenseDialog message handlers
