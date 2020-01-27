#pragma once

#include <afxwin.h>
#include "Resource.h"
#include "afxcmn.h"

// CrosshairDialog dialog

class CrosshairDialog : public CDialog
{
	DECLARE_DYNAMIC(CrosshairDialog)

public:
	CrosshairDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CrosshairDialog();

	float GetCrosshairLength();
	long GetCrosshairThickness();
	void SetCrosshairXOffsetMinMax(int min, int max);
	void SetCrosshairYOffsetMinMax(int min, int max);
	void SetCrosshairLength(float length);
	void SetCrosshairThickness(long thickness);
	int GetCrosshairXOffset();
	int GetCrosshairYOffset();
	void SetCrosshairXOffset(int xOffset);
	void SetCrosshairYOffset(int yOffset);
	BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
// Dialog Data
	enum { IDD = IDD_DIALOG_CROSSHAIR_DIMENSION };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CToolTipCtrl m_ToolTip;
	DECLARE_MESSAGE_MAP()
public:
	float m_length;
	long m_thickness;
	CEdit m_lengthEdit;
	CEdit m_thicknessEdit;
	// X-Offset for Crosshair. (0,0) is the center of image.
	int m_xOffset;
	// Y Offset for Crosshair. (0,0) is the center of image.
	int m_yOffset;
	int m_xOffsetMin;
	int m_xOffsetMax;
	int m_yOffsetMin;
	int m_yOffsetMax;
	CEdit m_yOffsetEdit;
	CEdit m_xOffsetEdit;
};
