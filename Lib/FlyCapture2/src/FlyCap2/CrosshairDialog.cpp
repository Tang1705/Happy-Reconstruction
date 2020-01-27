// CrosshairDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CrosshairDialog.h"

// CrosshairDialog dialog

IMPLEMENT_DYNAMIC(CrosshairDialog, CDialog)

CrosshairDialog::CrosshairDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CrosshairDialog::IDD, pParent)
	, m_length(0)
	, m_thickness(0)
	, m_xOffset(0)
	, m_yOffset(0)
	, m_xOffsetMin(0)
	, m_xOffsetMax(0)
	, m_yOffsetMin(0)
	, m_yOffsetMax(0)
{

}

CrosshairDialog::~CrosshairDialog()
{
}

void CrosshairDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_length);
	DDV_MinMaxFloat(pDX, m_length, 2, 200);
	DDX_Text(pDX, IDC_EDIT_THICKNESS, m_thickness);
	DDV_MinMaxLong(pDX, m_thickness, 1, 100);
	DDX_Control(pDX, IDC_EDIT_LENGTH, m_lengthEdit);
	DDX_Control(pDX, IDC_EDIT_THICKNESS, m_thicknessEdit);
	DDX_Text(pDX, IDC_XOffset, m_xOffset);
	DDV_MinMaxInt(pDX, m_xOffset, m_xOffsetMin, m_xOffsetMax);
	DDX_Text(pDX, IDC_YOffset, m_yOffset);
	DDV_MinMaxInt(pDX, m_yOffset, m_yOffsetMin, m_yOffsetMax);
	DDX_Control(pDX, IDC_YOffset, m_yOffsetEdit);
	DDX_Control(pDX, IDC_XOffset, m_xOffsetEdit);
}


BEGIN_MESSAGE_MAP(CrosshairDialog, CDialog)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CrosshairDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

	//Create the ToolTip control
	if( !m_ToolTip.Create(this))
	{
	   TRACE0("Unable to create the ToolTip!");
	}
	else
	{
	  m_ToolTip.AddTool( &m_lengthEdit, _T("Crosshair length in % of image width."));
	  m_ToolTip.AddTool( &m_thicknessEdit, _T("Crosshair line thickness in pixel."));
	  m_ToolTip.AddTool( &m_xOffsetEdit, _T("Crosshair offset in X direction. (0,0) is image center."));
	  m_ToolTip.AddTool( &m_yOffsetEdit, _T("Crosshair offset in Y direction. (0,0) is image center."));

	  m_ToolTip.Activate(TRUE);
	}

    return TRUE;
}

BOOL CrosshairDialog::PreTranslateMessage(MSG* pMsg)
{
     m_ToolTip.RelayEvent(pMsg);

     return CDialog::PreTranslateMessage(pMsg);
}

float CrosshairDialog::GetCrosshairLength()
{
	return m_length;
}

long CrosshairDialog::GetCrosshairThickness()
{
	return m_thickness;
}

void CrosshairDialog::SetCrosshairLength(float length)
{
	m_length = length;
}

void CrosshairDialog::SetCrosshairThickness(long thickness)
{
	m_thickness = thickness;
}

int CrosshairDialog::GetCrosshairXOffset()
{
	return m_xOffset;
}

int CrosshairDialog::GetCrosshairYOffset()
{
	return m_yOffset;
}

void CrosshairDialog::SetCrosshairXOffset(int xOffset)
{
	m_xOffset = xOffset;
}

void CrosshairDialog::SetCrosshairYOffset(int yOffset)
{
	m_yOffset = yOffset;
}

void CrosshairDialog::SetCrosshairXOffsetMinMax(int min, int max)
{
	m_xOffsetMin = min;
	m_xOffsetMax = max;
}

void CrosshairDialog::SetCrosshairYOffsetMinMax(int min, int max)
{
	m_yOffsetMin = min;
	m_yOffsetMax = max;
}


// CrosshairDialog message handlers
