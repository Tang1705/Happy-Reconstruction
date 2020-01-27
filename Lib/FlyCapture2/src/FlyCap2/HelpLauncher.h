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

#if defined(_WIN32) || defined(_WIN64)
#include "FlyCapture2Defs.h"
#include <string>
#if defined( _WIN64 ) && (_MSC_VER >= 1400)
#define REGISTRY_HIVE   KEY_WOW64_64KEY
#elif defined( _WIN32 ) && (_MSC_VER >= 1400)
#define REGISTRY_HIVE   KEY_WOW64_32KEY
#else
#define REGISTRY_HIVE   0
#endif

#else

// All other platforms

#endif

std::string GetHelpFilePath()
{
	// Default to the assumption that the app is being run out of the default
	// directory structure
	const char* defaultHelpPath = "..\\doc\\FlyCapture2SDKHelp.chm";

	char helpPath[FlyCapture2::sk_maxStringLength];
	memset( helpPath, 0x0, FlyCapture2::sk_maxStringLength );

	HKEY hkey = NULL;
	LONG retVal = RegOpenKeyEx(
			HKEY_LOCAL_MACHINE,
			"Software\\Point Grey Research, Inc.\\PGRFlyCapture\\",
			0,
			KEY_QUERY_VALUE | REGISTRY_HIVE,
			&hkey );
	if( retVal != ERROR_SUCCESS || hkey == NULL )
	{
		sprintf( helpPath, defaultHelpPath );
	}
	else
	{
		char installDir[FlyCapture2::sk_maxStringLength];
		memset( installDir, 0x0, FlyCapture2::sk_maxStringLength );

		DWORD dwBufSize = FlyCapture2::sk_maxStringLength;
		retVal = ::RegQueryValueEx(
				hkey,
				"InstallDir",
				0,
				NULL,
				(LPBYTE)installDir,
				&dwBufSize );
		if ( retVal != ERROR_SUCCESS )
		{
			sprintf( helpPath, defaultHelpPath );
		}
		else
		{
			retVal = ::RegCloseKey( hkey );
			if ( retVal != ERROR_SUCCESS )
			{
				// Error
			}

			sprintf( helpPath, "%sdoc\\FlyCapture2SDKHelp.chm", installDir );
		}
	}

	std::string helpFilePath( helpPath );
	return helpFilePath;
}
