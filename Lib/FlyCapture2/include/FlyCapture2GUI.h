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

#ifndef PGR_FC2_FLYCAPTURE2GUI_H
#define PGR_FC2_FLYCAPTURE2GUI_H

#include "FlyCapture2Platform.h"
#include "FlyCapture2Defs.h"

namespace FlyCapture2
{
	// Forward declaration
	class CameraBase;

	/**
	 * The CameraControlDlg object represents a dialog that provides
	 * a graphical interface to a specified camera.
	 */
	class FLYCAPTURE2_API CameraControlDlg
	{
		public:
			/**
			 * Default constructor.
			 */
			CameraControlDlg();

			/**
			 * Default destructor.
			 */
			~CameraControlDlg();

			/**
			 * Connect dialog to a camera.
			 *
			 * @param pCamera Camera object to connect the dialog to.
			 */
			void Connect(CameraBase* pCamera);

			/**
			 * Disconnect a connected camera from the dialog.
			 */
			void Disconnect();

			/**
			 * Show the dialog.
			 */
			void Show();

			/**
			 * Show the dialog.
			 */
			void Show(void* pParent);

			/**
			 * Show the modal dialog.
			 */
			void ShowModal();

			/**
			 * Show the modal dialog.
			 */
			void ShowModal(void* pParent);

			/**
			 * Hide the dialog
			 */
			void Hide();

			/**
			 * Get the visibility of the dialog.
			 *
			 * @return Whether the dialog is visible.
			 */
			bool IsVisible();

			/**
			 * Change the title of the window. This has to be called after
			 * calling Connect().
			 *
			 * @param title Null-terminated string representing the title.
			 */
			void SetTitle(const char* title);

		private:
			struct CamCtlData; // Forward declaration

			CamCtlData* m_pCamCtlData;

			CameraControlDlg( const CameraControlDlg& );
			CameraControlDlg& operator=( const CameraControlDlg& );
	};

	/**
	 * The CameraSelectionDlg object represents a dialog that provides
	 * a graphical interface that lists the number of cameras available to
	 * the library.
	 *
	 * Any GigE cameras that were connected prior to creating a 
	 * CameraSelectionDlg will lose CCP after the creation. Consider 
	 * creating a CameraSelectionDlg prior to connecting any GigE cameras
	 * or calling connect on any outstanding GigE camera.
	 *
	 */
	class FLYCAPTURE2_API CameraSelectionDlg
	{
		public:
			/**
			 * Default constructor.
			 */
			CameraSelectionDlg();

			/**
			 * Default destructor.
			 */
			~CameraSelectionDlg();

			/**
			 * Show the CameraSelectionDlg.
			 *
			 * @param pOk Whether Ok (true) or Cancel (false) was clicked.
			 * @param pGuid Array of PGRGuids containing the selected cameras.
			 * @param pSize Size of PGRGuid array.
			 */
			void ShowModal(bool* pOk, PGRGuid* pGuid, unsigned int* pSize);

			/**
			 * Set the window title.
			 *
			 * @param title Null-terminated string representing the title.
			 */
			void SetTitle(const char* title);

		private:
			struct CamSelectionData; // Forward declaration

			CamSelectionData* m_pCamSelectionData;

			CameraSelectionDlg( const CameraSelectionDlg& );
			CameraSelectionDlg& operator=( const CameraSelectionDlg& );
	};

#ifdef GENICAM
	/**
	 * The PropertyGridDlg object represents a dialog that provides
	 * a graphical interface to a GeniCam nodemap.
	 */
	class FLYCAPTURE2_API PropertyGridDlg
	{
		public:
			/**
			 * Default constructor.
			 */
			PropertyGridDlg();

			/**
			 * Default destructor.
			 */
			~PropertyGridDlg();

			/**
			 * Connect dialog to a camera.
			 *
			 * @param pCamera Camera object to connect the dialog to.
			 */
			void Connect(CameraBase* pCamera);
			void Connect(CameraBase* pCamera, const char* xmlPath);

			/**
			 * Disconnect a connected camera from the dialog.
			 */
			void Disconnect();

			/**
			 * Show the dialog.
			 */
			void Show();

			/**
			 * Show the dialog.
			 */
			void Show(void* pParent);

			/**
			 * Show the modal dialog.
			 */
			void ShowModal();

			/**
			 * Show the modal dialog.
			 */
			void ShowModal(void* pParent);

			/**
			 * Hide the dialog
			 */
			void Hide();

			/**
			 * Get the visibility of the dialog.
			 *
			 * @return Whether the dialog is visible.
			 */
			bool IsVisible();

			/**
			 * Change the title of the window. This has to be called after
			 * calling Connect().
			 *
			 * @param title Null-terminated string representing the title.
			 */
			void SetTitle(const char* title);

			void RefreshProperties();
			bool IsConnected();
		private:
			struct PropGridData; // Forward declaration

			PropGridData* m_pPropGridData;

			PropertyGridDlg( const PropertyGridDlg& );
			PropertyGridDlg& operator=( const PropertyGridDlg& );
	};
#endif
}

#endif // PGR_FC2_FLYCAPTURE2GUI_H
