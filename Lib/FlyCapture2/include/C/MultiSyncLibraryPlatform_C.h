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

#ifndef MULTISYNCLIBRARYPLATFORM_C_H
#define MULTISYNCLIBRARYPLATFORM_C_H

//=============================================================================
// Platform-specific header file for MultiSync C.
//
// All the platform-specific code that is required by individual compilers
// to produce the appropriate code for each platform.
//=============================================================================

#if defined(_WIN32) || defined(_WIN64)

// Windows 32-bit and 64-bit
#ifdef MULTISYNCLIBRARY_C_EXPORTS
#define MULTISYNCLIBRARY_C_API __declspec( dllexport )
#else
#define MULTISYNCLIBRARY_C_API __declspec( dllimport )
#endif

#if _MSC_VER > 1000
#pragma once
#endif

#elif defined(MAC_OSX)

// Mac OSX

#else

#define MULTISYNCLIBRARY_C_API
#define MULTISYNCLIBRARY_C_CALL_CONVEN
// Linux and all others

#endif

#endif

