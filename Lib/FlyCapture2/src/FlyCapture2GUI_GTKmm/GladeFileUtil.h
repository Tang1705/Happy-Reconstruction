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
// $Id: GladeFileUtil.h,v 1.5 2010-10-21 22:40:53 matt Exp $
//=============================================================================

#ifndef GLADEFILEUTIL_H_INCLUDED
#define GLADEFILEUTIL_H_INCLUDED

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

namespace FlyCapture2
{
	class GladeFileUtil
	{
		public:
			static Glib::ustring GetGladeFilePath( void)
			{
				static const char* sk_GUI_GTK_Glade = "FlyCapture2GUI_GTK.glade";

#if _MSC_VER == 1600
				static const char* sk_modules[] = { "FlyCapture2GUI_v100.dll",
					"FlyCapture2GUId_v100.dll"};
#elif _MSC_VER == 1500
				static const char* sk_modules[] = { "FlyCapture2GUI_v90.dll",
					"FlyCapture2GUId_v90.dll"};
#else
				static const char* sk_modules[] = { "FlyCapture2GUI.dll",
					"FlyCapture2GUId.dll"};
#endif

#if defined(_WIN32) || defined(_WIN64)
				//
				// For Windows, this function returns the full path to the glade file.
				// The relative path won't work if the glade file is not in the
				// current directory.
				//
				char fileName[ MAX_PATH];
				int numModules = sizeof ( sk_modules) / sizeof ( char*);

				// Try to search all the known modules that may be used.
				HMODULE module;
				int i = 0;
				do{
					module = ::GetModuleHandleA( sk_modules[ i++ ]);
				}while ( module == NULL && i < numModules);

				if ( module == NULL)
				{
					// Maybe using the static library. Just return the file name part.
					return sk_GUI_GTK_Glade;
				}

				// Found the module. Find the path to it.
				DWORD result = ::GetModuleFileNameA( module, fileName, sizeof(fileName));
				if ( result == 0)
					return sk_GUI_GTK_Glade;

				// Create a full path to the glade file.
				char *backslashPos = strrchr( fileName, '\\');
				if ( backslashPos == NULL)
					return sk_GUI_GTK_Glade;

				*(backslashPos+1) = 0;
				strcat( fileName, sk_GUI_GTK_Glade);
				return fileName;
#else
				//
				// For non-Windows, this just returns the relative path to the file.
				//
				return sk_GUI_GTK_Glade;
#endif

			};

	};
}
#endif // GLADEFILEUTIL_H_INCLUDED
