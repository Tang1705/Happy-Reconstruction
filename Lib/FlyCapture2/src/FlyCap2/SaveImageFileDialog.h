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

#ifndef SAVE_IMAGE_DIALOG_H
#define SAVE_IMAGE_DIALOG_H

#include "afxcmn.h"
#include "afxdlgs.h"


class CSaveImageFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CSaveImageFileDialog)

	public:
		CSaveImageFileDialog(BOOL bOpenFileDialog,
				LPCTSTR lpszDefExt = NULL,
				LPCTSTR lpszFileName = NULL,
				DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
				LPCTSTR lpszFilter = NULL,
				CWnd* pParentWnd = NULL);
		virtual ~CSaveImageFileDialog();

		virtual BOOL OnInitDialog();
		BOOL IsSaveBayerTileSelected();

		void IsRawImage(bool);

	protected:
		virtual BOOL OnFileNameOK();

	protected:
		DECLARE_MESSAGE_MAP()

			CButton m_chk_saveBayerTile;
		bool m_saveBayerTileSelected;
		bool m_displayBayerTileCheckbox;
};
#endif
