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
// $Id: FlyCapture2Platform_C.h,v 1.5 2010-08-13 18:49:59 soowei Exp $
//=============================================================================

#ifndef PGR_FC2_FLYCAPTURE2PLATFORM_C_H
#define PGR_FC2_FLYCAPTURE2PLATFORM_C_H

//=============================================================================
// Platform-specific header file for FlyCapture2 C.
//
// All the platform-specific code that is required by individual compilers
// to produce the appropriate code for each platform.
//=============================================================================

#if defined(_WIN32) || defined(_WIN64)

// Windows 32-bit and 64-bit
#ifdef FLYCAPTURE2_C_EXPORTS
#define FLYCAPTURE2_C_API __declspec( dllexport )
#elif defined(FLYCAPTURE2_C_STATIC)
#define FLYCAPTURE2_C_API
#else
#define FLYCAPTURE2_C_API __declspec( dllimport )
#endif

#if _MSC_VER > 1000
#pragma once
#endif

// Provide a common naming scheme for fixed-width integer types
#ifdef _MSC_VER
#if _MSC_VER >= 1600
#include <stdint.h>
#else
typedef __int8				int8_t;
typedef __int16				int16_t;
typedef __int32				int32_t;
typedef __int64				int64_t;
typedef unsigned __int8		uint8_t;
typedef unsigned __int16	uint16_t;
typedef unsigned __int32	uint32_t;
typedef unsigned __int64	uint64_t;
#endif
#elif __GNUC__ >=3
#include <cstdint>
#endif


#elif defined(MAC_OSX)

// Mac OSX

#else

#define FLYCAPTURE2_C_API
#define FLYCAPTURE2_C_CALL_CONVEN
// Linux and all others

#endif

#endif // PGR_FC2_FLYCAPTURE2PLATFORM_C_H

