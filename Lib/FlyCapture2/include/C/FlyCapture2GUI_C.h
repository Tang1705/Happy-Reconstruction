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
// $Id: FlyCapture2GUI_C.h,v 1.4 2010-04-13 21:31:12 hirokim Exp $
//=============================================================================

#ifndef PGR_FC2_FLYCAPTURE2GUI_C_H
#define PGR_FC2_FLYCAPTURE2GUI_C_H

//=============================================================================
// Global C header file for FlyCapture2.
//
// This file defines the C API for FlyCapture2 GUI
//=============================================================================

#include "FlyCapture2Defs_C.h"
#include "FlyCapture2Platform_C.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * Create a GUI context.
	 *
	 * Any GigE cameras that were connected prior to this call will lose CCP
	 * after the call. Consider creating a GUI context prior to connecting 
	 * any GigE cameras or calling connect on any outstanding GigE camera
	 * context.
	 *
	 * @param pContext Pointer to context to be created.
	 *
	 * @return An Error indicating the success or failure of the function.
	 */
	FLYCAPTURE2_C_API fc2Error
		fc2CreateGUIContext(
				fc2GuiContext* pContext );

	/**
	 * Destroy a GUI context.
	 *
	 * @param context Context to be destroyed.
	 *
	 * @return An Error indicating the success or failure of the function.
	 */
	FLYCAPTURE2_C_API fc2Error
		fc2DestroyGUIContext(
				fc2GuiContext context );

	/**
	 * Connect GUI context to a camera context.
	 *
	 * @param context GUI context to connect.
	 * @param cameraContext Camera context to connect.
	 *
	 * @return An Error indicating the success or failure of the function.
	 */
	FLYCAPTURE2_C_API void
		fc2GUIConnect(
				fc2GuiContext context,
				fc2Context cameraContext );

	/**
	 * Disconnect GUI context from camera.
	 *
	 * @param context GUI context to disconnect.
	 *
	 * @return An Error indicating the success or failure of the function.
	 */
	FLYCAPTURE2_C_API void
		fc2GUIDisconnect(
				fc2GuiContext context);

	/**
	 * Disconnect GUI context from camera.
	 *
	 * @param context GUI context to disconnect.
	 *
	 * @return An Error indicating the success or failure of the function.
	 *
	 * @deprecated This method is deprecated and will be removed in a future FlyCapture2 release. Please use fc2GUIDisconnect instead.
	 */
#ifdef _WIN32
#pragma deprecated(fc2Disonnect)
	FLYCAPTURE2_C_API void fc2Disonnect(fc2GuiContext context);
#else
	FLYCAPTURE2_C_API void fc2Disonnect(fc2GuiContext context) __attribute__ ((deprecated));
#endif

	/**
	 * Show the GUI.
	 *
	 * @param context Pointer to context to show.
	 *
	 * @return An Error indicating the success or failure of the function.
	 */
	FLYCAPTURE2_C_API void
		fc2Show(
				fc2GuiContext context);

	/**
	 * Hide the GUI.
	 *
	 * @param context Pointer to context to hide.
	 *
	 * @return An Error indicating the success or failure of the function.
	 */
	FLYCAPTURE2_C_API void
		fc2Hide(
				fc2GuiContext context);

	/**
	 * Check if the GUI is visible.
	 *
	 * @param context Pointer to context to show.
	 *
	 * @return Whether the GUI is visible.
	 */
	FLYCAPTURE2_C_API BOOL
		fc2IsVisible(
				fc2GuiContext context);

	/**
	 * Show the camera selection dialog.
	 *
	 * @param context Pointer to context to show.
	 * @param pOkSelected Whether Ok (true) or Cancel (false) was clicked.
	 * @param guidArray Array of PGRGuids containing the selected cameras.
	 * @param size Size of PGRGuid array.
	 */
	FLYCAPTURE2_C_API void
		fc2ShowModal(
				fc2GuiContext context,
				BOOL* pOkSelected,
				fc2PGRGuid* guidArray,
				unsigned int* size );

#ifdef __cplusplus
};
#endif

#endif // PGR_FC2_FLYCAPTURE2GUI_C_H

