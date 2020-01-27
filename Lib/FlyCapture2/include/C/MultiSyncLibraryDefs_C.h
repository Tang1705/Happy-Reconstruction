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

#ifndef MULTISYNCLIBRARYDEFS_C_H
#define MULTISYNCLIBRARYDEFS_C_H

#include <stdlib.h>

//=============================================================================
// C definitions header file for MultiSync.
//
// This file defines the C enumerations, typedefs and structures for MultiSync
//
//=============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

	//=============================================================================
	// Typedefs
	//=============================================================================

	typedef int BOOL;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef FULL_32BIT_VALUE
#define FULL_32BIT_VALUE 0x7FFFFFFF
#endif

#define MAX_STRING_LENGTH   512

	/**
	 * A context to the MultiSync C library. It must be created before
	 * performing any calls to the library.
	 */
	typedef void* syncContext;


	//=============================================================================
	// Enumerations
	//=============================================================================

	typedef enum _syncError
	{
		SYNC_ERROR_OK = 0,
		SYNC_ERROR_FAILED,
		SYNC_ERROR_ALREADY_STARTED,
		SYNC_ERROR_ALREADY_STOPPED,
		SYNC_ERROR_CONTEXT_NOT_INITIALIZED,
		SYNC_ERROR_UNKNOWN_ERROR,
	} syncError;

	typedef enum _syncMessage
	{
		SYNC_MESSAGE_OK = 0,
		SYNC_MESSAGE_FAILED,
		SYNC_MESSAGE_STARTED,
		SYNC_MESSAGE_STOPPED,
		SYNC_MESSAGE_SYNCING,
		SYNC_MESSAGE_NOMASTER,
		SYNC_MESSAGE_THREAD_ERROR,
		SYNC_MESSAGE_DEVICE_ERROR,
		SYNC_MESSAGE_NOT_ENOUGH_DEVICES,
		SYNC_MESSAGE_BUS_RESET,
		SYNC_MESSAGE_NOT_INITIALIZED,
		SYNC_MESSAGE_UNKNOWN_ERROR,
	} syncMessage;

#ifdef __cplusplus
};
#endif

#endif
