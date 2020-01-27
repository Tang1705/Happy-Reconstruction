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

#include "stdafx.h"
#include "TreeCtrlX.h"

IMPLEMENT_DYNAMIC(CTreeCtrlX, CTreeCtrl)

CTreeCtrlX::CTreeCtrlX()
{
}

CTreeCtrlX::~CTreeCtrlX()
{
}

	BEGIN_MESSAGE_MAP(CTreeCtrlX, CTreeCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CTreeCtrlX::ResetMap()
{
	m_mapColorFont.RemoveAll();
}

void CTreeCtrlX::SetItemColor(HTREEITEM hItem, COLORREF color)
{
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		cf.logfont.lfFaceName[0] = '\0';
	cf.color = color;
	m_mapColorFont[hItem] = cf;
}

BOOL CTreeCtrlX::GetItemFont(HTREEITEM hItem, LOGFONT * plogfont)
{
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		return FALSE;
	if( cf.logfont.lfFaceName[0] == '\0' )
		return FALSE;
	*plogfont = cf.logfont;
	return TRUE;

}

COLORREF CTreeCtrlX::GetItemColor(HTREEITEM hItem)
{
	// Returns (COLORREF)-1 if color was not set
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		return (COLORREF)-1;
	return cf.color;

}

// CTreeCtrlX message handlers

BOOL CTreeCtrlX::OnEraseBkgnd(CDC* pDC)
{
	// This should eliminate the flickering
	return FALSE;
}

void CTreeCtrlX::OnPaint()
{
	CPaintDC dc(this);

	// Create a memory DC compatible with the paint DC
	CDC memDC;

	memDC.CreateCompatibleDC( &dc );

	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	GetClientRect(&rcClient);

	// Select a compatible bitmap into the memory DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	memDC.SelectObject( &bitmap );

	// Set clip region to be same as that in paint DC
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcClip );
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject();


	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );


	HTREEITEM hItem = GetFirstVisibleItem();

	int n = GetVisibleCount()+1;
	while( hItem && n--)
	{
		CRect rect;

		// Do not meddle with selected items or drop highlighted items
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		Color_Font cf;

		if ( !(GetItemState( hItem, selflag ) & selflag )
				&& m_mapColorFont.Lookup( hItem, cf ))
		{
			CFont *pFontDC;
			CFont fontDC;
			LOGFONT logfont;

			if( cf.logfont.lfFaceName[0] != '\0' )
			{
				logfont = cf.logfont;
			}
			else
			{
				// No font specified, so use window font
				CFont *pFont = GetFont();
				pFont->GetLogFont( &logfont );
			}

			fontDC.CreateFontIndirect( &logfont );
			pFontDC = memDC.SelectObject( &fontDC );

			if( cf.color != (COLORREF)-1 )
				memDC.SetTextColor( cf.color );

			CString sItem = GetItemText( hItem );

			GetItemRect( hItem, &rect, TRUE );
			memDC.SetBkColor( GetSysColor( COLOR_WINDOW ) );
			memDC.TextOut( rect.left+2, rect.top+1, sItem );

			memDC.SelectObject( pFontDC );
		}
		hItem = GetNextVisibleItem( hItem );
	}


	dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC,
			rcClip.left, rcClip.top, SRCCOPY );
}

