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

#include "FlyCap2CameraSelection_ILBridge.h"
#include "FlyCapture2.h"

namespace FlyCapture2_ILBridge
{
	ILBridge_CameraSelectionDialog::ILBridge_CameraSelectionDialog()
	{
		m_pCamSelDialog = gcnew FlyCapture2Managed::Gui::CameraSelectionDialog;
	}

	void ILBridge_CameraSelectionDialog::ShowModal(bool* pOk, FlyCapture2::PGRGuid* pGuid, unsigned int* pSize)
	{
		*pOk = m_pCamSelDialog->ShowModal();

		if (*pOk != true)
		{
			return;
		}

		array<FlyCapture2Managed::ManagedPGRGuid^>^ selectedGuids = m_pCamSelDialog->GetSelectedCameraGuids();

		// Translate GUID array from managed to native C++
		const unsigned int inputSize = *pSize;
		*pSize = selectedGuids->Length;

		for (int i=0; i < (int)inputSize; i++)
		{
			if (i >= selectedGuids->Length)
			{
				break;
			}

			pGuid[i].value[0] = selectedGuids[i]->value0;
			pGuid[i].value[1] = selectedGuids[i]->value1;
			pGuid[i].value[2] = selectedGuids[i]->value2;
			pGuid[i].value[3] = selectedGuids[i]->value3;
		}
	}

	void ILBridge_CameraSelectionDialog::SetTitle(const wchar_t* title)
	{
		m_pCamSelDialog->SetTitle(gcnew System::String(title));
	}
}
