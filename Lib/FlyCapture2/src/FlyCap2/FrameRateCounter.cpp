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
// $Id: FrameRateCounter.cpp,v 1.7 2009-03-25 01:27:14 soowei Exp $
//=============================================================================

#include "stdafx.h"
#include "FrameRateCounter.h"

FrameRateCounter::FrameRateCounter( double dHistory )
{
	m_frameRate = 0.0;
	m_dHistory = dHistory;

	::QueryPerformanceFrequency( (LARGE_INTEGER*)&m_frequency );
	::QueryPerformanceCounter( (LARGE_INTEGER*)&m_prevTime );
}


double FrameRateCounter::GetFrameRate()
{
	return m_frameRate;
}


void FrameRateCounter::SetFrameRate( double frameRate )
{
	m_frameRate = frameRate;
}

void FrameRateCounter::NewFrame()
{
	//DWORD currTime = timeGetTime();
	__int64 currTime;
	::QueryPerformanceCounter( (LARGE_INTEGER*)&currTime );

	__int64 timeDiff64 = currTime - m_prevTime;
	double  timeDiff = timeDiff64/static_cast<double>(m_frequency);

	if ( timeDiff != 0 )
	{
		m_frameRate = (1/timeDiff)*(1-m_dHistory) + m_dHistory*m_frameRate;
		m_prevTime = currTime;
	}
}
