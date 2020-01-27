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

#ifndef MULTISYNCLIBRARYDEFS_H
#define MULTISYNCLIBRARYDEFS_H

#include <memory.h>

//=============================================================================
// Definitions file for MultiSync Library.
//
// Holds structures, enumerations and other global definitions that are used
// across the entire MultiSync API.
//=============================================================================

namespace MultiSyncLibrary
{
	typedef enum {
		PGRSyncError_OK = 0,
		PGRSyncError_FAILED,
		PGRSyncError_ALREADY_STARTED,
		PGRSyncError_ALREADY_STOPPED,
		PGRSyncError_CAMERA_NOT_FOUND,
		PGRSyncError_UNKNOWN_ERROR,
	} PGRSyncError;

	typedef enum {
		PGRSyncMessage_OK = 0,
		PGRSyncMessage_STARTED,
		PGRSyncMessage_STOPPED,
		PGRSyncMessage_SYNCING,
		PGRSyncMessage_NOMASTER,
		PGRSyncMessage_THREAD_ERROR,
		PGRSyncMessage_DEVICE_ERROR,
		PGRSyncMessage_NOT_ENOUGH_DEVICES,
		PGRSyncMessage_BUS_RESET,
		PGRSyncMessage_NOT_INITIALIZED,
		PGRSyncMessage_UNKNOWN_ERROR,
	} PGRSyncMessage;

	class SyncManager
	{
		public:
			MULTISYNCLIBRARY_API SyncManager();
			MULTISYNCLIBRARY_API ~SyncManager();
			MULTISYNCLIBRARY_API PGRSyncError Start();
			MULTISYNCLIBRARY_API PGRSyncError Stop();
			MULTISYNCLIBRARY_API PGRSyncError RescanMasterTimingBus();
			MULTISYNCLIBRARY_API PGRSyncMessage GetSyncStatus();
			MULTISYNCLIBRARY_API double GetTimeSinceSynced();
			MULTISYNCLIBRARY_API bool IsTimingBusConnected();
			MULTISYNCLIBRARY_API bool EnableCrossPCSynchronization();
			MULTISYNCLIBRARY_API bool DisableCrossPCSynchronization();
			MULTISYNCLIBRARY_API bool QueryCrossPCSynchronizationSetting();

		private:
			struct PGRSyncData; // Forward declaration
			PGRSyncData* m_pPGRSyncData;
	};
}

#endif //MULTISYNCLIBRARYDEFS_H
