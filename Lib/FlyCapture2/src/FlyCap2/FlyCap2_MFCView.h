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

#define MAX_ZOOM_LEVEL 10.0
#define MIN_ZOOM_LEVEL 0.1

#pragma once
#include "afxcmn.h"

#include "FrameRateCounter.h"
#include "InformationPane.h"
#include "CrosshairDialog.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "afxwin.h"
#include "TreeCtrlX.h"

class CFlyCap2_MFCView : public CFormView
{
	private:
		static const int sk_camInfoWidth = 280;
		static const int sk_scrollbarThickness = 20;
		static const int sk_scrollbarPageChangeValue = 50;
	public:
		enum{ IDD = IDD_FLYCAP2_MFC_FORM };

		void ResetViewConfig();
		CFlyCap2_MFCDoc* GetDocument() const;
		CTreeCtrlX* pCamInfoTreeView;
		double GetDisplayedFrameRate();
		int GetXOffset();
		void GetMinSize(unsigned int* width,unsigned int* height);
		RECT GetDisplaySize();//get the area contains drawing area and scrollbar
		void GetPixelPositionFromImage(int* pX, int* pY);
		double GetZoomLevel();
		void SetToWindowedMode();
		void SetToFullScreenMode();

		void SetCrosshairLength(float length);
		void SetCrosshairThickness(long thickness);

		float GetCrosshairLength();
		long GetCrosshairThickness();

		void SetCrosshairXOffset(int xOffset);
		void SetCrosshairYOffset(int yOffset);

		int GetCrosshairXOffset();
		int GetCrosshairYOffset();

		void UpdateCameraInfoData();
		virtual void OnDraw(CDC* pDC);
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		virtual ~CFlyCap2_MFCView();

#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

	protected:
		FrameRateCounter m_displayedFrameRate;
		InformationPane  m_infoPane;
		FlyCapture2::Image m_holdImage;
		CBitmap m_logo;

		bool m_openGLInitialized;
		bool m_direct2DInitialized;
		bool m_camInfoDataInitialized;
		bool m_viewInitialized;
		bool m_isStreaming;
		bool m_enableCameraInformationPanel;

		bool m_bTreeExpanded;
		bool m_bTreeLinkeded;

		bool m_isDrawingImage;
		bool m_showCrosshair;
		COLORREF m_colorCrosshair;
		bool m_isFullScreen;
		bool m_isStretchToFit;
		int m_currentSizeX;
		int m_currentSizeY;

		RECT m_imageRect;
		void AdjustDrawingArea();
		void AdjustViewSize(int cx, int cy);
		void AdjustToFullScreenSize(int cx, int cy);
		double m_zoomLevel;
		double m_prevZoomLevel;
		void ChangeScrollbarPositionValue(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

#ifdef DIRECT2D_SUPPORT
		/** Direct2D rendering context */
		HMODULE m_hD2DModule;
		ID2D1Factory *m_pD2DFactory;
		ID2D1Bitmap *m_pBitmap;
		ID2D1SolidColorBrush* m_pBrush;
		ID2D1HwndRenderTarget *m_pRenderTarget;
#endif

		std::vector<float> m_zoomLevelTable;
		unsigned int m_zoomLevelIndex;

		/** OpenGL rendering context. */
		HGLRC m_hRC;

		/** Device context for OpenGL drawing. */
		CDC* m_pDC;
		bool   m_PBOSupported;
		bool m_skipPBO;
		GLuint m_PBO;

		HCURSOR m_hHand;
		HCURSOR m_hArrow;

		static const unsigned int sk_maxNumTextures = 36;
		GLuint m_imageTextures[sk_maxNumTextures];

		bool InitializeOpenGL();
		void InitializeImageTexture();
		bool InitializeD2D();

		int m_crosshairThickness;
		float m_crosshairLength;
		int m_crosshairXOffset;
		int m_crosshairYOffset;

#ifdef DIRECT2D_SUPPORT
		// This method creates resources which are bound to a particular D3D device.
		HRESULT CreateDeviceResources();
		void DiscardDeviceResources();
#endif

		bool SetupPixelFormat();
		void DrawOGLImage(int width, int height, const unsigned char* pImagePixels);
		void BindGL( );
		void UnbindGL( );
		void UpdateCameraInfoPanel();
		void LinkTreeView();
		CFlyCap2_MFCView();
		DECLARE_DYNCREATE(CFlyCap2_MFCView)
			virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		// Generated message map functions
	protected:
		DECLARE_MESSAGE_MAP()
	public:
			virtual void OnInitialUpdate();
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg BOOL OnEraseBkgnd(CDC* pDC);
			afx_msg void OnViewShowInformationPanel();
			afx_msg void OnUpdateViewDrawImage(CCmdUI *pCmdUI);
			afx_msg void OnViewDrawImage();
			afx_msg void OnViewChangeCrosshairColor();
			afx_msg void OnDrawCrosshairClick();
			afx_msg void OnUpdateViewDrawCrosshair(CCmdUI *pCmdUI);
			afx_msg void OnUpdateViewFullscreen(CCmdUI *pCmdUI);
			afx_msg void OnViewEnableOpenGL();
			afx_msg void OnZoomIn();
			afx_msg void OnZoomOut();
			afx_msg void OnBtnOriginalImageSize();
			afx_msg void OnUpdateZoomIn(CCmdUI *pCmdUI);
			afx_msg void OnUpdateZoomOut(CCmdUI *pCmdUI);
			afx_msg void OnUpdateOriginalZoom(CCmdUI *pCmdUI);
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
			afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
			afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
			afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg void OnUpdateViewStretchToFit(CCmdUI *pCmdUI);
			afx_msg void OnViewStretchToFit();
			afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
			LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			afx_msg void OnFileNewCamera();
			afx_msg void OnUpdateViewShowInformationPanel(CCmdUI *pCmdUI);
			//	afx_msg void OnNMClickInfotree(NMHDR *pNMHDR, LRESULT *pResult);
			afx_msg void OnNMDblclkInfotree(NMHDR *pNMHDR, LRESULT *pResult);
			afx_msg void OnTreeGetInfoTip(NMHDR *pNMHDR, LRESULT *pResult);
			afx_msg void OnViewEnableDirect2D();
			afx_msg void OnViewEnableGDI();
			afx_msg void OnViewChangeCrosshairDimension();
};

#ifndef _DEBUG  // debug version in FlyCap2_MFCView.cpp
inline CFlyCap2_MFCDoc* CFlyCap2_MFCView::GetDocument() const
{ return reinterpret_cast<CFlyCap2_MFCDoc*>(m_pDocument); }
#endif

