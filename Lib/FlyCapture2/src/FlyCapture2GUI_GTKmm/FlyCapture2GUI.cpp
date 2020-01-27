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
//=============================================================================
// $Id: FlyCapture2GUI.cpp,v 1.11 2009/03/04 01:02:02 soowei Exp $
//=============================================================================

#include "Precompiled.h"
#include "FlyCapture2GUI.h"

#include "CamSelection.h"
#include "CamControl.h"

namespace FlyCapture2
{
	struct CameraControlDlg::CamCtlData
	{
		CamControl m_camControl;
	};

	CameraControlDlg::CameraControlDlg()
	{
		m_pCamCtlData = new CamCtlData();

		bool retVal;
		retVal = m_pCamCtlData->m_camControl.Initialize();
		if ( retVal != true )
		{
			// Error during initialization
		}
	}

	CameraControlDlg::~CameraControlDlg()
	{
		delete m_pCamCtlData;
	}

	void CameraControlDlg::Connect( CameraBase* pCamera )
	{
		m_pCamCtlData->m_camControl.Connect( pCamera );
	}

	void CameraControlDlg::Disconnect()
	{
		m_pCamCtlData->m_camControl.Disconnect();
	}

	void CameraControlDlg::Show()
	{
		m_pCamCtlData->m_camControl.Show();
	}

	void CameraControlDlg::ShowModal()
	{
		m_pCamCtlData->m_camControl.Show(TRUE);
	}

	void CameraControlDlg::Hide()
	{
		m_pCamCtlData->m_camControl.Hide();
	}

	bool CameraControlDlg::IsVisible()
	{
		return m_pCamCtlData->m_camControl.IsVisible();
	}

	void CameraControlDlg::SetTitle( const char *pTitle)
	{
		m_pCamCtlData->m_camControl.SetTitle( pTitle);
	}

	struct CameraSelectionDlg::CamSelectionData
	{
		CamSelection m_camSelection;
	};

	CameraSelectionDlg::CameraSelectionDlg()
	{
		m_pCamSelectionData = new CamSelectionData();
	}

	CameraSelectionDlg::~CameraSelectionDlg()
	{
		delete m_pCamSelectionData;
	}

	void CameraSelectionDlg::ShowModal( bool* pOkSelected, PGRGuid* guidArray, unsigned int* size)
	{
		bool retVal;
		retVal = m_pCamSelectionData->m_camSelection.Initialize();
		if ( retVal != true )
		{
			// Error during initialization
			*pOkSelected = false;
			*size = 0;

			return;
		}


		m_pCamSelectionData->m_camSelection.ShowModal( pOkSelected, guidArray, size );
	}

	void CameraSelectionDlg::SetTitle( const char *pTitle)
	{
		if ( pTitle != NULL)
		{
			m_pCamSelectionData->m_camSelection.SetTitle( pTitle);
		}
	}
}
