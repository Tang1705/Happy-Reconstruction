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
// $Id: LadybugSettingsPage.h,v 1.13 2010-11-12 18:09:38 soowei Exp $
//=============================================================================

#ifndef _LADYBUGSETTINGSPAGE_H_
#define _LADYBUGSETTINGSPAGE_H_

#include "BasePage.h"

namespace FlyCapture2
{
	class LadybugSettingsPage : public BasePage
	{
		public:
			LadybugSettingsPage( CameraBase* pCamera, Glib::RefPtr<Gnome::Glade::Xml> refXml );
			~LadybugSettingsPage();

			void UpdateWidgets();

		protected:
			void GetWidgets();
			void AttachSignals();

		private:
			struct LadybugAutoExposure
			{
				Gtk::HScale* pHScale;
				Gtk::SpinButton* pSpinButton;
				Gtk::Adjustment* pAdjustment;

				Gtk::CheckButton* pOnOff;
				Gtk::CheckButton* pAuto;

				Gtk::CheckButton* pCCD0;
				Gtk::CheckButton* pCCD1;
				Gtk::CheckButton* pCCD2;
				Gtk::CheckButton* pCCD3;
				Gtk::CheckButton* pCCD4;
				Gtk::CheckButton* pCCD5;
			};

			struct LadybugShutter
			{
				Gtk::HScale* pHScale;
				Gtk::SpinButton* pSpinButton;
				Gtk::Adjustment* pAdjustment;

				Gtk::CheckButton* pOnOff;
				Gtk::CheckButton* pAuto;
			};

			struct LadybugGain
			{
				Gtk::HScale* pHScale;
				Gtk::SpinButton* pSpinButton;
				Gtk::Adjustment* pAdjustment;

				Gtk::CheckButton* pOnOff;
				Gtk::CheckButton* pAuto;
			};

			static const int sk_timeout = 300;

			// Register definitions
			// 0x80000001 (1%) -> 0x80000064 (100%)
			// Bit7 = 1 indicating auto jpeg is enabled
			static const unsigned int sk_CompressorJpegQualityReg = 0x1a20;

			// The least significant byte is the buffer usage for JPEG compression
			// 0x......01 (1%) -> 0x......FF (100%)
			static const unsigned int sk_Compressor_BufferControlReg = 0x1a24;

			// Register 1e80h updates similar functionality found in 1a20h.
			// For Ladybug2, valid since firmware 1.0.2.0 and later
			// For Ladtbug3, valid since firmware 1.2.2.1 and later
			static const unsigned int sk_JpegControlReg = 0x1e80;
			// Register 1e84h and 1E88h update similar functionality found in 1a24h.
			// For Ladybug2, valid since firmware 1.0.2.0 and later
			// For Ladtbug3, valid since firmware 1.2.2.1 and later
			static const unsigned int sk_JpegBufferUsageReg = 0x1e84;
			static const unsigned int sk_ImageSelectionReg =  0x1e88;

			// Independent Exposure Inquiry. Ladybug3 only.
			// The quadlet offset of the base address of the per sensor
			// independent exposure controls
			static const unsigned int sk_IndependentExposureInq =  0x1e94;

			// Base address of Ladybug2 Independent exposure control registers
			static const unsigned int sk_IndependentExposureRegBase_LD2 =  0x1800;

			// Independent exposure control register offsets
			static const unsigned int sk_Ind_Exp_Reg_Offset_Gain =  0x00;
			static const unsigned int sk_Ind_Exp_Reg_Offset_Shutter =  0x04;
			static const unsigned int sk_Ind_Exp_Reg_Offset_Exposure =  0x08;

			// Bit mask for auto bit
			static const unsigned int sk_Ind_Exp_Reg_AutoBitMask =  0x01000000;

			// Bit mask for On/Off bit
			static const unsigned int sk_Ind_Exp_Reg_OnOffBitMask =  0x02000000;

			// Ladybug3 only
			static const unsigned int sk_AE_Stats_MaskReg = 0x1e90;

			static const char* sk_checkbuttonLdJPEGQualityAuto;
			static const char* sk_hscaleLdJPEGQuality;
			static const char* sk_hscaleLdAutoBufferUsage;

			static const unsigned int sk_numCameras = 6;

			LadybugAutoExposure m_exposureWidgets[sk_numCameras];
			LadybugShutter m_shutterWidgets[sk_numCameras];
			LadybugGain m_gainWidgets[sk_numCameras];

			Gtk::CheckButton* m_pCheckButtonLdJPEGQualityAuto;
			Gtk::HScale* m_pHScaleLdJPEGQuality;
			Gtk::Adjustment* m_pAdjLdJPEGQuality;
			Gtk::HScale* m_pHScaleLdAutoBufferUsage;
			Gtk::Adjustment* m_pAdjLdAutoBufferUsage;

			Gtk::CheckButton* m_pSensorForStats[sk_numCameras];

			LadybugSettingsPage();
			LadybugSettingsPage( const LadybugSettingsPage& );
			LadybugSettingsPage& operator=( const LadybugSettingsPage& );

			void OnCheckJPEGQualityAuto();
			void OnHScaleJPEGQualityChanged();
			void OnHScaleAutoBufferUsageChanged();

			void OnExposureValueChanged(unsigned int cameraIdx);
			void OnExposureOnOffChecked(unsigned int cameraIdx);
			void OnExposureAutoChecked(unsigned int cameraIdx);
			void OnExposureCCDChecked(unsigned int cameraIdx, unsigned int CCD);

			void OnShutterValueChanged(unsigned int cameraIdx);
			void OnShutterOnOffChecked(unsigned int cameraIdx);
			void OnShutterAutoChecked(unsigned int cameraIdx);

			void OnGainValueChanged(unsigned int cameraIdx);
			void OnGainOnOffChecked(unsigned int cameraIdx);
			void OnGainAutoChecked(unsigned int cameraIdx);

			void OnSensorForStatsChecked(unsigned int cameraIdx);

			void SetAdjustedValueInReg(unsigned int cameraIdx, unsigned int valueToSet, unsigned int regOffset );
			void SetCheckedBitInReg(unsigned int cameraIdx, bool active, unsigned int regOffset, unsigned int bitMask );

			void EnableJpegSettingsWidgets( bool bEnable );
			void EnableAutoBufferUsageSettingsWidgets( bool bEnable );
			bool UpdateJpegSettingsValues();

			void EnableSensorForStatsWidgets( bool bEnable );

			void EnableAllAECWidgets( bool bEnable );
			void EnableGainWidgets( unsigned int camera, bool bEnable );
			void EnableShutterWidgets( unsigned int camera, bool bEnable );
			void EnableExposureWidgets( unsigned int camera, bool bEnable );

			virtual bool OnTimer();

			void UpdateAllAECSettings( );
			void UpdateGainSettings( );
			void UpdateShutterSettings( );
			void UpdateExposureSettings( );

			void UpdateSensorForStatsSettings( );

			void UpdateCheckButton( Gtk::CheckButton* pButton, bool bVal );

			unsigned int m_independentExposureRegBase;

			bool m_isLadybug;

			/**  Whether the independent exposure supported */
			bool m_independentExposureSupported;

			/**  Whether the independent exposure supported */
			bool m_independentExposureSensorMaskSupported;

			Glib::Mutex m_valueChangeMutex;

	};
}

#endif // _LADYBUGSETTINGSPAGE_H_
