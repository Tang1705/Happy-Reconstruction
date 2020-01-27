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
// $Id: FrameRateCounter.h,v 1.5 2009-01-14 22:58:43 release Exp $
//=============================================================================

#ifndef __FRAMERATE_H__
#define __FRAMERATE_H__

class FrameRateCounter
{
	public:
		FrameRateCounter( double dHistory = 0.5 );
		virtual ~FrameRateCounter(void){};

		double GetFrameRate();
		void SetFrameRate( double frameRate );
		void NewFrame();

	protected:
		double m_frameRate;
		double m_dHistory;
		__int64  m_frequency;
		__int64  m_lastTime;
		__int64  m_prevTime;
};


#endif // #ifndef __FRAMERATE_H__
