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
// $Id: Precompiled.h,v 1.8 2009-07-20 19:03:20 soowei Exp $
//=============================================================================

#ifndef PRECOMPILED_H
#define PRECOMPILED_H

#if defined(_WIN32) || defined(_WIN64)
#pragma warning( push, 0 )
#endif

#include <gtkmm.h>
#include <giomm.h>
#include <libglademm/xml.h>
#include "FlyCapture2.h"
#include "PGRIcon.h"

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif
