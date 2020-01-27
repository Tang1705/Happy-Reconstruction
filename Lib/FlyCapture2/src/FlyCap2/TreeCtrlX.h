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

// Setting color and font attribute for individual items
// www.codeguru.com/cpp/controls/treeview/misc-advanced/article.php/c633/

#pragma once

class CTreeCtrlX : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeCtrlX)

	public:
		CTreeCtrlX();
		virtual ~CTreeCtrlX();
		void CTreeCtrlX::SetItemColor(HTREEITEM hItem, COLORREF color);
		BOOL CTreeCtrlX::GetItemFont(HTREEITEM hItem, LOGFONT * plogfont);
		COLORREF CTreeCtrlX::GetItemColor(HTREEITEM hItem);
		void CTreeCtrlX::ResetMap();
		afx_msg void OnPaint();

	protected:
		struct Color_Font
		{
			COLORREF color;
			LOGFONT  logfont;
		};

		CMap< void*, void*, Color_Font, Color_Font& > m_mapColorFont ;

		DECLARE_MESSAGE_MAP()
	public:
			afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


