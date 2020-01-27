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

#include "FlyCap2CameraControl_ILBridge.h"
#include "FlyCapture2.h"

namespace FlyCapture2_ILBridge
{
	ILBridge_CameraControlDialog::ILBridge_CameraControlDialog()
	{
		m_pCamCtrlDialog = gcnew FlyCapture2Managed::Gui::CameraControlDialog;
	}

	void ILBridge_CameraControlDialog::Connect(FlyCapture2::CameraBase* pCamera)
	{
		FlyCapture2Managed::ManagedCameraBase^ camera;
		FlyCapture2::GigECamera* pGigECamera = dynamic_cast<FlyCapture2::GigECamera*>(pCamera);
		if (pGigECamera == NULL)
		{
			FlyCapture2::Camera* pOtherCamera = dynamic_cast<FlyCapture2::Camera*>(pCamera);
			camera = gcnew FlyCapture2Managed::ManagedCamera();
			camera->SetCamera((System::IntPtr)pOtherCamera);
		}
		else
		{
			FlyCapture2::GigECamera* pOtherCamera = dynamic_cast<FlyCapture2::GigECamera*>(pCamera);
			camera = gcnew FlyCapture2Managed::ManagedGigECamera();
			camera->SetCamera((System::IntPtr)pOtherCamera);
		}
		m_pCamCtrlDialog->Connect(camera);
	}

	void ILBridge_CameraControlDialog::Disconnect()
	{
		m_pCamCtrlDialog->Disconnect();
	}

	void ILBridge_CameraControlDialog::Hide()
	{
		m_pCamCtrlDialog->Hide();
	}

	void ILBridge_CameraControlDialog::Show()
	{
		m_pCamCtrlDialog->Show();
	}

	void ILBridge_CameraControlDialog::Show(void* pParent)
	{
		m_pCamCtrlDialog->Show((int)pParent);
	}

	void ILBridge_CameraControlDialog::ShowModal()
	{
		m_pCamCtrlDialog->ShowModal();
	}

	void ILBridge_CameraControlDialog::ShowModal(void* pParent)
	{
		m_pCamCtrlDialog->ShowModal((int)pParent);
	}

	bool ILBridge_CameraControlDialog::IsVisible()
	{
		System::Boolean __ReturnVal = m_pCamCtrlDialog->IsVisible();
		return __ReturnVal;
	}

	void ILBridge_CameraControlDialog::SetTitle(const wchar_t* title)
	{
		m_pCamCtrlDialog->SetTitle(gcnew System::String(title));
	}
}
