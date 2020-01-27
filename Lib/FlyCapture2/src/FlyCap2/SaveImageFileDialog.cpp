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
#include "SaveImageFileDialog.h"
#include <dlgs.h>


// CSaveImageFileDialog

IMPLEMENT_DYNAMIC(CSaveImageFileDialog, CFileDialog)

	//[Bug 32070 - afxdialogex.h not supported in VS 2005, so this check was included for compatability.
#if (_MSC_VER == 1400)
	CSaveImageFileDialog::CSaveImageFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
			DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd, 0),
		m_displayBayerTileCheckbox(false),
		m_saveBayerTileSelected(false),
		m_chk_saveBayerTile()
{
}
#else
CSaveImageFileDialog::CSaveImageFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
	CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd, 0, false),
	m_displayBayerTileCheckbox(false),
	m_saveBayerTileSelected(false),
	m_chk_saveBayerTile()
{
}
#endif


CSaveImageFileDialog::~CSaveImageFileDialog()
{
}


	BEGIN_MESSAGE_MAP(CSaveImageFileDialog, CFileDialog)
END_MESSAGE_MAP()



	// CSaveImageFileDialog message handlers


BOOL CSaveImageFileDialog::OnInitDialog()
{
	const unsigned int EXTRA_HEIGHT = 60;

	if (m_displayBayerTileCheckbox)
	{
		CWnd* parentWindow = GetParent();

		RECT rect;

		parentWindow->GetWindowRect(&rect);
		parentWindow->SetWindowPos(NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top + EXTRA_HEIGHT, SWP_NOMOVE);
		parentWindow->GetWindowRect(&rect);
		parentWindow->ScreenToClient(&rect);

		RECT ctrlRect;
		CWnd* wndCtrl = parentWindow->GetDlgItem(stc2);
		wndCtrl->GetWindowRect(&ctrlRect);
		parentWindow->ScreenToClient(&ctrlRect);

		rect.left   = ctrlRect.left;
		rect.top	= ctrlRect.bottom + 8;
		rect.right  = rect.right-100;
		rect.bottom = rect.top + 60;

		m_chk_saveBayerTile.Create("Save the raw (bayer-tile) image regardless of the currently active color-processing algorithm", BS_AUTOCHECKBOX | BS_MULTILINE, rect, parentWindow,  4800);
		m_chk_saveBayerTile.ShowWindow(SW_SHOW);
	}

	CFileDialog::OnInitDialog();
	return TRUE;
}

void CSaveImageFileDialog::IsRawImage(bool isRaw)
{
	m_displayBayerTileCheckbox = isRaw;
}

BOOL CSaveImageFileDialog::IsSaveBayerTileSelected()
{
	return m_saveBayerTileSelected;
}

BOOL CSaveImageFileDialog::OnFileNameOK()
{
	m_saveBayerTileSelected = m_chk_saveBayerTile.GetCheck() == BST_CHECKED;
	return CFileDialog::OnFileNameOK();
}
