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
// $Id:
//=============================================================================

#ifndef MULTISYNCLIBRARY_C_H
#define MULTISYNCLIBRARY_C_H

//=============================================================================
// Global C header file for MultiSync
//
// This file defines the C API for MultiSync Library
//=============================================================================

#include "MultiSyncLibraryPlatform_C.h"
#include "MultiSyncLibraryDefs_C.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * Create a Sync context for MultiSync Library.
	 * This call must be made before any other calls that use a context
	 * will succeed.
	 *
	 * @param pContext A pointer to the syncContext to be created.
	 *
	 * @return A syncError indicating the success or failure of the function.
	 */
	MULTISYNCLIBRARY_C_API syncError
		syncCreateContext(
				syncContext* pContext );

	/**
	 * Destory the sync context. This must be called when the user is finished
	 * with the context in order to prevent memory leaks.
	 *
	 * @param context The syncContext to be destoryed.
	 *
	 * @return A syncError indicating the success or failure of the function.
	 */
	MULTISYNCLIBRARY_C_API syncError
		syncDestroyContext(
				syncContext context );

	/**
	 * Start the sync progress
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return A syncError indicating the success or failure of the function.
	 */
	MULTISYNCLIBRARY_C_API syncError
		syncStart(
				syncContext context );

	/**
	 * Stop the sync progress
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return A syncError indicating the success or failure of the function.
	 */
	MULTISYNCLIBRARY_C_API syncError
		syncStop(
				syncContext context );


	/**
	 * Scan newly connected or removed timing bus (for corss-PC syncing only)
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return A syncError indicating the success or failure of the function.
	 */
	MULTISYNCLIBRARY_C_API syncError
		syncRescanMasterTimingBus(
				syncContext context );

	/**
	 * Start the sync progress
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return A syncMessage indicating the sync status.
	 */
	MULTISYNCLIBRARY_C_API syncMessage
		syncGetStatus(
				syncContext context );

	/**
	 * Time since sync started
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return Time sinced synced.
	 */
	MULTISYNCLIBRARY_C_API double
		syncGetTimeSinceSynced(
				syncContext context );

	/**
	 * Whether syncing across PCs
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return True if its syncing across PC
	 */
	MULTISYNCLIBRARY_C_API BOOL
		syncIsTimingBusConnected(
				syncContext context );

	/**
	 * Enable across pc synchronization support
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return True if operation was successful
	 */
	MULTISYNCLIBRARY_C_API BOOL
		syncEnableCrossPCSynchronization(
				syncContext context );

	/**
	 * Disable across pc synchronization support
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return True if operation was successful
	 */
	MULTISYNCLIBRARY_C_API BOOL
		syncDisableCrossPCSynchronization(
				syncContext context );

	/**
	 * Query cross pc synchronizaion support status
	 *
	 * @param context The syncContext to be used.
	 *
	 * @return True if cross pc synchronization was supported
	 */
	MULTISYNCLIBRARY_C_API BOOL
		syncQueryCrossPCSynchronizationSetting(
				syncContext context );
#ifdef __cplusplus
};
#endif

#endif
