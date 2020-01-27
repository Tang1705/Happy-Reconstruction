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
// $Id: ReceivedFrameRateCounter.h,v 1.5 2009-01-14 22:58:43 release Exp $
//=============================================================================

#ifndef __RECEIVED_FRAMERATE_H__
#define __RECEIVED_FRAMERATE_H__

#include <deque>
#include "FrameRateCounter.h"

class ReceivedFrameRateCounter : public FrameRateCounter
{
	public:
		ReceivedFrameRateCounter(double dHistory = 0.5);
		virtual ~ReceivedFrameRateCounter(void);
		void NewFrame(FlyCapture2::TimeStamp* timeStamp);

	protected:

		double m_prevTimeFromTimeStamp;
		__int64  m_currTime;
		double TimeStamptoDouble(FlyCapture2::TimeStamp* timeStamp);
};

#endif // #ifndef RECEIVED_FRAMERATE_H_
