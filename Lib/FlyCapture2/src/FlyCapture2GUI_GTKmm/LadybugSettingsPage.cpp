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
// $Id: LadybugSettingsPage.cpp,v 1.20 2011-02-08 18:23:17 hirokim Exp $
//=============================================================================

#include "Precompiled.h"
#include "LadybugSettingsPage.h"

#if defined(_WIN32) || defined(_WIN64)
#include "windows.h"
#endif

namespace FlyCapture2
{
	const char* LadybugSettingsPage::sk_checkbuttonLdJPEGQualityAuto = "checkbuttonLdJPEGQualityAuto";
	const char* LadybugSettingsPage::sk_hscaleLdJPEGQuality = "hscaleLdJPEGQuality";
	const char* LadybugSettingsPage::sk_hscaleLdAutoBufferUsage = "hscaleLdAutoBufferUsage";

	LadybugSettingsPage::LadybugSettingsPage()
	{
		m_isLadybug = false;
	}

	LadybugSettingsPage::LadybugSettingsPage( CameraBase* pCamera, Glib::RefPtr<Gnome::Glade::Xml> refXml ) : BasePage( pCamera, refXml )
	{
		m_isLadybug = false;
	}

	LadybugSettingsPage::~LadybugSettingsPage()
	{
		if (m_pAdjLdJPEGQuality != NULL)
		{
			delete m_pAdjLdJPEGQuality;
			m_pAdjLdJPEGQuality = NULL;
		}

		if (m_pAdjLdAutoBufferUsage != NULL)
		{
			delete m_pAdjLdAutoBufferUsage;
			m_pAdjLdAutoBufferUsage = NULL;
		}

		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			delete m_exposureWidgets[i].pAdjustment;
			m_exposureWidgets[i].pAdjustment = NULL;

			delete m_shutterWidgets[i].pAdjustment;
			m_shutterWidgets[i].pAdjustment = NULL;

			delete m_gainWidgets[i].pAdjustment;
			m_gainWidgets[i].pAdjustment = NULL;
		}
	}

	void LadybugSettingsPage::UpdateWidgets()
	{
		unsigned int uiRegVal = 0;
		CameraInfo camInfo;

		if ( m_pCamera != NULL && IsConnected() == true )
		{
			m_pCamera->GetCameraInfo( &camInfo );
			m_isLadybug = IsLadybug();
		}

		if ( !m_isLadybug )
		{
			EnableJpegSettingsWidgets( false );
			EnableAutoBufferUsageSettingsWidgets( false );
			EnableAllAECWidgets( false );
			EnableSensorForStatsWidgets( false );
			return;
		}

		Error error = m_pCamera->ReadRegister(sk_JpegBufferUsageReg, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading JPEG control register", error );
		}

		if ( !(uiRegVal & 0x80000000) )
		{
			// Auto buffer usage feature is not supported
			EnableAutoBufferUsageSettingsWidgets( false );
		}

		bool bLadybug3Camera = false;
		bLadybug3Camera = IsLadybug3();
		// Deal with default value 0
		if ( (uiRegVal & 0x0000007F) == 0 )
		{
			if ( bLadybug3Camera )
			{
				// The default is 90% in LD3 Firmware if the value is 0
				m_pAdjLdAutoBufferUsage->set_value( 90 );
			}
			else
			{
				// The default is 80% in Firmware if the value is 0
				m_pAdjLdAutoBufferUsage->set_value( 80 );
			}
		}

		error = m_pCamera->ReadRegister(sk_JpegControlReg, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading JPEG control register", error );
		}

		if ( !(uiRegVal & 0x80000000) )
		{
			// JPEG control feature is not supported
			EnableJpegSettingsWidgets( false );
			return;
		}


		if ( uiRegVal & 0x01000000 )
		{
			m_pCheckButtonLdJPEGQualityAuto->set_active(true);
		}
		else
		{
			m_pCheckButtonLdJPEGQualityAuto->set_active(false);
		}

		if ( (uiRegVal & 0x000000FF) == 0 )
		{
			// The default is 60% in Firmware if the value is 0
			m_pAdjLdJPEGQuality->set_value( 60 );
		}

		// Check if Independent Exposure is supported
		m_independentExposureSupported = false;
		if ( bLadybug3Camera )
		{
			error = m_pCamera->ReadRegister(sk_IndependentExposureInq, &uiRegVal);
			if (error != PGRERROR_OK)
			{
				ShowErrorMessageDialog( "Error reading independent exposure  inquiry register", error );
			}
			// Get the offset
			m_independentExposureRegBase = (uiRegVal * 4) & 0xFFFF;
			// Supported if offset is not 0
			m_independentExposureSupported = m_independentExposureRegBase != 0;
			m_independentExposureSensorMaskSupported = false;
		}
		else
		{
			if ( IsLadybug2() )
			{
				m_independentExposureSupported = true;
				m_independentExposureSensorMaskSupported = true;
				m_independentExposureRegBase =  sk_IndependentExposureRegBase_LD2;
			}
		}

		UpdateExposureSettings();
		UpdateShutterSettings();
		UpdateGainSettings();

		EnableAllAECWidgets( m_independentExposureSupported );

		// Set sensor-for-statistics control
		bool bSensorForStatsSupported = false;
		if ( bLadybug3Camera )
		{
			error = m_pCamera->ReadRegister( sk_AE_Stats_MaskReg, &uiRegVal);
			if (error != PGRERROR_OK)
			{
				ShowErrorMessageDialog( "Error reading auto exposure statistics register", error );
			}
			bSensorForStatsSupported = ( uiRegVal & 0x80000000 ) > 0;
		}

		EnableSensorForStatsWidgets( bSensorForStatsSupported );
	}

	void LadybugSettingsPage::GetWidgets()
	{
		Error error;

		m_refXml->get_widget( sk_checkbuttonLdJPEGQualityAuto, m_pCheckButtonLdJPEGQualityAuto );
		m_refXml->get_widget( sk_hscaleLdJPEGQuality, m_pHScaleLdJPEGQuality );
		m_refXml->get_widget( sk_hscaleLdAutoBufferUsage, m_pHScaleLdAutoBufferUsage );

		m_pAdjLdJPEGQuality = new Gtk::Adjustment(0.0, 1.0, 100.0);
		m_pAdjLdAutoBufferUsage = new Gtk::Adjustment(0.0, 1.0, 100.0);

		m_pHScaleLdJPEGQuality->set_adjustment(*m_pAdjLdJPEGQuality);
		m_pHScaleLdAutoBufferUsage->set_adjustment(*m_pAdjLdAutoBufferUsage);

		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			char widgetName[64];

			m_exposureWidgets[i].pAdjustment = new Gtk::Adjustment(0.0, 1.0, 100.0);

			sprintf(widgetName, "hscaleLdExposureCam%u", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pHScale);
			m_exposureWidgets[i].pHScale->set_adjustment(*m_exposureWidgets[i].pAdjustment);

			sprintf(widgetName, "spinbuttonLdExposureCam%u", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pSpinButton);
			m_exposureWidgets[i].pSpinButton->set_adjustment(*m_exposureWidgets[i].pAdjustment);

			sprintf(widgetName, "checkbuttonLdExposureOnOffCam%u", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pOnOff);

			sprintf(widgetName, "checkbuttonLdExposureAutoCam%u", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pAuto);

			sprintf(widgetName, "checkbuttonLdCCDCam%u_0", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pCCD0);

			sprintf(widgetName, "checkbuttonLdCCDCam%u_1", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pCCD1);

			sprintf(widgetName, "checkbuttonLdCCDCam%u_2", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pCCD2);

			sprintf(widgetName, "checkbuttonLdCCDCam%u_3", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pCCD3);

			sprintf(widgetName, "checkbuttonLdCCDCam%u_4", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pCCD4);

			sprintf(widgetName, "checkbuttonLdCCDCam%u_5", i);
			m_refXml->get_widget(widgetName, m_exposureWidgets[i].pCCD5);
		}

		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			char widgetName[64];

			m_shutterWidgets[i].pAdjustment = new Gtk::Adjustment(0.0, 1.0, 100.0);

			sprintf(widgetName, "hscaleLdShutterCam%u", i);
			m_refXml->get_widget(widgetName, m_shutterWidgets[i].pHScale);
			m_shutterWidgets[i].pHScale->set_adjustment(*m_shutterWidgets[i].pAdjustment);

			sprintf(widgetName, "spinbuttonLdShutterCam%u", i);
			m_refXml->get_widget(widgetName, m_shutterWidgets[i].pSpinButton);
			m_shutterWidgets[i].pSpinButton->set_adjustment(*m_shutterWidgets[i].pAdjustment);

			sprintf(widgetName, "checkbuttonLdShutterOnOffCam%u", i);
			m_refXml->get_widget(widgetName, m_shutterWidgets[i].pOnOff);

			sprintf(widgetName, "checkbuttonLdShutterAutoCam%u", i);
			m_refXml->get_widget(widgetName, m_shutterWidgets[i].pAuto);
		}

		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			char widgetName[64];

			m_gainWidgets[i].pAdjustment = new Gtk::Adjustment(0.0, 1.0, 100.0);

			sprintf(widgetName, "hscaleLdGainCam%u", i);
			m_refXml->get_widget(widgetName, m_gainWidgets[i].pHScale);
			m_gainWidgets[i].pHScale->set_adjustment(*m_gainWidgets[i].pAdjustment);

			sprintf(widgetName, "spinbuttonLdGainCam%u", i);
			m_refXml->get_widget(widgetName, m_gainWidgets[i].pSpinButton);
			m_gainWidgets[i].pSpinButton->set_adjustment(*m_gainWidgets[i].pAdjustment);

			sprintf(widgetName, "checkbuttonLdGainOnOffCam%u", i);
			m_refXml->get_widget(widgetName, m_gainWidgets[i].pOnOff);

			sprintf(widgetName, "checkbuttonLdGainAutoCam%u", i);
			m_refXml->get_widget(widgetName, m_gainWidgets[i].pAuto);
		}

		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			char widgetName[64];

			sprintf(widgetName, "checkbuttonLdAutoExposureCam%u", i);
			m_refXml->get_widget(widgetName, m_pSensorForStats[i] );
		}
	}

	void LadybugSettingsPage::AttachSignals()
	{
		SetTimerConnection(
				Glib::signal_timeout().connect(
					sigc::mem_fun(*this, &LadybugSettingsPage::OnTimer),
					sk_timeout ));

		m_pCheckButtonLdJPEGQualityAuto->signal_toggled().connect(
				sigc::mem_fun(*this, &LadybugSettingsPage::OnCheckJPEGQualityAuto));

		m_pAdjLdJPEGQuality->signal_value_changed().connect(
				sigc::mem_fun(*this, &LadybugSettingsPage::OnHScaleJPEGQualityChanged));

		m_pAdjLdAutoBufferUsage->signal_value_changed().connect(
				sigc::mem_fun(*this, &LadybugSettingsPage::OnHScaleAutoBufferUsageChanged));

		// Attach the exposure handlers
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_exposureWidgets[i].pAdjustment->signal_value_changed().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureValueChanged), i ));

			m_exposureWidgets[i].pOnOff->signal_toggled().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureOnOffChecked), i));

			m_exposureWidgets[i].pAuto->signal_toggled().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureAutoChecked), i));

			m_exposureWidgets[i].pCCD0->signal_toggled().connect(
					sigc::bind<unsigned int, unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureCCDChecked), i, 0));

			m_exposureWidgets[i].pCCD1->signal_toggled().connect(
					sigc::bind<unsigned int, unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureCCDChecked), i, 1));

			m_exposureWidgets[i].pCCD2->signal_toggled().connect(
					sigc::bind<unsigned int, unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureCCDChecked), i, 2));

			m_exposureWidgets[i].pCCD3->signal_toggled().connect(
					sigc::bind<unsigned int, unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureCCDChecked), i, 3));

			m_exposureWidgets[i].pCCD4->signal_toggled().connect(
					sigc::bind<unsigned int, unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureCCDChecked), i, 4));

			m_exposureWidgets[i].pCCD5->signal_toggled().connect(
					sigc::bind<unsigned int, unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnExposureCCDChecked), i, 5));
		}

		// Attach the shutter handles
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_shutterWidgets[i].pAdjustment->signal_value_changed().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnShutterValueChanged), i ));

			m_shutterWidgets[i].pOnOff->signal_toggled().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnShutterOnOffChecked), i));

			m_shutterWidgets[i].pAuto->signal_toggled().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnShutterAutoChecked), i));
		}

		// Attach the gain handlers
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_gainWidgets[i].pAdjustment->signal_value_changed().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnGainValueChanged), i ));

			m_gainWidgets[i].pOnOff->signal_toggled().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnGainOnOffChecked), i));

			m_gainWidgets[i].pAuto->signal_toggled().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnGainAutoChecked), i));
		}

		// Attach sensor-for-statistics handlers
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_pSensorForStats[i]->signal_toggled().connect(
					sigc::bind<unsigned int>(
						sigc::mem_fun(*this, &LadybugSettingsPage::OnSensorForStatsChecked), i));
		}

	}

	void LadybugSettingsPage::OnCheckJPEGQualityAuto()
	{
		Error error;
		unsigned int value;
		error = m_pCamera->ReadRegister( sk_JpegControlReg, &value );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error reading JPEG control register", error );
		}

		if ( m_pCheckButtonLdJPEGQualityAuto->get_active() == true )
		{
			value |= 0x01000000;
			// Disable JPEG quality adjustment
			m_pHScaleLdJPEGQuality->set_sensitive( false );
			// Enable auto buffer usage adjustment
			m_pHScaleLdAutoBufferUsage->set_sensitive( true );
		}
		else
		{
			value &= 0xFEFFFFFF;
			// Ennable JPEG quality adjustment
			m_pHScaleLdJPEGQuality->set_sensitive( true );
			// Disable auto buffer usage adjustment
			m_pHScaleLdAutoBufferUsage->set_sensitive( false );

		}

		error = m_pCamera->WriteRegister( sk_JpegControlReg, value );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error writing JPEG control  register", error );
		}
	}

	void LadybugSettingsPage::OnHScaleJPEGQualityChanged()
	{
		Error error;
		double valueAdj;
		unsigned int valueReg, valueSet, value;

		valueAdj = m_pAdjLdJPEGQuality->get_value();
		valueSet =  static_cast<unsigned int>(valueAdj );

		error = m_pCamera->ReadRegister( sk_JpegControlReg, &valueReg );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error reading JPEG control register", error );
		}

		value = ( valueReg & 0xFFFFFF00 ) + ( valueSet & 0x000000FF );
		error = m_pCamera->WriteRegister( sk_JpegControlReg, value );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error writing JPEG register", error );
		}
	}

	void LadybugSettingsPage::OnHScaleAutoBufferUsageChanged()
	{
		Error error;
		double valueAdj;
		unsigned int valueReg, valueSet, value;

		valueAdj = m_pAdjLdAutoBufferUsage->get_value();
		// Auto buffer usage definition: 0% - 0x00, 100 - 0xFF
		valueSet = (unsigned int)( 127.0 *  valueAdj / 100.0 );

		error = m_pCamera->ReadRegister( sk_JpegBufferUsageReg, &valueReg );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error reading auto buffer usage register", error );
		}

		value = ( valueReg & 0xFFFFFF80 ) + ( valueSet & 0x0000007F );
		error = m_pCamera->WriteRegister( sk_JpegBufferUsageReg, value );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error writing auto buffer usage register", error );
		}
	}

	void LadybugSettingsPage::EnableJpegSettingsWidgets( bool bEnable )
	{
		m_pHScaleLdJPEGQuality->set_sensitive( bEnable );
		m_pCheckButtonLdJPEGQualityAuto->set_sensitive( bEnable );
	}

	void LadybugSettingsPage::EnableAutoBufferUsageSettingsWidgets( bool bEnable )
	{
		m_pHScaleLdAutoBufferUsage->set_sensitive( bEnable );
	}

	void LadybugSettingsPage::EnableSensorForStatsWidgets( bool bEnable )
	{
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_pSensorForStats[i]->set_sensitive( bEnable );
		}
	}

	bool LadybugSettingsPage::UpdateJpegSettingsValues()
	{
		unsigned int uiRegVal = 0;

		Error error = m_pCamera->ReadRegister(sk_JpegBufferUsageReg, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading JPEG control register", error );
		}

		if ( (uiRegVal & 0x0000007F) == 0 )
		{
			CameraInfo camInfo;
			m_pCamera->GetCameraInfo( &camInfo );
			if ( IsLadybug3())
			{
				// The default is 90% in LD3 Firmware if the value is 0
				m_pAdjLdAutoBufferUsage->set_value( 90.0 );
			}
			else
			{
				// The default is 80% in Firmware if the value is 0
				m_pAdjLdAutoBufferUsage->set_value( 80.0 );
			}
		}
		else
		{
			// Set the value
			m_pAdjLdAutoBufferUsage->set_value( 100.0 *  (double)(uiRegVal & 0x0000007F) / 127.0 );
		}

		error = m_pCamera->ReadRegister(sk_JpegControlReg, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading JPEG control register", error );
		}

		if ( uiRegVal & 0x01000000 )
		{
			m_pCheckButtonLdJPEGQualityAuto->set_active(true);
		}
		else
		{
			m_pCheckButtonLdJPEGQualityAuto->set_active(false);
		}

		if ( ( uiRegVal & 0x000000FF) == 0 )
		{
			// The default is 60% in Firmware if the value is 0
			m_pAdjLdJPEGQuality->set_value( 60 );
		}
		else
		{
			m_pAdjLdJPEGQuality->set_value( ( uiRegVal & 0x000000FF) );
		}

		return true;
	}

	bool LadybugSettingsPage::OnTimer()
	{
		if (m_pCamera == NULL || !IsUpdateable() || !m_isLadybug )
		{
			return true;
		}

		Gtk::Notebook* pNotebook;
		m_refXml->get_widget( "notebookCamCtl", pNotebook );
		if ( pNotebook->get_current_page() == 14 )
		{
			UpdateJpegSettingsValues();
			if ( m_independentExposureSupported )
			{
				UpdateAllAECSettings( );
			}

			UpdateSensorForStatsSettings();
		}

		return true;
	}


	void LadybugSettingsPage::UpdateAllAECSettings( )
	{
		Glib::Mutex::Lock updateLock( m_valueChangeMutex, Glib::NOT_LOCK );
		if ( updateLock.try_acquire() != true )
		{
			return;
		}

		UpdateShutterSettings( );
		UpdateGainSettings( );
		UpdateExposureSettings( );
	}

	void LadybugSettingsPage::UpdateShutterSettings( )
	{
		Error error;
		unsigned int uiRegVal = 0;
		unsigned int uiValue = 0;
		PropertyInfo camPropInfo;

		// Get the SHUTTER property info to update the max/min value
		camPropInfo.type = SHUTTER;
		Error getPropInfoErr = m_pCamera->GetPropertyInfo( &camPropInfo );
		if ( getPropInfoErr != PGRERROR_OK )
		{
			return;
		}
		// Update max/min values
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_shutterWidgets[i].pAdjustment->set_lower( camPropInfo.min );
			m_shutterWidgets[i].pAdjustment->set_upper( camPropInfo.max );
		}

		// For all independent shutter registers
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			error = m_pCamera->ReadRegister( m_independentExposureRegBase + 0x20 * i + 0x04, &uiRegVal);
			if (error != PGRERROR_OK)
			{
				ShowErrorMessageDialog( "Error reading independent exposure  inquiry register", error );
			}

			if ( !(uiRegVal & 0x80000000) )
			{
				// Not present
				EnableShutterWidgets( i, false );
				continue;
			}

			// Bit-6 is On/Off
			UpdateCheckButton( m_shutterWidgets[i].pOnOff, (uiRegVal & 0x02000000)>0 );
			// Bit-7 is Auto
			UpdateCheckButton( m_shutterWidgets[i].pAuto, (uiRegVal & 0x01000000)>0 );
			// Bit-20:31 is the shutter value
			uiValue = ( uiRegVal & 0xFFF );
			if ( m_shutterWidgets[i].pAdjustment->get_value() != uiValue )
			{
				m_shutterWidgets[i].pAdjustment->set_value( uiValue );
			}
		}
	};

	void LadybugSettingsPage::UpdateGainSettings( )
	{
		Error error;
		unsigned int uiRegVal = 0;
		unsigned int uiValue = 0;

		PropertyInfo camPropInfo;
		// Get the GAIN property info
		camPropInfo.type = GAIN;
		Error getPropInfoErr = m_pCamera->GetPropertyInfo( &camPropInfo );
		if ( getPropInfoErr != PGRERROR_OK )
		{
			return;
		}
		// Update the gain max/min values
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_gainWidgets[i].pAdjustment->set_lower( camPropInfo.min );
			m_gainWidgets[i].pAdjustment->set_upper( camPropInfo.max );
		}

		// For all independent gain registers
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			error = m_pCamera->ReadRegister( m_independentExposureRegBase + 0x20 * i, &uiRegVal);
			if (error != PGRERROR_OK)
			{
				ShowErrorMessageDialog( "Error reading independent exposure  inquiry register", error );
			}

			if ( !(uiRegVal & 0x80000000) )
			{
				// Not present
				EnableGainWidgets( i, false );
				continue;
			}

			// Bit-6 is On/Off
			UpdateCheckButton( m_gainWidgets[i].pOnOff, (uiRegVal & 0x02000000)>0 );
			// Bit-7 is Auto
			UpdateCheckButton( m_gainWidgets[i].pAuto, (uiRegVal & 0x01000000)>0 );
			// Bit-20:31 is the gain value
			uiValue = ( uiRegVal & 0xFFF );
			if ( m_gainWidgets[i].pAdjustment->get_value() != uiValue )
			{
				m_gainWidgets[i].pAdjustment->set_value( uiValue );
			}
		}

	};

	void LadybugSettingsPage::UpdateExposureSettings( )
	{
		Error error;
		unsigned int uiRegVal = 0;
		unsigned int uiValue = 0;

		PropertyInfo camPropInfo;
		// Get the AUTO_EXPOSURE property info
		camPropInfo.type = AUTO_EXPOSURE;
		Error getPropInfoErr = m_pCamera->GetPropertyInfo( &camPropInfo );
		if ( getPropInfoErr != PGRERROR_OK )
		{
			return;
		}
		// Update max/min values
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			m_exposureWidgets[i].pAdjustment->set_lower( camPropInfo.min );
			m_exposureWidgets[i].pAdjustment->set_upper( camPropInfo.max );
		}

		// For all independent auto exposure registers
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			error = m_pCamera->ReadRegister( m_independentExposureRegBase + 0x20 * i + 0x08, &uiRegVal);
			if (error != PGRERROR_OK)
			{
				ShowErrorMessageDialog( "Error reading independent exposure  inquiry register", error );
			}

			if ( !(uiRegVal & 0x80000000) )
			{
				// Not present
				EnableExposureWidgets( i, false );
				continue;
			}

			// Bit-6 is On/Off
			UpdateCheckButton( m_exposureWidgets[i].pOnOff, (uiRegVal & 0x02000000)>0 );
			// Bit-7 is Auto
			UpdateCheckButton( m_exposureWidgets[i].pAuto, (uiRegVal & 0x01000000)>0 );
			// Bit-20:31 is the auto exposure value
			uiValue = ( uiRegVal & 0xFFF );
			if ( m_exposureWidgets[i].pAdjustment->get_value() != uiValue )
			{
				m_exposureWidgets[i].pAdjustment->set_value( uiValue );
			}

			// Bit-14:19 Sensor_Mask
			//if ( m_independentExposureSensorMaskSupported )
			{
				UpdateCheckButton( m_exposureWidgets[i].pCCD5, (uiRegVal & 0x00020000)>0 );
				UpdateCheckButton( m_exposureWidgets[i].pCCD4, (uiRegVal & 0x00010000)>0 );
				UpdateCheckButton( m_exposureWidgets[i].pCCD3, (uiRegVal & 0x00008000)>0 );
				UpdateCheckButton( m_exposureWidgets[i].pCCD2, (uiRegVal & 0x00004000)>0 );
				UpdateCheckButton( m_exposureWidgets[i].pCCD1, (uiRegVal & 0x00002000)>0 );
				UpdateCheckButton( m_exposureWidgets[i].pCCD0, (uiRegVal & 0x00001000)>0 );
			}
		}


	};

	void LadybugSettingsPage::UpdateSensorForStatsSettings( )
	{
		Error error;
		unsigned int uiRegVal = 0;

		if ( m_pSensorForStats[0]->get_state() == Gtk::STATE_INSENSITIVE )
		{
			// Test anyone(0) is enabled or not.
			// If disabled, do nothing.
			return;
		}

		error = m_pCamera->ReadRegister( sk_AE_Stats_MaskReg, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading auto exposure statistics register", error );
		}

		bool bCheck = false;
		for (unsigned int i=0; i < sk_numCameras; i++)
		{
			bCheck = (( 0x01 << ( sk_numCameras - i - 1)) & uiRegVal ) != 0;
			UpdateCheckButton( m_pSensorForStats[i], bCheck );
		}
	}

	void LadybugSettingsPage::UpdateCheckButton( Gtk::CheckButton* pButton, bool bVal )
	{
		if ( pButton == NULL )
		{
			return;
		}

		if ( pButton->get_state() == Gtk::STATE_INSENSITIVE )
		{
			pButton->set_sensitive( true );
		}

		if ( pButton->get_active() != bVal )
		{
			pButton->set_active( bVal );
		}
	}

	void LadybugSettingsPage::EnableAllAECWidgets( bool bEnable )
	{
		for (unsigned int i=0; i < sk_numCameras; i++)
		{

			EnableGainWidgets( i, bEnable );
			EnableShutterWidgets( i, bEnable );
			EnableExposureWidgets( i, bEnable );
		}
	}

	void LadybugSettingsPage::EnableGainWidgets( unsigned int camera, bool bEnable )
	{
		// Enable or disable
		m_gainWidgets[camera].pHScale->set_sensitive( bEnable );
		m_gainWidgets[camera].pSpinButton->set_sensitive( bEnable );
		m_gainWidgets[camera].pOnOff->set_sensitive( bEnable );
		m_gainWidgets[camera].pAuto->set_sensitive( bEnable );
	}

	void LadybugSettingsPage::EnableShutterWidgets( unsigned int camera, bool bEnable )
	{
		// Enable or disable
		m_shutterWidgets[camera].pHScale->set_sensitive( bEnable );
		m_shutterWidgets[camera].pSpinButton->set_sensitive( bEnable );
		m_shutterWidgets[camera].pOnOff->set_sensitive( bEnable );
		m_shutterWidgets[camera].pAuto->set_sensitive( bEnable );
	}

	void LadybugSettingsPage::EnableExposureWidgets( unsigned int camera, bool bEnable )
	{
		// Enable or disable
		m_exposureWidgets[camera].pHScale->set_sensitive( bEnable );
		m_exposureWidgets[camera].pSpinButton->set_sensitive( bEnable );
		m_exposureWidgets[camera].pOnOff->set_sensitive( bEnable );
		m_exposureWidgets[camera].pAuto->set_sensitive( bEnable );

		m_exposureWidgets[camera].pCCD0->set_sensitive( bEnable );
		m_exposureWidgets[camera].pCCD1->set_sensitive( bEnable );
		m_exposureWidgets[camera].pCCD2->set_sensitive( bEnable );
		m_exposureWidgets[camera].pCCD3->set_sensitive( bEnable );
		m_exposureWidgets[camera].pCCD4->set_sensitive( bEnable );
		m_exposureWidgets[camera].pCCD5->set_sensitive( bEnable  );
	}

	void LadybugSettingsPage::OnExposureValueChanged(unsigned int cameraIdx)
	{
		double valueAdj = m_exposureWidgets[cameraIdx].pAdjustment->get_value();
		unsigned int valueRegAdj = static_cast<unsigned int>(valueAdj);

		SetAdjustedValueInReg(cameraIdx, valueRegAdj, sk_Ind_Exp_Reg_Offset_Exposure );
	}

	void LadybugSettingsPage::OnExposureOnOffChecked(unsigned int cameraIdx)
	{
		bool checked = m_exposureWidgets[cameraIdx].pOnOff->get_active();
		SetCheckedBitInReg( cameraIdx, checked, sk_Ind_Exp_Reg_Offset_Exposure, sk_Ind_Exp_Reg_OnOffBitMask );
	}

	void LadybugSettingsPage::OnExposureAutoChecked(unsigned int cameraIdx)
	{
		bool checked = m_exposureWidgets[cameraIdx].pAuto->get_active();
		SetCheckedBitInReg( cameraIdx, checked, sk_Ind_Exp_Reg_Offset_Exposure, sk_Ind_Exp_Reg_AutoBitMask );
	}

	void LadybugSettingsPage::OnExposureCCDChecked(unsigned int cameraIdx, unsigned int CCD)
	{
		Error error;
		unsigned int uiRegVal = 0;
		unsigned int uiValue = 0;

		error = m_pCamera->ReadRegister( m_independentExposureRegBase + 0x20 * cameraIdx + 0x08, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading independent exposure  inquiry register", error );
		}

		bool bActive = false;
		switch ( CCD )
		{
			case 0: bActive = m_exposureWidgets[cameraIdx].pCCD0->get_active();
					break;
			case 1: bActive = m_exposureWidgets[cameraIdx].pCCD1->get_active();
					break;
			case 2: bActive = m_exposureWidgets[cameraIdx].pCCD2->get_active();
					break;
			case 3: bActive = m_exposureWidgets[cameraIdx].pCCD3->get_active();
					break;
			case 4: bActive = m_exposureWidgets[cameraIdx].pCCD4->get_active();
					break;
			case 5: bActive = m_exposureWidgets[cameraIdx].pCCD5->get_active();
					break;
		}
		// Bit-14:19 Sensor_Mask
		if ( bActive )
			uiValue = uiRegVal | (0x00001000 << CCD) ;
		else
			uiValue = uiRegVal & (~(0x00001000 << CCD)) ;

		error = m_pCamera->WriteRegister( m_independentExposureRegBase + 0x20 * cameraIdx + 0x08, uiValue);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error writing independent shutter register", error );
		}
	}

	void LadybugSettingsPage::OnShutterValueChanged(unsigned int cameraIdx)
	{
		double valueAdj = m_shutterWidgets[cameraIdx].pAdjustment->get_value();
		unsigned int valueRegAdj = static_cast<unsigned int>(valueAdj);

		SetAdjustedValueInReg(cameraIdx, valueRegAdj, sk_Ind_Exp_Reg_Offset_Shutter );
	}

	void LadybugSettingsPage::OnShutterOnOffChecked(unsigned int cameraIdx)
	{
		bool checked = m_shutterWidgets[cameraIdx].pOnOff->get_active();
		SetCheckedBitInReg( cameraIdx, checked, sk_Ind_Exp_Reg_Offset_Shutter, sk_Ind_Exp_Reg_OnOffBitMask );
	}

	void LadybugSettingsPage::OnShutterAutoChecked(unsigned int cameraIdx)
	{
		bool checked = m_shutterWidgets[cameraIdx].pAuto->get_active();
		SetCheckedBitInReg( cameraIdx, checked, sk_Ind_Exp_Reg_Offset_Shutter, sk_Ind_Exp_Reg_AutoBitMask );
	}

	void LadybugSettingsPage::OnGainValueChanged(unsigned int cameraIdx)
	{
		double valueAdj = m_gainWidgets[cameraIdx].pAdjustment->get_value();
		unsigned int valueRegAdj = static_cast<unsigned int>(valueAdj);

		SetAdjustedValueInReg(cameraIdx, valueRegAdj, sk_Ind_Exp_Reg_Offset_Gain );
	}

	void LadybugSettingsPage::OnGainOnOffChecked(unsigned int cameraIdx)
	{
		bool checked = m_gainWidgets[cameraIdx].pOnOff->get_active();
		SetCheckedBitInReg( cameraIdx, checked, sk_Ind_Exp_Reg_Offset_Gain, sk_Ind_Exp_Reg_OnOffBitMask );
	}

	void LadybugSettingsPage::OnGainAutoChecked(unsigned int cameraIdx)
	{
		bool checked = m_gainWidgets[cameraIdx].pAuto->get_active();
		SetCheckedBitInReg( cameraIdx, checked, sk_Ind_Exp_Reg_Offset_Gain, sk_Ind_Exp_Reg_AutoBitMask );
	}

	void LadybugSettingsPage::OnSensorForStatsChecked(unsigned int cameraIdx)
	{
		Error error;
		unsigned int uiRegVal = 0;
		unsigned int uiValue = 0;

		bool checked = m_pSensorForStats[cameraIdx]->get_active();

		error = m_pCamera->ReadRegister( sk_AE_Stats_MaskReg, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading auto exposure statistics register", error );
		}

		unsigned int bitMask = ( 0x01 ) << (sk_numCameras - cameraIdx - 1);
		if ( checked )
			uiValue = uiRegVal | bitMask;
		else
			uiValue = uiRegVal & (~bitMask);

		error = m_pCamera->WriteRegister( sk_AE_Stats_MaskReg, uiValue);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error writing auto exposure statistics register", error );
		}

	}

	void LadybugSettingsPage::SetAdjustedValueInReg(unsigned int cameraIdx, unsigned int valueToSet, unsigned int regOffset )
	{
		Error error;
		unsigned int uiRegVal = 0;
		unsigned int uiValue = 0;

		Glib::Mutex::Lock valueChangeLock( m_valueChangeMutex, Glib::NOT_LOCK );
		if ( valueChangeLock.try_acquire() != true )
		{
			return;
		}

		error = m_pCamera->ReadRegister( m_independentExposureRegBase + 0x20 * cameraIdx + regOffset, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading independent exposure control register", error );
		}

		uiValue = uiRegVal & 0xFFFFF000;
		uiValue = uiValue  | ( valueToSet & 0xFFF );

		error = m_pCamera->WriteRegister( m_independentExposureRegBase + 0x20 * cameraIdx + regOffset, uiValue);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error writing independent exposure control register", error );
		}
	}

	void LadybugSettingsPage::SetCheckedBitInReg(unsigned int cameraIdx, bool active, unsigned int regOffset, unsigned int bitMask )
	{
		Error error;
		unsigned int uiRegVal = 0;
		unsigned int uiValue = 0;

		Glib::Mutex::Lock valueChangeLock( m_valueChangeMutex, Glib::NOT_LOCK );
		if ( valueChangeLock.try_acquire() != true )
		{
			return;
		}

		error = m_pCamera->ReadRegister( m_independentExposureRegBase + 0x20 * cameraIdx + regOffset, &uiRegVal);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error reading independent exposure control register", error );
		}

		if ( active )
			uiValue = uiRegVal | bitMask;
		else
			uiValue = uiRegVal & (~bitMask);

		error = m_pCamera->WriteRegister( m_independentExposureRegBase + 0x20 * cameraIdx + regOffset, uiValue);
		if (error != PGRERROR_OK)
		{
			ShowErrorMessageDialog( "Error writing independent exposure control register", error );
		}
	}
}
