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

#pragma managed
#include "FlyCap2CameraControl_ILBridge.h"
#include "FlyCap2CameraSelection_ILBridge.h"
#ifdef GENICAM
#include "FlyCap2PropertyGrid_ILBridge.h"
#endif
#include "AssemblyResolver.h"
#pragma unmanaged
#include "FlyCapture2GUI.h"

#include <string>

using namespace FlyCapture2_ILBridge;

namespace FlyCapture2
{
	struct CameraControlDlg::CamCtlData
	{
		ILBridge_CameraControlDialog* m_camControlDlg;
		AssemblyResolver::AssemblyResolver m_assemblyResolver;
	};

	CameraControlDlg::CameraControlDlg()
	{
		m_pCamCtlData = new CamCtlData();
		m_pCamCtlData->m_camControlDlg = new ILBridge_CameraControlDialog();
	}

	CameraControlDlg::~CameraControlDlg()
	{
		delete m_pCamCtlData->m_camControlDlg;
		delete m_pCamCtlData;
	}

	void CameraControlDlg::Connect( CameraBase* pCamera )
	{
		m_pCamCtlData->m_camControlDlg->Connect(pCamera);
	}

	void CameraControlDlg::Disconnect()
	{
		m_pCamCtlData->m_camControlDlg->Disconnect();
	}

	void CameraControlDlg::Show()
	{
		m_pCamCtlData->m_camControlDlg->Show();
	}

	void CameraControlDlg::Show(void* pParent)
	{
		m_pCamCtlData->m_camControlDlg->Show(pParent);
	}

	void CameraControlDlg::ShowModal()
	{
		m_pCamCtlData->m_camControlDlg->ShowModal();
	}

	void CameraControlDlg::ShowModal(void* pParent)
	{
		m_pCamCtlData->m_camControlDlg->Show(pParent);
	}
	void CameraControlDlg::Hide()
	{
		m_pCamCtlData->m_camControlDlg->Hide();
	}

	bool CameraControlDlg::IsVisible()
	{
		return m_pCamCtlData->m_camControlDlg->IsVisible();
	}

	void CameraControlDlg::SetTitle(const char *pTitle)
	{
		std::string titleStr(pTitle);
		std::wstring wideTitleStr(titleStr.begin(), titleStr.end());
		m_pCamCtlData->m_camControlDlg->SetTitle(wideTitleStr.c_str());
	}

	struct CameraSelectionDlg::CamSelectionData
	{
		ILBridge_CameraSelectionDialog* m_camSelectionDlg;
		AssemblyResolver::AssemblyResolver m_assemblyResolver;
	};

	CameraSelectionDlg::CameraSelectionDlg()
	{
		m_pCamSelectionData = new CamSelectionData();
		m_pCamSelectionData->m_camSelectionDlg = new ILBridge_CameraSelectionDialog();
	}

	CameraSelectionDlg::~CameraSelectionDlg()
	{
		delete m_pCamSelectionData->m_camSelectionDlg;
		delete m_pCamSelectionData;
	}

	void CameraSelectionDlg::ShowModal( bool* pOkSelected, PGRGuid* guidArray, unsigned int* size)
	{
		m_pCamSelectionData->m_camSelectionDlg->ShowModal(pOkSelected, guidArray, size);
	}

	void CameraSelectionDlg::SetTitle( const char *pTitle)
	{
		std::string titleStr(pTitle);
		std::wstring wideTitleStr(titleStr.begin(), titleStr.end());
		m_pCamSelectionData->m_camSelectionDlg->SetTitle(wideTitleStr.c_str());
	}
#ifdef GENICAM
	struct PropertyGridDlg::PropGridData
	{
		ILBridge_PropertyGridDialog * m_gridDlg;
		AssemblyResolver::AssemblyResolver m_assemblyResolver;
	};

	PropertyGridDlg::PropertyGridDlg()
	{
		m_pPropGridData = new PropGridData();
		m_pPropGridData->m_gridDlg = new ILBridge_PropertyGridDialog();
	}

	PropertyGridDlg::~PropertyGridDlg()
	{
		delete m_pPropGridData->m_gridDlg;
		delete m_pPropGridData;
	}

	void PropertyGridDlg::Connect( CameraBase* pCamera )
	{
		m_pPropGridData->m_gridDlg->Connect(pCamera);
	}

	void PropertyGridDlg::Connect( CameraBase* pCamera, const char* xmlPath )
	{
		m_pPropGridData->m_gridDlg->Connect(pCamera, xmlPath);
	}

	void PropertyGridDlg::Disconnect()
	{
		m_pPropGridData->m_gridDlg->Disconnect();
	}

	void PropertyGridDlg::Show()
	{
		m_pPropGridData->m_gridDlg->Show();
	}

	void PropertyGridDlg::Show(void* pParent)
	{
		m_pPropGridData->m_gridDlg->Show(pParent);
	}

	void PropertyGridDlg::ShowModal()
	{
		m_pPropGridData->m_gridDlg->ShowModal();
	}

	void PropertyGridDlg::ShowModal(void* pParent)
	{
		m_pPropGridData->m_gridDlg->Show(pParent);
	}
	void PropertyGridDlg::Hide()
	{
		m_pPropGridData->m_gridDlg->Hide();
	}

	bool PropertyGridDlg::IsVisible()
	{
		return m_pPropGridData->m_gridDlg->IsVisible();
	}

	void PropertyGridDlg::SetTitle(const char *pTitle)
	{
		std::string titleStr(pTitle);
		std::wstring wideTitleStr(titleStr.begin(), titleStr.end());
		m_pPropGridData->m_gridDlg->SetTitle(wideTitleStr.c_str());
	}

	void PropertyGridDlg::RefreshProperties()
	{
		m_pPropGridData->m_gridDlg->RefreshProperties();
	}

	bool PropertyGridDlg::IsConnected()
	{
		return m_pPropGridData->m_gridDlg->IsConnected();
	}
#endif
}
