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

#include "StdAfx.h"
#include "ReceivedFrameRateCounter.h"

	ReceivedFrameRateCounter::ReceivedFrameRateCounter(double dHistory)
:FrameRateCounter( dHistory )
{
	m_prevTimeFromTimeStamp = 0.0;
	::QueryPerformanceCounter( (LARGE_INTEGER*)&m_lastTime );
}

ReceivedFrameRateCounter::~ReceivedFrameRateCounter(void)
{
}

	void
ReceivedFrameRateCounter::NewFrame(FlyCapture2::TimeStamp *timeStamp)
{
	double currTime = TimeStamptoDouble(timeStamp);

	// Set frame rate to zero if embedded
	// timestamps is not available
	if(currTime == 0)
	{
		m_frameRate = 0.0;
		return;
	}

	double tempCurrTime = currTime;
	double timeDiff = 0.0;
	__int64 timeDiff64 = 0;

	// Initialize
	if( m_prevTimeFromTimeStamp == 0.0)
	{
		m_prevTimeFromTimeStamp = currTime;
		::QueryPerformanceCounter( (LARGE_INTEGER*)&m_lastTime );
		return;
	}

	// Check to see if there were any undetected wrap around
	::QueryPerformanceCounter( (LARGE_INTEGER*)&m_currTime );
	timeDiff64 = m_currTime - m_lastTime;
	if ( timeDiff64/static_cast<double>(m_frequency) >= 128 )
	{
		// 128+ seconds has elapsed since last capture.
		// This could happen if camera was in trigger mode.
		tempCurrTime = currTime + timeDiff64/static_cast<double>(m_frequency);
	}

	timeDiff = tempCurrTime - m_prevTimeFromTimeStamp;

	if(timeDiff == 0)
	{
		//Same Image was received again
		return;
	}

	// Check to see if a wrap around had just happened
	if(timeDiff < 0)
	{
		// Adding 127/7999/3071 to currTime in order to computer time difference properly
		tempCurrTime = tempCurrTime + 127.99999995930989583333333333333;
		timeDiff = tempCurrTime - m_prevTimeFromTimeStamp;
	}

	m_frameRate = m_dHistory*m_frameRate + (1/(timeDiff))*(1-m_dHistory);

	m_prevTimeFromTimeStamp = currTime;
	::QueryPerformanceCounter( (LARGE_INTEGER*)&m_lastTime );
}

	double
ReceivedFrameRateCounter::TimeStamptoDouble(FlyCapture2::TimeStamp *timeStamp)
{
	return (double)timeStamp->cycleSeconds + (((double)timeStamp->cycleCount+((double)timeStamp->cycleOffset/3072.0))/8000.0);
}
