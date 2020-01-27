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
// $Id: HDRPage.h,v 1.10 2010-12-17 21:32:28 matt Exp $
//=============================================================================

#ifndef _HDRFLASHPAGE_H_
#define _HDRFLASHPAGE_H_

#include "BasePage.h"

namespace FlyCapture2
{
	struct HDRImage
	{
		Gtk::HScale* pHscaleGain;
		Gtk::Adjustment* pAdjustmentGain;

		Gtk::HScale* pHscaleShutter;
		Gtk::Adjustment* pAdjustmentShutter;
	};

	class HDRPage : public BasePage
	{
		public:
			HDRPage( CameraBase* pCamera, Glib::RefPtr<Gnome::Glade::Xml> refXml );
			~HDRPage();

			void UpdateWidgets();

			void OnEnableHDRToggled();
			void OnGainScroll( int image );
			void OnShutterScroll( int image );

		protected:
			void GetWidgets();
			void AttachSignals();

		private:
			static const unsigned int sk_bumblebeeHDRReg = 0x1400;
			static const unsigned int sk_ladybug2HDRReg = 0x13FC;
			static const unsigned int sk_hdrReg = 0x1800;

			static const int sk_timeout = 500;

			static const char* sk_checkbuttonEnableHDR;
			static const char* sk_hScaleHDR1Gain;
			static const char* sk_hScaleHDR1Shutter;
			static const char* sk_hScaleHDR2Gain;
			static const char* sk_hScaleHDR2Shutter;
			static const char* sk_hScaleHDR3Gain;
			static const char* sk_hScaleHDR3Shutter;
			static const char* sk_hScaleHDR4Gain;
			static const char* sk_hScaleHDR4Shutter;

			Gtk::CheckButton* m_pCheckbuttonEnableHDR;

			HDRImage m_hdrImageArray[4];

			unsigned int m_hdrRegOffset;
			unsigned int m_hdrRegIncrement;

			HDRPage();
			HDRPage( const HDRPage& );
			HDRPage& operator=( const HDRPage& );

			bool IsHDRSupported();
			bool IsHDREnabled();
			unsigned int GetHDRRegOffset();

			// Get / set gain from camera
			unsigned int GetGain( int image );
			void SetGain( int image, unsigned int gainValue );

			// Get / set shutter from camera
			unsigned int GetShutter( int image );
			void SetShutter( int image, unsigned int shutterValue );

			// Set the adjustments
			void SetGainRange( int image, unsigned int min, unsigned int max );
			void SetShutterRange( int image, unsigned int min, unsigned int max );

			unsigned int GetRegisterOffset( unsigned int regBase, int image );

			void EnableHDRWidgets();
			void DisableHDRWidgets();
			void UpdateHDRWidgets();

			virtual bool OnTimer();

	};
}

#endif // _HDRFLASHPAGE_H_
