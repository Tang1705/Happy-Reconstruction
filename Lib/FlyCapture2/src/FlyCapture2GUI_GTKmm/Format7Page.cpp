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
// $Id: Format7Page.cpp,v 1.90 2010/12/03 19:24:42 soowei Exp $
//=============================================================================

#include "Precompiled.h"
#include "Format7Page.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

namespace FlyCapture2
{
	const char* Format7Page::sk_vboxMode = "vboxF7Mode";
	const char* Format7Page::sk_comboBoxMode = "comboboxMode";

	const char* Format7Page::sk_comboBoxPixelFormat = "comboboxPixelFormat";

	const char* Format7Page::sk_labelJpegCompressionStatus = "labelJpegCompressionStatus";
	const char* Format7Page::sk_hscaleJpegQuality = "hscaleJpegQuality";

	const char* Format7Page::sk_vboxGigEBinning = "vboxGigEBinning";
	const char* Format7Page::sk_spinGigEHorzBinning = "spinbuttonGigEHorzBinning";
	const char* Format7Page::sk_spinGigEVertBinning = "spinbuttonGigEVertBinning";
	const char* Format7Page::sk_checkGigEAveragingEnabled = "checkbuttonGigEAveragingEnabled";

	const char* Format7Page::sk_labelCursor = "labelCursor";
	const char* Format7Page::sk_labelMaxImageSize = "labelMaxImageSize";
	const char* Format7Page::sk_labelImageSizeUnits = "labelImageSizeUnits";
	const char* Format7Page::sk_labelOffsetUnits = "labelOffsetUnits";
	const char* Format7Page::sk_labelResizeInformation = "labelResizeInformation";

	const char* Format7Page::sk_spinF7Left = "spinF7Left";
	const char* Format7Page::sk_spinF7Top = "spinF7Top";
	const char* Format7Page::sk_spinF7Width = "spinF7Width";
	const char* Format7Page::sk_spinF7Height = "spinF7Height";
	const char* Format7Page::sk_buttonCenterROI = "buttonCenterROI";

	const char* Format7Page::sk_vboxF7PacketSize = "vboxF7PacketSize";
	const char* Format7Page::sk_labelMaxPacketSize = "labelMaxPacketSize";
	const char* Format7Page::sk_labelMinPacketSize = "labelMinPacketSize";
	const char* Format7Page::sk_spinCurrPacketSize = "spinCurrPacketSize";
	const char* Format7Page::sk_hscalePacketSize = "hscalePacketSize";

	const char* Format7Page::sk_vboxGigEPacketSize = "vboxGigEPacketSize";
	const char* Format7Page::sk_spinGigECurrPacketSize = "spinGigEPacketSize";
	const char* Format7Page::sk_hscaleGigEPacketSize = "hscaleGigEPacketSize";

	const char* Format7Page::sk_vboxGigEPacketDelay = "vboxGigEPacketDelay";
	const char* Format7Page::sk_spinGigECurrPacketDelay = "spinGigEPacketDelay";
	const char* Format7Page::sk_hscaleGigEPacketDelay = "hscaleGigEPacketDelay";

	const char* Format7Page::sk_btnApply = "btnApply";
	const char* Format7Page::sk_drawingareaFormat7 = "drawingareaFormat7";

	Format7Page::Format7Page()
	{
		m_pDrawingArea = NULL;
		m_isLadybugCamera = IsLadybugDLLPresent();
	}

	Format7Page::Format7Page( CameraBase* pCamera, Glib::RefPtr<Gnome::Glade::Xml> refXml ) : BasePage( pCamera, refXml )
	{
		m_pDrawingArea = NULL;
		m_isLadybugCamera = IsLadybugDLLPresent() && IsLadybug();
	}

	Format7Page::~Format7Page()
	{
		if ( m_pAdjustmentF7Left != NULL )
		{
			delete m_pAdjustmentF7Left;
			m_pAdjustmentF7Left = NULL;
		}

		if ( m_pAdjustmentF7Top != NULL )
		{
			delete m_pAdjustmentF7Top;
			m_pAdjustmentF7Top = NULL;
		}

		if ( m_pAdjustmentF7Width != NULL )
		{
			delete m_pAdjustmentF7Width;
			m_pAdjustmentF7Width = NULL;
		}

		if ( m_pAdjustmentF7Height != NULL )
		{
			delete m_pAdjustmentF7Height;
			m_pAdjustmentF7Height = NULL;
		}

		if ( m_pAdjustmentPacketSize != NULL )
		{
			delete m_pAdjustmentPacketSize;
			m_pAdjustmentPacketSize = NULL;
		}

		if (m_pAdjustmentJpegQuality != NULL)
		{
			delete m_pAdjustmentJpegQuality;
			m_pAdjustmentJpegQuality = NULL;
		}

		if ( m_pAdjustmentGigEHorzBinning != NULL )
		{
			delete m_pAdjustmentGigEHorzBinning;
			m_pAdjustmentGigEHorzBinning = NULL;
		}

		if ( m_pAdjustmentGigEVertBinning != NULL )
		{
			delete m_pAdjustmentGigEVertBinning;
			m_pAdjustmentGigEVertBinning = NULL;
		}

		if ( m_pAdjustmentGigEPacketSize != NULL )
		{
			delete m_pAdjustmentGigEPacketSize;
			m_pAdjustmentGigEPacketSize = NULL;
		}

		if ( m_pAdjustmentGigEPacketDelay != NULL )
		{
			delete m_pAdjustmentGigEPacketDelay;
			m_pAdjustmentGigEPacketDelay = NULL;
		}

		if ( m_pDrawingArea != NULL )
		{
			delete m_pDrawingArea;
			m_pDrawingArea = NULL;
		}
	}

	void Format7Page::UpdateWidgets()
	{
		if ( m_pCamera == NULL || IsConnected() != true )
		{
			return;
		}

		if ( m_camInfo.interfaceType == INTERFACE_GIGE )
		{
			m_pVboxF7PacketSize->hide();
			m_pVBoxGigEBinning->show();
			m_pVboxGigEPacketSize->show();
			m_pVboxGigEPacketDelay->show();
		}
		else
		{
			m_pVboxF7PacketSize->show();
			m_pVBoxGigEBinning->hide();
			m_pVboxGigEPacketSize->hide();
			m_pVboxGigEPacketDelay->hide();
		}

		if ( IsIIDC() )
		{
			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);
			Mode modeToPopulate;
			PixelFormat pixelFormatToPopulate;

			const unsigned int k_f7InqReg = 0x19C;
			unsigned int f7InqRegVal = 0;
			Error error = pCamera->ReadRegister(k_f7InqReg, &f7InqRegVal);
			if (error != PGRERROR_OK || f7InqRegVal == 0)
			{
				DisableWidgets();
				return;
			}

			if ( IsCurrentlyInFormat7() == true )
			{
				// Currently in Format 7, get the current config and use it
				// to populate the combo boxes
				Format7ImageSettings imageSettings;
				unsigned int packetSize;
				float speed;

				Error error = pCamera->GetFormat7Configuration( &imageSettings, &packetSize, &speed );
				if ( error != PGRERROR_OK )
				{
					// Error
					ShowErrorMessageDialog( "Error getting current Format7 configuration", error );
				}

				modeToPopulate = imageSettings.mode;
				pixelFormatToPopulate = imageSettings.pixelFormat;
			}
			else
			{
				// Populate using the lowest mode (usually 0)
				modeToPopulate = GetLowestMode();
				pixelFormatToPopulate = GetLowestPixelFormat( modeToPopulate );
			}

			bool supported;
			Format7Info fmt7Info;
			fmt7Info.mode = modeToPopulate;

			error = pCamera->GetFormat7Info( &fmt7Info, &supported );
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error querying Format7 information", error );
			}

			PopulateModeComboBox();
			PopulatePixelFormatComboBox(fmt7Info.pixelFormatBitField, fmt7Info.vendorPixelFormatBitField);

			// Populate fields with camera settings for given mode
			SetActiveModeComboBox( modeToPopulate );
			OnComboBoxModeChanged();

			ValidateImageSize();
			ValidatePacketSize();

			UpdateResizeInformation();
		}
		else if ( IsGEV() )
		{
			GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

			// Update the packet size
			UpdateGigEPacketInfo();

			// Update the packet delay value
			UpdateGigEPacketDelay();

			GigEImageSettings imageSettings;
			Error error = pCamera->GetGigEImageSettings( &imageSettings );
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error getting current GigE image configuration", error );
			}

			GigEImageSettingsInfo imageSettingsInfo;
			error = pCamera->GetGigEImageSettingsInfo( &imageSettingsInfo );
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error querying GigE image information", error );
			}

			// Get the current imaging mode
			Mode currMode;
			error = pCamera->GetGigEImagingMode(&currMode);
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error querying GigE imaging mode", error );
			}

			PopulateModeComboBox();
			SetActiveModeComboBox(currMode);

			PopulatePixelFormatComboBox(imageSettingsInfo.pixelFormatBitField, imageSettingsInfo.vendorPixelFormatBitField);

			// Set the appropriate mode and pixel format as active
			SetActivePixelFormatComboBox( imageSettings.pixelFormat );

			// Update image information
			UpdateGigEImageInfo();

			// Make sure the initial state of the binning spin controls is green
			Gdk::Color color_green = GetColorAccentGreen();
			m_pSpinGigEHorzBinning->modify_base(Gtk::STATE_NORMAL, color_green);
			m_pSpinGigEVertBinning->modify_base(Gtk::STATE_NORMAL, color_green);

			UpdateResizeInformation();
		}

		UpdateJpegInformation();

		EnableWidgets();
	}

	void Format7Page::GetWidgets()
	{
		m_refXml->get_widget( sk_vboxMode, m_pVBoxF7Mode );
		m_refXml->get_widget( sk_comboBoxMode, m_pComboBoxMode );

		m_refXml->get_widget( sk_comboBoxPixelFormat, m_pComboBoxPixelFormat );

		m_refXml->get_widget( sk_labelJpegCompressionStatus, m_pLabelJpegCompressionStatus );
		m_refXml->get_widget( sk_hscaleJpegQuality, m_pHscaleJpegQuality );

		m_refXml->get_widget( sk_vboxGigEBinning, m_pVBoxGigEBinning );
		m_refXml->get_widget( sk_spinGigEHorzBinning, m_pSpinGigEHorzBinning );
		m_refXml->get_widget( sk_spinGigEVertBinning, m_pSpinGigEVertBinning );
		m_refXml->get_widget( sk_checkGigEAveragingEnabled, m_pCheckGigEAveragingEnabled );

		m_refXml->get_widget( sk_labelMaxImageSize, m_pLabelMaxImageSize );
		m_refXml->get_widget( sk_labelImageSizeUnits, m_pLabelImageSizeUnits );
		m_refXml->get_widget( sk_labelOffsetUnits, m_pLabelOffsetUnits );
		m_refXml->get_widget( sk_labelResizeInformation, m_pLabelResizeInformation );

		m_refXml->get_widget( sk_spinF7Left, m_pSpinF7Left );
		m_refXml->get_widget( sk_spinF7Top, m_pSpinF7Top );
		m_refXml->get_widget( sk_spinF7Width, m_pSpinF7Width );
		m_refXml->get_widget( sk_spinF7Height, m_pSpinF7Height );
		m_refXml->get_widget( sk_buttonCenterROI, m_pButtonCenterROI );

		m_refXml->get_widget( sk_vboxF7PacketSize, m_pVboxF7PacketSize );
		m_refXml->get_widget( sk_labelMaxPacketSize, m_pLabelMaxPacketSize );
		m_refXml->get_widget( sk_labelMinPacketSize, m_pLabelMinPacketSize );
		m_refXml->get_widget( sk_spinCurrPacketSize, m_pSpinCurrPacketSize );
		m_refXml->get_widget( sk_hscalePacketSize, m_pHScalePacketSize );

		m_refXml->get_widget( sk_vboxGigEPacketSize, m_pVboxGigEPacketSize );
		m_refXml->get_widget( sk_spinGigECurrPacketSize, m_pSpinGigEPacketSize );
		m_refXml->get_widget( sk_hscaleGigEPacketSize, m_pHScaleGigEPacketSize );

		m_refXml->get_widget( sk_vboxGigEPacketDelay, m_pVboxGigEPacketDelay );
		m_refXml->get_widget( sk_spinGigECurrPacketDelay, m_pSpinGigEPacketDelay );
		m_refXml->get_widget( sk_hscaleGigEPacketDelay, m_pHScaleGigEPacketDelay );

		m_refXml->get_widget( sk_btnApply, m_pBtnApply );
		m_refXml->get_widget_derived( sk_drawingareaFormat7, m_pDrawingArea );

		m_pAdjustmentJpegQuality = new Gtk::Adjustment(0.0, 0.0, 100.0);
		m_pHscaleJpegQuality->set_adjustment(*m_pAdjustmentJpegQuality);

		const int k_binningMin = 1;
		const int k_binningMax = 4;
		const int k_binningCurr = 1;
		const int k_binningStep = 1;

		m_pAdjustmentGigEHorzBinning = new Gtk::Adjustment( k_binningCurr, k_binningMin, k_binningMax, k_binningStep, k_binningStep);
		m_pSpinGigEHorzBinning->set_adjustment( *m_pAdjustmentGigEHorzBinning );

		m_pAdjustmentGigEVertBinning = new Gtk::Adjustment( k_binningCurr, k_binningMin, k_binningMax, k_binningStep, k_binningStep);
		m_pSpinGigEVertBinning->set_adjustment( *m_pAdjustmentGigEVertBinning );

		// Hide averaging check box
		m_pCheckGigEAveragingEnabled->hide();

		const int k_adjF7Min = 0;
		const int k_adjF7Max = 128;
		const int k_adjF7Curr = 0;

		m_pAdjustmentF7Left = new Gtk::Adjustment( k_adjF7Curr, k_adjF7Min, k_adjF7Max );
		m_pSpinF7Left->set_adjustment( *m_pAdjustmentF7Left );

		m_pAdjustmentF7Top = new Gtk::Adjustment( k_adjF7Curr, k_adjF7Min, k_adjF7Max );
		m_pSpinF7Top->set_adjustment( *m_pAdjustmentF7Top );

		m_pAdjustmentF7Width = new Gtk::Adjustment( k_adjF7Curr, k_adjF7Min, k_adjF7Max );
		m_pSpinF7Width->set_adjustment( *m_pAdjustmentF7Width );

		m_pAdjustmentF7Height = new Gtk::Adjustment( k_adjF7Curr, k_adjF7Min, k_adjF7Max );
		m_pSpinF7Height->set_adjustment( *m_pAdjustmentF7Height );

		const int k_adjPacketSizeMin = 8;
		const int k_adjPacketSizeMax = 15040;
		const int k_adjPacketSizeCurr = 15040;

		m_pAdjustmentPacketSize = new Gtk::Adjustment( k_adjPacketSizeCurr, k_adjPacketSizeMin, k_adjPacketSizeMax );
		m_pHScalePacketSize->set_adjustment(*m_pAdjustmentPacketSize);
		m_pSpinCurrPacketSize->set_adjustment(*m_pAdjustmentPacketSize);

		const int k_adjGigEPacketSizeMin = 576;
		const int k_adjGigEPacketSizeMax = 9000;
		const int k_adjGigEPacketSizeCurr = 9000;

		m_pAdjustmentGigEPacketSize = new Gtk::Adjustment(k_adjGigEPacketSizeCurr, k_adjGigEPacketSizeMin, k_adjGigEPacketSizeMax);
		m_pHScaleGigEPacketSize->set_adjustment(*m_pAdjustmentGigEPacketSize);
		m_pSpinGigEPacketSize->set_adjustment(*m_pAdjustmentGigEPacketSize);

		const int k_adjGigEPacketDelayMin = 0;
		const int k_adjGigEPacketDelayMax = 6250;
		const int k_adjGigEPacketDelayCurr = 400;

		m_pAdjustmentGigEPacketDelay = new Gtk::Adjustment(k_adjGigEPacketDelayCurr, k_adjGigEPacketDelayMin, k_adjGigEPacketDelayMax);
		m_pHScaleGigEPacketDelay->set_adjustment(*m_pAdjustmentGigEPacketDelay);
		m_pSpinGigEPacketDelay->set_adjustment(*m_pAdjustmentGigEPacketDelay);

		m_refListStoreModes = Gtk::ListStore::create( m_modeColumns );
		m_pComboBoxMode->set_model( m_refListStoreModes );

		m_refListStorePixelFormats = Gtk::ListStore::create( m_pixelFormatColumns );
		m_pComboBoxPixelFormat->set_model( m_refListStorePixelFormats );
	}

	void Format7Page::AttachSignals()
	{
		m_pComboBoxMode->signal_changed().connect( sigc::mem_fun( *this, &Format7Page::OnComboBoxModeChanged ) );
		m_sigctlPixelFormat = m_pComboBoxPixelFormat->signal_changed().connect( sigc::mem_fun( *this, &Format7Page::OnComboBoxPixelFormatChanged ) );

		m_pButtonCenterROI->signal_clicked().connect( sigc::mem_fun( *this, &Format7Page::OnCenterROI ), false);

		m_pHscaleJpegQuality->signal_value_changed().connect(sigc::mem_fun( *this, &Format7Page::OnHScaleJpegQualityChanged ));

		m_pSpinGigEHorzBinning->signal_focus_out_event().connect( sigc::mem_fun( *this, &Format7Page::OnSpinBinningValueFocusLost ) );
		m_pSpinGigEVertBinning->signal_focus_out_event().connect( sigc::mem_fun( *this, &Format7Page::OnSpinBinningValueFocusLost ) );

		m_pAdjustmentGigEHorzBinning->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinBinningValueChanged ), false );
		m_pAdjustmentGigEVertBinning->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinBinningValueChanged ), false );

		m_pSpinF7Left->signal_focus_out_event().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeFocusLost ), false );
		m_pSpinF7Top->signal_focus_out_event().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeFocusLost ), false );
		m_pSpinF7Width->signal_focus_out_event().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeFocusLost ), false );
		m_pSpinF7Height->signal_focus_out_event().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeFocusLost ), false );



		m_sigctlF7Left = m_pAdjustmentF7Left->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );
		m_sigctlF7Top = m_pAdjustmentF7Top->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );
		m_sigctlF7Width = m_pAdjustmentF7Width->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );
		m_sigctlF7Height = m_pAdjustmentF7Height->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );

		m_pSpinCurrPacketSize->signal_focus_out_event().connect( sigc::mem_fun( *this, &Format7Page::OnSpinF7PacketSizeFocusLost ), false );
		m_pAdjustmentPacketSize->signal_value_changed().connect( sigc::mem_fun(*this, &Format7Page::OnF7PacketSizeChanged) );

		m_pBtnApply->signal_clicked().connect( sigc::mem_fun( *this, &Format7Page::OnApply ) );

		m_pDrawingArea->signal_image_size_changed().connect( sigc::mem_fun( *this, &Format7Page::OnImageSizeChanged));
		m_pDrawingArea->signal_drawing_area_pressed().connect(sigc::mem_fun( *this, &Format7Page::OnDrawingAreaPressed));
	}

	void Format7Page::OnDrawingAreaPressed()
	{
		//temproray disconnect setting image on adjustment change, will resume the connection when user releases the drawing area
		m_sigctlF7Left.disconnect();
		m_sigctlF7Top.disconnect();
		m_sigctlF7Width.disconnect();
		m_sigctlF7Height.disconnect();
	}

	void Format7Page::OnComboBoxModeChanged()
	{
		Mode selectedMode = GetActiveModeComboBox();
		if ( selectedMode == NUM_MODES )
		{
			return;
		}

		Error error;

		if ( IsIIDC() )
		{
			Error error;
			char entry[128];

			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

			bool supported;
			Format7Info fmt7Info;
			fmt7Info.pixelFormatBitField = 0;
			fmt7Info.mode = selectedMode;
			error = pCamera->GetFormat7Info( &fmt7Info, &supported );
			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error querying Format7 information", error );
			}

			// Common labels
			sprintf( entry, "%u x %u", fmt7Info.maxWidth, fmt7Info.maxHeight );
			m_pLabelMaxImageSize->set_text( entry );

			sprintf( entry, "%u(H), %u(V)", fmt7Info.imageHStepSize, fmt7Info.imageVStepSize );
			m_pLabelImageSizeUnits->set_text( entry );

			sprintf( entry, "%u(H), %u(V)", fmt7Info.offsetHStepSize, fmt7Info.offsetVStepSize );
			m_pLabelOffsetUnits->set_text( entry );

			UpdateResizeInformation();

			m_pAdjustmentF7Left->set_lower( 0 );
			m_pAdjustmentF7Left->set_upper( fmt7Info.maxWidth - fmt7Info.imageHStepSize );
			m_pAdjustmentF7Left->set_step_increment( fmt7Info.offsetHStepSize );
			m_pAdjustmentF7Left->set_page_increment( fmt7Info.offsetHStepSize );

			m_pAdjustmentF7Top->set_lower( 0 );
			m_pAdjustmentF7Top->set_upper( fmt7Info.maxHeight - fmt7Info.imageVStepSize );
			m_pAdjustmentF7Top->set_step_increment( fmt7Info.offsetVStepSize );
			m_pAdjustmentF7Top->set_page_increment( fmt7Info.offsetVStepSize );

			m_pAdjustmentF7Width->set_lower( fmt7Info.imageHStepSize );
			m_pAdjustmentF7Width->set_upper( fmt7Info.maxWidth );
			m_pAdjustmentF7Width->set_step_increment( fmt7Info.imageHStepSize );
			m_pAdjustmentF7Width->set_page_increment( fmt7Info.imageHStepSize );

			m_pAdjustmentF7Height->set_lower( fmt7Info.imageVStepSize );
			m_pAdjustmentF7Height->set_upper( fmt7Info.maxHeight );
			m_pAdjustmentF7Height->set_step_increment( fmt7Info.imageVStepSize );
			m_pAdjustmentF7Height->set_page_increment( fmt7Info.imageVStepSize );

			unsigned int left = 0;
			unsigned int top = 0;
			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int packetSize = 0;
			PixelFormat pixelFormat;

			bool success = GetF7ImageParametersFromCamera( selectedMode, &left, &top, &width, &height, &pixelFormat, &packetSize);
			if ( success == true )
			{
				const bool leftOk = ValidateImageLeft( left, width, fmt7Info.offsetHStepSize, fmt7Info.maxWidth );
				const bool topOk = ValidateImageTop( top, height, fmt7Info.offsetVStepSize, fmt7Info.maxHeight );
				const bool widthOk = ValidateImageWidth( left, width, fmt7Info.imageHStepSize, fmt7Info.maxWidth );
				const bool heightOk = ValidateImageHeight( top, height, fmt7Info.imageVStepSize, fmt7Info.maxHeight );

				if ( !leftOk || !topOk || !widthOk || !heightOk )
				{
					// Values don't seem valid, set it to the maximum size
					m_pAdjustmentF7Left->set_value( 0 );
					m_pAdjustmentF7Top->set_value( 0 );
					m_pAdjustmentF7Width->set_value( fmt7Info.maxWidth );
					m_pAdjustmentF7Height->set_value( fmt7Info.maxHeight );
				}
				else
				{
					// Set it to the size retrieved from the camera
					m_pAdjustmentF7Left->set_value( left );
					m_pAdjustmentF7Top->set_value( top );
					m_pAdjustmentF7Width->set_value( width );
					m_pAdjustmentF7Height->set_value( height );
				}

				// Update pixel format
				PopulatePixelFormatComboBox(fmt7Info.pixelFormatBitField, fmt7Info.vendorPixelFormatBitField);
				SetActivePixelFormatComboBox(pixelFormat);

				// Force an update of packet info
				m_pAdjustmentPacketSize->set_upper( fmt7Info.maxPacketSize );
				m_pAdjustmentPacketSize->set_lower( fmt7Info.minPacketSize );
				m_pAdjustmentPacketSize->set_value( packetSize );
				m_pAdjustmentPacketSize->set_step_increment( fmt7Info.minPacketSize );
				m_pAdjustmentPacketSize->set_page_increment( fmt7Info.minPacketSize * 10 );
				ValidatePacketSize();
			}
			else
			{
				// Set it to the maximum size possible
				m_pAdjustmentF7Left->set_value( 0 );
				m_pAdjustmentF7Top->set_value( 0 );
				m_pAdjustmentF7Width->set_value( fmt7Info.maxWidth );
				m_pAdjustmentF7Height->set_value( fmt7Info.maxHeight );
				m_pAdjustmentPacketSize->set_value( fmt7Info.maxPacketSize );

			}
			ValidateImageSize();

			// Display message if the selected mode is not supported by ladybug library
			if ( m_isLadybugCamera )
			{
				CameraInfo camInfo;
				pCamera->GetCameraInfo( &camInfo );
				bool bLadybugLibSupported = true;
				if ( IsLadybug3() )
				{
					bLadybugLibSupported =
						selectedMode == MODE_0 || selectedMode == MODE_7 ||
						selectedMode == MODE_2 || selectedMode == MODE_3 ;

				}
				else
				{
					if ( IsLadybug2() )
					{
						bLadybugLibSupported =
							selectedMode == MODE_0 || selectedMode == MODE_7;
					}
				}
				if ( !bLadybugLibSupported )
				{
					ShowMessageDialog(
							"This mode is not supported by Ladybug library.",
							"Please select another mode.");
				}
			}

			UpdateJpegInformation();
		}
		else if ( IsGEV() )
		{
			GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

			error = pCamera->SetGigEImagingMode(selectedMode);
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error setting GigE imaging mode", error );
				return;
			}

			GigEImageSettingsInfo imageInfo;
			error = pCamera->GetGigEImageSettingsInfo( &imageInfo );
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error querying GigE image settings information", error );
				return;
			}

			GigEImageSettings imageSettings;
			error = pCamera->GetGigEImageSettings( &imageSettings );
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error querying GigE image settings", error );
				return;
			}

			// Repopulate pixel format box
			PopulatePixelFormatComboBox(imageInfo.pixelFormatBitField, imageInfo.vendorPixelFormatBitField);

			// Get lowest pixel format and set it as the active selection
			SetActivePixelFormatComboBox( imageSettings.pixelFormat );

			// Get the new binning values
			unsigned int horzBinning = 0;
			unsigned int vertBinning = 0;
			error = pCamera->GetGigEImageBinningSettings(&horzBinning, &vertBinning);
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error querying GigE binning settings", error );
				return;
			}

			// Update the spin buttons to the right binning value
			if (m_pAdjustmentGigEHorzBinning->get_value() != horzBinning)
			{
				m_pAdjustmentGigEHorzBinning->set_value(horzBinning);
			}

			if (m_pAdjustmentGigEVertBinning->get_value() != vertBinning)
			{
				m_pAdjustmentGigEVertBinning->set_value(vertBinning);
			}

			// Repopulate image size and packet size boxes
			UpdateF7Info( selectedMode );
			ValidateImageSize();

			UpdateGigEImageInfo();

			UpdateJpegInformation();

			OnApply();
		}

	}

	void Format7Page::OnComboBoxPixelFormatChanged()
	{
		if ( IsIIDC() == true )
		{
			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

			// Get the values from the screen
			Format7ImageSettings imageSettings;
			GetF7InfoFromPage( &imageSettings );

			if ( imageSettings.mode == NUM_MODES ||
					imageSettings.width == 0 ||
					imageSettings.height == 0 ||
					imageSettings.pixelFormat == NUM_PIXEL_FORMATS )
			{
				return;
			}

			// Validate the values received
			bool supported = false;
			Format7PacketInfo packetInfo;
			Error error = pCamera->ValidateFormat7Settings( &imageSettings, &supported, &packetInfo );
			if ( error != PGRERROR_OK )
			{
				//return;
			}

			// Update the packet info
			if ( supported == true )
			{
				UpdateF7PacketInfo( imageSettings, packetInfo );

				m_pBtnApply->set_sensitive(true);
			}
			else
			{
				m_pBtnApply->set_sensitive(false);
			}

			UpdateJpegInformation();
		}
		else if ( IsGEV() == true )
		{
			m_pBtnApply->set_sensitive(true);

			UpdateJpegInformation();
		}
	}

	void Format7Page::OnSpinImageSizeChanged()
	{
		ValidateImageSize();
		OnComboBoxPixelFormatChanged();
		ValidatePacketSize();
	}

	void Format7Page::OnCenterROI()
	{
		if ( IsIIDC() == true )
		{
			Format7ImageSettings settings;
			GetF7InfoFromPage( &settings );

			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

			Error error;
			Format7Info fmt7Info;
			fmt7Info.mode = settings.mode;
			bool supported;
			error = pCamera->GetFormat7Info( &fmt7Info, &supported );

			unsigned int left = (fmt7Info.maxWidth - settings.width) / 2;
			while (left % fmt7Info.offsetHStepSize != 0)
			{
				left++;
			}

			if ((left + settings.width) <= fmt7Info.maxWidth)
			{
				settings.offsetX = left;
				m_pAdjustmentF7Left->set_value((double)left);
			}

			unsigned int top = (fmt7Info.maxHeight - settings.height) / 2;
			while (top % fmt7Info.offsetVStepSize != 0)
			{
				top++;
			}

			if ((top + settings.height) <= fmt7Info.maxHeight)
			{
				settings.offsetY = top;
				m_pAdjustmentF7Top->set_value((double)top);
			}

			// Update the drawing area with the new values
			m_pDrawingArea->UpdateSettings( &fmt7Info, &settings );
		}
		else if ( IsGEV() == true )
		{
			GigEImageSettings settings;
			GetGigEImageInfoFromPage( &settings );

			GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

			GigEImageSettingsInfo imageSettingsInfo;
			Error error = pCamera->GetGigEImageSettingsInfo( &imageSettingsInfo );

			unsigned int left = (imageSettingsInfo.maxWidth - settings.width) / 2;
			while(left % imageSettingsInfo.offsetHStepSize != 0)
			{
				left++;
			}

			if((left + settings.width) <= imageSettingsInfo.maxWidth)
			{
				settings.offsetX = left;
				m_pAdjustmentF7Left->set_value((double)left);
			}

			unsigned int top = (imageSettingsInfo.maxHeight - settings.height) / 2;
			while(top % imageSettingsInfo.offsetVStepSize != 0)
			{
				top++;
			}

			if((top + settings.height) <= imageSettingsInfo.maxHeight)
			{
				settings.offsetY = top;
				m_pAdjustmentF7Top->set_value((double)top);
			}

			// Update the drawing area with the new values
			m_pDrawingArea->UpdateSettings( &imageSettingsInfo, &settings );
		}
	}

	void Format7Page::OnHScaleJpegQualityChanged()
	{
		const unsigned int jpegReg = 0x1E80;
		unsigned int jpegRegVal = 0;
		Error error = m_pCamera->ReadRegister(jpegReg, &jpegRegVal);
		if (error != PGRERROR_OK)
		{
			// TODO: Error
			return;
		}

		jpegRegVal &= 0xFFFFFF00;

		const unsigned int newQuality = (unsigned int)(m_pAdjustmentJpegQuality->get_value());
		jpegRegVal += newQuality;

		error = m_pCamera->WriteRegister(jpegReg, jpegRegVal);
		if (error != PGRERROR_OK)
		{
			// TODO: Error
			return;
		}
	}

	bool Format7Page::OnSpinBinningValueFocusLost( GdkEventFocus* /*event*/ )
	{
		OnSpinBinningValueChanged();

		return false;
	}

	void Format7Page::OnSpinBinningValueChanged()
	{
		if ( IsIIDC() == true )
		{
			return;
		}

		GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

		// Get the binning values from the GUI
		const unsigned int horzBinningVal = (unsigned int)m_pAdjustmentGigEHorzBinning->get_value();
		const unsigned int vertBinningVal = (unsigned int)m_pAdjustmentGigEVertBinning->get_value();

		// Get the binning values from the camera
		unsigned int camHorzBinningVal = 0;
		unsigned int camVertBinningVal = 0;
		Error error = pCamera->GetGigEImageBinningSettings(&camHorzBinningVal, &camVertBinningVal);
		if ( error != PGRERROR_OK )
		{
			// Error
			ShowErrorMessageDialog("Error getting current binning settings from camera.", error);
			return;
		}

		if ( camHorzBinningVal == horzBinningVal && camVertBinningVal == vertBinningVal )
		{
			// The camera is already has the correct binning values
			// Set the spin buttons to the right colour
			Gdk::Color color_green = GetColorAccentGreen();
			m_pSpinGigEHorzBinning->modify_base(Gtk::STATE_NORMAL, color_green);
			m_pSpinGigEVertBinning->modify_base(Gtk::STATE_NORMAL, color_green);
			m_pBtnApply->set_sensitive(true);

			return;
		}

		error = pCamera->SetGigEImageBinningSettings(horzBinningVal, vertBinningVal);
		if ( error != PGRERROR_OK )
		{
			Gdk::Color color_red = GetColorAccentRed();
			m_pSpinGigEHorzBinning->modify_base(Gtk::STATE_NORMAL, color_red);
			m_pSpinGigEVertBinning->modify_base(Gtk::STATE_NORMAL, color_red);
			m_pBtnApply->set_sensitive(false);
			return;
		}
		else
		{
			Gdk::Color color_green = GetColorAccentGreen();
			m_pSpinGigEHorzBinning->modify_base(Gtk::STATE_NORMAL, color_green);
			m_pSpinGigEVertBinning->modify_base(Gtk::STATE_NORMAL, color_green);
			m_pBtnApply->set_sensitive(true);
		}

		// Get the new imaging mode
		Mode mode;
		error = pCamera->GetGigEImagingMode(&mode);
		if ( error != PGRERROR_OK )
		{
			//return;
		}

		SetActiveModeComboBox(mode);

		// Update the GUI with the new settings
		UpdateGigEImageInfo();

		OnApply();
	}

	bool Format7Page::OnSpinImageSizeFocusLost( GdkEventFocus* /*event*/ )
	{
		ValidateImageSize();

		OnComboBoxPixelFormatChanged();

		ValidatePacketSize();

		return false;
	}

	bool Format7Page::OnSpinF7PacketSizeFocusLost( GdkEventFocus* /*event*/ )
	{
		return false;
	}

	void Format7Page::OnF7PacketSizeChanged()
	{
		unsigned int newPacketSize = static_cast<unsigned int>(m_pAdjustmentPacketSize->get_value());

		unsigned int minPacketSize = strtoul(m_pLabelMinPacketSize->get_text().c_str(), NULL, 10 );

		// Make sure that the value is a multiple of the minimum packet size
		if( minPacketSize == 0 )
		{
			minPacketSize = 8;
		}

		if ( newPacketSize % minPacketSize != 0 )
		{
			newPacketSize -= newPacketSize % minPacketSize;
			m_pAdjustmentPacketSize->set_value( newPacketSize );
		}
		ValidatePacketSize();
	}

	void Format7Page::OnApply()
	{
		if ( IsIIDC() == true )
		{
			ApplyF7Settings();
		}
		else if ( IsGEV() == true )
		{
			ApplyGigESettings();
		}

		UpdateResizeInformation();
		UpdateJpegInformation();

		// Inform DCAM formats page to switch to Format 7
		m_signal_format7_applied();
	}

	void Format7Page::ApplyF7Settings()
	{
		Error error;

		// Save the current settings
		VideoMode currVideoMode;
		FrameRate currFrameRate;
		Format7ImageSettings currFmt7Settings;
		unsigned int currPacketSize = 0;

		Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

		error = pCamera->GetVideoModeAndFrameRate( &currVideoMode, &currFrameRate );
		if ( error != PGRERROR_OK )
		{
			// Error
			ShowErrorMessageDialog( "Error getting current video mode and frame rate", error );
		}

		if ( currVideoMode == VIDEOMODE_FORMAT7 )
		{
			// Get the current Format 7 settings
			float percentage; // Don't need to keep this
			error = pCamera->GetFormat7Configuration( &currFmt7Settings, &currPacketSize, &percentage );
			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error getting current Format7 configuration", error );
				return;
			}
		}

		// Get the image settings from the page
		Format7ImageSettings newFmt7Settings;
		GetF7InfoFromPage( &newFmt7Settings );

		// Stop the camera
		error = pCamera->StopCapture();

		bool restartCamera = false;
		if ( error != PGRERROR_OK ) //&& error != PGRERROR_NOT_STARTED )
		{
			// Error
		}

		if ( error == PGRERROR_OK )
		{
			// The camera was actively capturing images, indicate that
			// it needs to be restarted
			restartCamera = true;
		}

		// Set the Format7 settings
		error = pCamera->SetFormat7Configuration(
				&newFmt7Settings,
				static_cast<unsigned int>(m_pAdjustmentPacketSize->get_value()) );
		if ( error != PGRERROR_OK )
		{
			ShowMessageDialog(
					"Error setting Format7",
					"There was an error setting the Format7 settings, attempting to revert to previous mode...",
					Gtk::MESSAGE_ERROR );

			if (currVideoMode == VIDEOMODE_FORMAT7)
			{
				// The camera was in Format7, so set it back to Format7
				error = pCamera->SetFormat7Configuration( &currFmt7Settings, currPacketSize );
			}
			else
			{
				// Set the camera back to original DCAM video mode and frame rate
				error = pCamera->SetVideoModeAndFrameRate( currVideoMode, currFrameRate );
			}

			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error reverting to previous mode", error );
			}
		}

		// Settings were applied, or reverted to previous mode
		// Either way, the camera should be able to be restarted successfully
		if ( restartCamera == true )
		{
			// Restart the camera if it was running beforehand.
			error = pCamera->StartCapture();
			if ( error != PGRERROR_OK )
			{
				ShowMessageDialog(
						"Error restarting camera",
						"There was an error restarting the camera",
						Gtk::MESSAGE_ERROR );
			}
		}
	}

	void Format7Page::ApplyGigESettings()
	{
		Error error;
		GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

		// Cache the current settings
		GigEImageSettings currImageSettings;
		error = pCamera->GetGigEImageSettings( &currImageSettings );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error getting current image configuration", error );
			return;
		}

		GigEImageSettings newImageSettings;
		GetGigEImageInfoFromPage( &newImageSettings );

		// Get the packet size from the GUI
		const unsigned int packetSize = static_cast<unsigned int>(m_pAdjustmentGigEPacketSize->get_value());

		// Get the packet delay from the GUI
		const unsigned int packetDelay = static_cast<unsigned int>(m_pAdjustmentGigEPacketDelay->get_value());

		// Get the binning values from the GUI
		const unsigned int horzBinning = static_cast<unsigned int>(m_pAdjustmentGigEHorzBinning->get_value());
		const unsigned int vertBinning = static_cast<unsigned int>(m_pAdjustmentGigEVertBinning->get_value());

		// Perform some sanity checking on the binning values
		const bool isValidBinningCombo = (horzBinning == vertBinning) &&
			((horzBinning == 1 && vertBinning == 1) ||
			 (horzBinning == 2 && vertBinning == 2) ||
			 (horzBinning == 4 && vertBinning == 4));

		if ( !isValidBinningCombo )
		{
			ShowErrorMessageDialog(
					"Invalid binning combination",
					"The combination of binning values is invalid." );
			return;
		}

		// Stop the camera
		error = pCamera->StopCapture();

		bool restartCamera = false;
		if ( error != PGRERROR_OK ) //&& error != PGRERROR_NOT_STARTED )
		{
			// Error
		}

		if ( error == PGRERROR_OK )
		{
			// The camera was actively capturing images, indicate that
			// it needs to be restarted
			restartCamera = true;
		}

		// Get the current binning settings and decide if there is a need
		// to write the binning settings to the camera
		unsigned int currHorzBinning = 0;
		unsigned int currVertBinning = 0;
		error = pCamera->GetGigEImageBinningSettings( &currHorzBinning, &currVertBinning );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error getting current image binning configuration", error );
			return;
		}

		if ( currHorzBinning != horzBinning || currVertBinning != vertBinning )
		{
			error = pCamera->SetGigEImageBinningSettings( horzBinning, vertBinning );
			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error setting image binning configuration", error );
				return;
			}
		}

		error = pCamera->SetGigEImageSettings( &newImageSettings );
		if ( error != PGRERROR_OK )
		{
			ShowMessageDialog(
					"Error setting GigE image settings",
					"There was an error setting the image settings, attempting to revert to previous settings...",
					Gtk::MESSAGE_ERROR );

			// Set the camera back to original state
			pCamera->SetGigEImageSettings( &currImageSettings );

			return;
		}

		// Set the packet size and delay to the camera
		GigEProperty packetSizeProp;
		packetSizeProp.propType = PACKET_SIZE;
		packetSizeProp.value = packetSize;
		error = pCamera->SetGigEProperty(&packetSizeProp);
		if ( error != PGRERROR_OK )
		{
			ShowMessageDialog(
					"Error setting GigE packet size",
					"There was an error setting the GigE packet size, attempting to revert to previous settings...",
					Gtk::MESSAGE_ERROR );

			// Set the camera back to original state
			pCamera->SetGigEImageSettings( &currImageSettings );

			return;
		}

		GigEProperty packetDelayProp;
		packetDelayProp.propType = PACKET_DELAY;
		packetDelayProp.value = packetDelay;
		error = pCamera->SetGigEProperty(&packetDelayProp);
		if ( error != PGRERROR_OK )
		{
			ShowMessageDialog(
					"Error setting GigE packet delay",
					"There was an error setting the GigE packet size, attempting to revert to previous settings...",
					Gtk::MESSAGE_ERROR );

			// Set the camera back to original state
			pCamera->SetGigEImageSettings( &currImageSettings );

			return;
		}

		// Settings were applied successfully
		if ( restartCamera == true )
		{
			// Restart the camera if it was running beforehand.
			error = pCamera->StartCapture();
			if ( error != PGRERROR_OK )
			{
				ShowMessageDialog(
						"Error restarting camera",
						"There was an error restarting the camera",
						Gtk::MESSAGE_ERROR );

				// Set the camera back to original state
				error = pCamera->SetGigEImageSettings( &currImageSettings );
				if ( error != PGRERROR_OK )
				{
					ShowErrorMessageDialog( "Error setting image settings", error );
				}

				return;
			}
		}
	}

	void Format7Page::OnImageSizeChanged(
			unsigned int left, unsigned int top, unsigned int width, unsigned int height, bool isButtonReleased )
	{
		const unsigned int currWidth = static_cast<unsigned int>(m_pAdjustmentF7Width->get_value());
		const unsigned int currHeight = static_cast<unsigned int>(m_pAdjustmentF7Height->get_value());

		bool offsetOnly = false;
		if ( currWidth == width && currHeight == height )
		{
			offsetOnly = true;
		}

		m_pAdjustmentF7Left->set_value( left );
		m_pAdjustmentF7Top->set_value( top );
		m_pAdjustmentF7Width->set_value( width );
		m_pAdjustmentF7Height->set_value( height );

		if(!isButtonReleased){
			return;
		}
		const bool settingsValid = ValidateImageSize();
		if ( settingsValid == true && offsetOnly == true )
		{

			// Get the current mode from the video mode register
			unsigned int currModeRegVal = 0;
			Error error = m_pCamera->ReadRegister(0x604, &currModeRegVal);
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error reading current video mode", error );
			}

			const unsigned int currModeVal =
				((currModeRegVal & 0xE0000000) >> 29) +
				(((currModeRegVal & 0x02000000) >> 25) << 4) +
				(((currModeRegVal & 0x01000000) >> 24) << 3);

			const Mode currMode = static_cast<Mode>(currModeVal);

			// Get the quadlet offset for the mode
			const unsigned int modeOffsetInqReg = 0x2E0 + (0x4 * static_cast<int>(currMode));
			unsigned int modeOffsetInqRegVal = 0;
			error = m_pCamera->ReadRegister(modeOffsetInqReg, &modeOffsetInqRegVal);
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error reading mode offset register", error );
			}

			// Write to the offset registers
			const unsigned int regOffset = ((modeOffsetInqRegVal * 4) & 0x000FFFFF) + 0x8;
			const unsigned int roiOffsetVal = (left << 16) | (top & 0xFFFF);
			error = m_pCamera->WriteRegister( regOffset, roiOffsetVal );
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error writing ROI offset register", error );
			}
		}

		OnComboBoxPixelFormatChanged();
		ValidatePacketSize();
		if(!m_sigctlF7Left.connected()){
			m_sigctlF7Left = m_pAdjustmentF7Left->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );
		}
		if(!m_sigctlF7Top.connected()){
			m_sigctlF7Top = m_pAdjustmentF7Top->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );
		}
		if(!m_sigctlF7Width.connected()){
			m_sigctlF7Width = m_pAdjustmentF7Width->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );
		}
		if(!m_sigctlF7Height.connected()){
			m_sigctlF7Height = m_pAdjustmentF7Height->signal_value_changed().connect( sigc::mem_fun( *this, &Format7Page::OnSpinImageSizeChanged ), false );
		}
	}

	void Format7Page::PopulateModeComboBox()
	{
		m_refListStoreModes->clear();

		if ( IsIIDC() == true )
		{
			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

			for ( int i = 0; i < NUM_MODES; i++ )
			{
				bool supported = false;
				Format7Info fmt7Info;
				fmt7Info.mode = (Mode)i;
				Error error = pCamera->GetFormat7Info( &fmt7Info, &supported );
				if ( error != PGRERROR_OK )
				{
					ShowErrorMessageDialog( "Error querying Format7 information", error );
					continue;
				}

				if ( supported == true )
				{
					char mode[16];
					sprintf( mode, "%d", i );

					Gtk::TreeModel::Row row = *(m_refListStoreModes->append());

					row[m_modeColumns.m_colModeStr] = mode;
					row[m_modeColumns.m_colMode] = (Mode)i;
				}
			}
		}
		else if ( IsGEV() == true )
		{
			GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

			for ( int i = 0; i < NUM_MODES; i++ )
			{
				bool supported = false;
				Mode currMode = (Mode)i;
				Error error = pCamera->QueryGigEImagingMode(currMode, &supported);
				if ( error != PGRERROR_OK )
				{
					ShowErrorMessageDialog( "Error querying GigE imaging mode availability", error );
					continue;
				}

				if ( supported == true )
				{
					char mode[16];
					sprintf( mode, "%d", i );

					Gtk::TreeModel::Row row = *(m_refListStoreModes->append());

					row[m_modeColumns.m_colModeStr] = mode;
					row[m_modeColumns.m_colMode] = (Mode)i;
				}
			}
		}

		// Hide the mode column
		m_pComboBoxMode->clear();
		m_pComboBoxMode->pack_start( m_modeColumns.m_colModeStr );
	}

	void Format7Page::PopulatePixelFormatComboBox(
			unsigned int pixelFormats, unsigned int vendorPixelFormats )
	{
		m_refListStorePixelFormats->clear();

		if ( (pixelFormats & PIXEL_FORMAT_MONO8) != 0 )
		{
			AddToPixelFormatComboBox( "Mono 8", PIXEL_FORMAT_MONO8 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_MONO12) != 0 )
		{
			AddToPixelFormatComboBox( "Mono 12", PIXEL_FORMAT_MONO12 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_MONO16) != 0 )
		{
			AddToPixelFormatComboBox( "Mono 16", PIXEL_FORMAT_MONO16 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_RAW8) != 0 )
		{
			AddToPixelFormatComboBox( "Raw 8", PIXEL_FORMAT_RAW8 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_RAW12) != 0 )
		{
			AddToPixelFormatComboBox( "Raw 12", PIXEL_FORMAT_RAW12 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_RAW16) != 0 )
		{
			AddToPixelFormatComboBox( "Raw 16", PIXEL_FORMAT_RAW16 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_411YUV8) != 0 )
		{
			AddToPixelFormatComboBox( "YUV 411", PIXEL_FORMAT_411YUV8 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_422YUV8) != 0 )
		{
			AddToPixelFormatComboBox( "YUV 422", PIXEL_FORMAT_422YUV8 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_444YUV8) != 0 )
		{
			AddToPixelFormatComboBox( "YUV 444", PIXEL_FORMAT_444YUV8 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_RGB8) != 0 )
		{
			AddToPixelFormatComboBox( "RGB 8", PIXEL_FORMAT_RGB8 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_RGB16) != 0 )
		{
			AddToPixelFormatComboBox( "RGB 16", PIXEL_FORMAT_RGB16 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_S_MONO16) != 0 )
		{
			AddToPixelFormatComboBox( "Signed Mono 16", PIXEL_FORMAT_S_MONO16 );
		}

		if ( (pixelFormats & PIXEL_FORMAT_S_RGB16) != 0 )
		{
			AddToPixelFormatComboBox( "Signed RGB 16", PIXEL_FORMAT_S_RGB16 );
		}

		/*
		   if ( pixelFormats & PIXEL_FORMAT_BGR )
		   {
		   AddToPixelFormatComboBox( "BGR", PIXEL_FORMAT_BGR );
		   }

		   if ( pixelFormats & PIXEL_FORMAT_BGRU )
		   {
		   AddToPixelFormatComboBox( "BGRU", PIXEL_FORMAT_BGRU );
		   }
		   */

		// Check vendor unique pixel formats
		if (vendorPixelFormats & PIXEL_FORMAT_422YUV8_JPEG)
		{
			AddToPixelFormatComboBox( "YUV 422 (JPEG)", PIXEL_FORMAT_422YUV8_JPEG );
		}

		// Hide the mode column
		m_pComboBoxPixelFormat->clear();
		m_pComboBoxPixelFormat->pack_start( m_pixelFormatColumns.m_colPixelFormatStr );
	}

	void Format7Page::SetActiveModeComboBox( Mode activeMode )
	{
		if ( m_refListStoreModes->children().size() == 0 )
		{
			return;
		}

		// Find the selected mode in the list store and set it
		Gtk::TreeModel::iterator iter;
		Gtk::TreeModel::Row row;
		bool found = false;

		for ( iter = m_refListStoreModes->children().begin();
				iter != m_refListStoreModes->children().end();
				iter++ )
		{
			row = *iter;
			if ( row[m_modeColumns.m_colMode] == activeMode )
			{
				found = true;
				break;
			}
		}

		if ( found == true )
		{
			m_pComboBoxMode->set_active(iter);
		}
		else
		{
			m_pComboBoxMode->set_active(0);
		}
	}

	void Format7Page::SetActivePixelFormatComboBox( PixelFormat activePixelFormat )
	{
		if ( m_refListStorePixelFormats->children().size() == 0 )
		{
			return;
		}

		// Find the selected pixel format in the list store and set it
		Gtk::TreeModel::iterator iter;
		Gtk::TreeModel::Row row;
		bool found = false;

		for ( iter = m_refListStorePixelFormats->children().begin();
				iter != m_refListStorePixelFormats->children().end();
				iter++ )
		{
			row = *iter;
			if ( row[m_pixelFormatColumns.m_colPixelFormat] == activePixelFormat )
			{
				found = true;
				break;
			}
		}

		if ( found == true )
		{
			m_pComboBoxPixelFormat->set_active(iter);
		}
		else
		{
			m_pComboBoxPixelFormat->set_active(0);
		}
	}

	Mode Format7Page::GetActiveModeComboBox()
	{
		// Get the active row
		Gtk::TreeModel::iterator iter = m_pComboBoxMode->get_active();
		if ( iter == 0 )
		{
			return NUM_MODES;
		}

		Gtk::TreeModel::Row row = *iter;
		Mode selectedMode = row[m_modeColumns.m_colMode];

		return selectedMode;
	}

	PixelFormat Format7Page::GetActivePixelFormatComboBox()
	{
		// Get the active row
		Gtk::TreeModel::iterator iter = m_pComboBoxPixelFormat->get_active();
		if ( iter == 0 )
		{
			return NUM_PIXEL_FORMATS;
		}

		Gtk::TreeModel::Row row = *iter;
		PixelFormat selectedPixelFormat = row[m_pixelFormatColumns.m_colPixelFormat];

		return selectedPixelFormat;
	}

	void Format7Page::AddToPixelFormatComboBox( Glib::ustring pixelFormat, PixelFormat pixFmt )
	{
		Gtk::TreeModel::Row row = *(m_refListStorePixelFormats->append());
		row[m_pixelFormatColumns.m_colPixelFormatStr] = pixelFormat;
		row[m_pixelFormatColumns.m_colPixelFormat] = pixFmt;
	}

	void Format7Page::UpdateF7Info( Mode mode )
	{
		if ( IsGEV() == true )
		{
			UpdateGigEImageInfo();
			return;
		}

		Error error;
		char entry[128];

		Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

		bool supported;
		Format7Info fmt7Info;
		fmt7Info.pixelFormatBitField = 0;
		fmt7Info.mode = mode;
		error = pCamera->GetFormat7Info( &fmt7Info, &supported );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error querying Format7 information", error );
		}

		// Common labels
		sprintf( entry, "%u x %u", fmt7Info.maxWidth, fmt7Info.maxHeight );
		m_pLabelMaxImageSize->set_text( entry );

		sprintf( entry, "%u(H), %u(V)", fmt7Info.imageHStepSize, fmt7Info.imageVStepSize );
		m_pLabelImageSizeUnits->set_text( entry );

		sprintf( entry, "%u(H), %u(V)", fmt7Info.offsetHStepSize, fmt7Info.offsetVStepSize );
		m_pLabelOffsetUnits->set_text( entry );

		UpdateResizeInformation();

		m_pAdjustmentF7Left->set_lower( 0 );
		m_pAdjustmentF7Left->set_upper( fmt7Info.maxWidth - fmt7Info.imageHStepSize );
		m_pAdjustmentF7Left->set_step_increment( fmt7Info.offsetHStepSize );
		m_pAdjustmentF7Left->set_page_increment( fmt7Info.offsetHStepSize );

		m_pAdjustmentF7Top->set_lower( 0 );
		m_pAdjustmentF7Top->set_upper( fmt7Info.maxHeight - fmt7Info.imageVStepSize );
		m_pAdjustmentF7Top->set_step_increment( fmt7Info.offsetVStepSize );
		m_pAdjustmentF7Top->set_page_increment( fmt7Info.offsetVStepSize );

		m_pAdjustmentF7Width->set_lower( fmt7Info.imageHStepSize );
		m_pAdjustmentF7Width->set_upper( fmt7Info.maxWidth );
		m_pAdjustmentF7Width->set_step_increment( fmt7Info.imageHStepSize );
		m_pAdjustmentF7Width->set_page_increment( fmt7Info.imageHStepSize );

		m_pAdjustmentF7Height->set_lower( fmt7Info.imageVStepSize );
		m_pAdjustmentF7Height->set_upper( fmt7Info.maxHeight );
		m_pAdjustmentF7Height->set_step_increment( fmt7Info.imageVStepSize );
		m_pAdjustmentF7Height->set_page_increment( fmt7Info.imageVStepSize );

		if ( IsCurrentlyInFormat7() == true )
		{
			Format7ImageSettings imageSettings;
			unsigned int packetSize;
			float speed;

			error = pCamera->GetFormat7Configuration( &imageSettings, &packetSize, &speed );
			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error getting Format7 configuration", error );
			}

			m_pAdjustmentF7Left->set_value( imageSettings.offsetX );
			m_pAdjustmentF7Top->set_value( imageSettings.offsetY );
			m_pAdjustmentF7Width->set_value( imageSettings.width );
			m_pAdjustmentF7Height->set_value( imageSettings.height );
		}
		else
		{
			unsigned int left = 0;
			unsigned int top = 0;
			unsigned int width = 0;
			unsigned int height = 0;

			bool success = GetF7ImageParametersFromCamera( mode, &left, &top, &width, &height );
			if ( success == true )
			{
				const bool leftOk = ValidateImageLeft( left, width, fmt7Info.offsetHStepSize, fmt7Info.maxWidth );
				const bool topOk = ValidateImageTop( top, height, fmt7Info.offsetVStepSize, fmt7Info.maxHeight );
				const bool widthOk = ValidateImageWidth( left, width, fmt7Info.imageHStepSize, fmt7Info.maxWidth );
				const bool heightOk = ValidateImageHeight( top, height, fmt7Info.imageVStepSize, fmt7Info.maxHeight );

				if ( !leftOk || !topOk || !widthOk || !heightOk )
				{
					// Values don't seem valid, set it to the maximum size
					m_pAdjustmentF7Left->set_value( 0 );
					m_pAdjustmentF7Top->set_value( 0 );
					m_pAdjustmentF7Width->set_value( fmt7Info.maxWidth );
					m_pAdjustmentF7Height->set_value( fmt7Info.maxHeight );
				}
				else
				{
					// Set it to the size retrieved from the camera
					m_pAdjustmentF7Left->set_value( left );
					m_pAdjustmentF7Top->set_value( top );
					m_pAdjustmentF7Width->set_value( width );
					m_pAdjustmentF7Height->set_value( height );
				}
			}
			else
			{
				// Set it to the maximum size possible
				m_pAdjustmentF7Left->set_value( 0 );
				m_pAdjustmentF7Top->set_value( 0 );
				m_pAdjustmentF7Width->set_value( fmt7Info.maxWidth );
				m_pAdjustmentF7Height->set_value( fmt7Info.maxHeight );
			}
		}

		// Force an update of packet info
		OnComboBoxPixelFormatChanged();

		ValidateImageSize();
	}

	void Format7Page::UpdateGigEImageInfo()
	{
		Error error;
		char entry[128];

		GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

		GigEImageSettingsInfo imageSettingsInfo;
		error = pCamera->GetGigEImageSettingsInfo( &imageSettingsInfo );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error querying GigE image settings information", error );
		}

		// Common labels
		sprintf( entry, "%u x %u", imageSettingsInfo.maxWidth, imageSettingsInfo.maxHeight );
		m_pLabelMaxImageSize->set_text( entry );

		sprintf( entry, "%u(H), %u(V)", imageSettingsInfo.imageHStepSize, imageSettingsInfo.imageVStepSize );
		m_pLabelImageSizeUnits->set_text( entry );

		sprintf( entry, "%u(H), %u(V)", imageSettingsInfo.offsetHStepSize, imageSettingsInfo.offsetVStepSize );
		m_pLabelOffsetUnits->set_text( entry );

		UpdateResizeInformation();

		m_pAdjustmentF7Left->set_lower( 0 );
		m_pAdjustmentF7Left->set_upper( imageSettingsInfo.maxWidth - imageSettingsInfo.imageHStepSize );
		m_pAdjustmentF7Left->set_step_increment( imageSettingsInfo.offsetHStepSize );
		m_pAdjustmentF7Left->set_page_increment( imageSettingsInfo.offsetHStepSize );

		m_pAdjustmentF7Top->set_lower( 0 );
		m_pAdjustmentF7Top->set_upper( imageSettingsInfo.maxHeight - imageSettingsInfo.imageVStepSize );
		m_pAdjustmentF7Top->set_step_increment( imageSettingsInfo.offsetVStepSize );
		m_pAdjustmentF7Top->set_page_increment( imageSettingsInfo.offsetVStepSize );

		m_pAdjustmentF7Width->set_lower( imageSettingsInfo.imageHStepSize );
		m_pAdjustmentF7Width->set_upper( imageSettingsInfo.maxWidth );
		m_pAdjustmentF7Width->set_step_increment( imageSettingsInfo.imageHStepSize );
		m_pAdjustmentF7Width->set_page_increment( imageSettingsInfo.imageHStepSize );

		m_pAdjustmentF7Height->set_lower( imageSettingsInfo.imageVStepSize );
		m_pAdjustmentF7Height->set_upper( imageSettingsInfo.maxHeight );
		m_pAdjustmentF7Height->set_step_increment( imageSettingsInfo.imageVStepSize );
		m_pAdjustmentF7Height->set_page_increment( imageSettingsInfo.imageVStepSize );

		GigEImageSettings imageSettings;
		error = pCamera->GetGigEImageSettings( &imageSettings );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error getting GigE image settings configuration", error );
		}

		m_pAdjustmentF7Left->set_value( imageSettings.offsetX );
		m_pAdjustmentF7Top->set_value( imageSettings.offsetY );
		m_pAdjustmentF7Width->set_value( imageSettings.width );
		m_pAdjustmentF7Height->set_value( imageSettings.height );

		ValidateImageSize();
	}

	void Format7Page::UpdateF7PacketInfo( Format7ImageSettings imageSettings, Format7PacketInfo info )
	{
		if ( IsIIDC() != true )
		{
			return;
		}

		unsigned int configPacketSize = 0;
		float speed = 0.0;

		unsigned int currPacketSize = info.recommendedBytesPerPacket;
		if ( IsCurrentlyInFormat7() == true )
		{
			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);
			Format7ImageSettings camImageSettings;
			Error error = pCamera->GetFormat7Configuration( &camImageSettings, &configPacketSize, &speed );
			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error getting current Format7 configuration", error );
			}

			if ( imageSettings.pixelFormat == camImageSettings.pixelFormat &&
					imageSettings.mode == camImageSettings.mode )
			{
				currPacketSize =
					(configPacketSize < info.maxBytesPerPacket)?configPacketSize:info.maxBytesPerPacket;
			}
			else
			{
				currPacketSize = info.maxBytesPerPacket;
			}
		}

		char entry[128];
		sprintf( entry, "%u", info.unitBytesPerPacket );
		m_pLabelMinPacketSize->set_text( entry );

		sprintf( entry, "%u", info.maxBytesPerPacket );
		m_pLabelMaxPacketSize->set_text( entry );

		m_pAdjustmentPacketSize->set_upper( info.maxBytesPerPacket );
		m_pAdjustmentPacketSize->set_lower( info.unitBytesPerPacket );
		m_pAdjustmentPacketSize->set_value( currPacketSize );
		m_pAdjustmentPacketSize->set_step_increment( info.unitBytesPerPacket );
		m_pAdjustmentPacketSize->set_page_increment( info.unitBytesPerPacket * 10 );
	}

	void Format7Page::UpdateGigEPacketInfo()
	{
		if ( IsIIDC() == true )
		{
			return;
		}

		GigECamera* pGigECamera = dynamic_cast<GigECamera*>(m_pCamera);
		GigEProperty packetSize;
		packetSize.propType = PACKET_SIZE;

		Error error = pGigECamera->GetGigEProperty(&packetSize);
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error getting current packet size", error );
			return;
		}

		m_pAdjustmentGigEPacketSize->set_value(packetSize.value);
	}

	void Format7Page::UpdateGigEPacketDelay()
	{
		if ( IsIIDC() == true )
		{
			return;
		}

		GigECamera* pGigECamera = dynamic_cast<GigECamera*>(m_pCamera);
		GigEProperty packetDelay;
		packetDelay.propType = PACKET_DELAY;

		Error error = pGigECamera->GetGigEProperty(&packetDelay);
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error getting current packet delay", error );
			return;
		}

		m_pAdjustmentGigEPacketDelay->set_value(packetDelay.value);
	}

	void Format7Page::UpdateJpegInformation()
	{
		const unsigned int jpegReg = 0x1E80;
		unsigned int jpegRegVal = 0;
		Error error = m_pCamera->ReadRegister(jpegReg, &jpegRegVal);
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error reading JPEG status", error );
			return;
		}

		if (jpegRegVal >> 31 == 0)
		{
			m_pLabelJpegCompressionStatus->set_text("Compression: Not available");
			m_pHscaleJpegQuality->set_sensitive(false);
		}

		char compressionStatus[128];
		sprintf(
				compressionStatus,
				"Compression: %s",
				((jpegRegVal >> 29) & 0x1) != 0 ? "On" : "Off" );

		m_pLabelJpegCompressionStatus->set_text(compressionStatus);
		m_pHscaleJpegQuality->set_sensitive(true);

		const unsigned int jpegQuality = jpegRegVal & 0xFF;
		m_pAdjustmentJpegQuality->set_value(jpegQuality);
	}

	void Format7Page::UpdateResizeInformation()
	{
		unsigned int resizeRegVal = 0;
		Error error = m_pCamera->ReadRegister(0x1AC8, &resizeRegVal);
		if (error != PGRERROR_OK)
		{
			m_pLabelResizeInformation->set_label("");
			return;
		}

		if ((resizeRegVal >> 31) != 1)
		{
			m_pLabelResizeInformation->set_label("");
			return;
		}

		// Check to see what is enabled
		const bool bPreVert = (resizeRegVal & (0x1 << 7)) != 0;
		const bool bPreHorz = (resizeRegVal & (0x1 << 6)) != 0;
		const bool bPostVert = (resizeRegVal & (0x1 << 5)) != 0;
		const bool bPostHorz = (resizeRegVal & (0x1 << 4)) != 0;

		const bool bStdVert = (resizeRegVal & (0x1 << 3)) != 0;
		const bool bStdHorz = (resizeRegVal & (0x1 << 2)) != 0;
		const bool bBayerVert = (resizeRegVal & (0x1 << 1)) != 0;
		const bool bBayerHorz = (resizeRegVal & (0x1 << 0)) != 0;

		const char* k_preColorProcessingSubsampling = "Pre color processing subsampling: ";
		const char* k_postColorProcessingSubsampling = "Post color processing subsampling: ";
		const char* k_standardBinning = "Standard binning: ";
		const char* k_bayerBinning = "Bayer binning: ";
		const char* k_vertHorz = "Vertical + Horizontal";
		const char* k_vertOnly = "Vertical only";
		const char* k_horzOnly = "Horizontal only";
		const char* k_none = "None";
		const char* k_unknown = "Unknown";
		const char* k_newLine = "\r\n";

		std::string resizeStatus;

		if ( !bPreVert && !bPreHorz && !bPostVert && !bPostHorz &&
				!bStdVert && !bStdHorz && !bBayerVert && !bBayerHorz )
		{
			std::string tempStr;
			tempStr += k_unknown;
			tempStr += k_newLine;

			resizeStatus += k_preColorProcessingSubsampling + tempStr;
			resizeStatus += k_postColorProcessingSubsampling + tempStr;
			resizeStatus += k_standardBinning + tempStr;
			resizeStatus += k_bayerBinning + tempStr;

			resizeStatus += "Cols: 0\tRows: 0";

			m_pLabelResizeInformation->set_label(resizeStatus);
			return;

			/*
			   m_pLabelResizeInformation->set_label("");
			   return;
			   */
		}

		// Check pre-color processing subsampling
		resizeStatus += k_preColorProcessingSubsampling;
		if ( bPreVert && bPreHorz )
			resizeStatus += k_vertHorz;
		else if ( bPreVert && !bPreHorz )
			resizeStatus += k_vertOnly;
		else if ( !bPreVert && bPreHorz )
			resizeStatus += k_horzOnly;
		else
			resizeStatus += k_none;

		resizeStatus += k_newLine;

		// Check post-color processing subsampling
		resizeStatus += k_postColorProcessingSubsampling;
		if ( bPostVert && bPostHorz )
			resizeStatus += k_vertHorz;
		else if ( bPostVert && !bPostHorz )
			resizeStatus += k_vertOnly;
		else if ( !bPostVert && bPostHorz )
			resizeStatus += k_horzOnly;
		else
			resizeStatus += k_none;

		resizeStatus += k_newLine;

		// Check std binning
		resizeStatus += k_standardBinning;
		if ( bStdVert && bStdHorz )
			resizeStatus += k_vertHorz;
		else if ( bStdVert && !bStdHorz )
			resizeStatus += k_vertOnly;
		else if ( !bStdVert && bStdHorz )
			resizeStatus += k_horzOnly;
		else
			resizeStatus += k_none;

		resizeStatus += k_newLine;

		// Check bayer binning
		resizeStatus += k_bayerBinning;
		if ( bBayerVert && bBayerHorz )
			resizeStatus += k_vertHorz;
		else if ( bBayerVert && !bBayerHorz )
			resizeStatus += k_vertOnly;
		else if ( !bBayerVert && bBayerHorz )
			resizeStatus += k_horzOnly;
		else
			resizeStatus += k_none;

		resizeStatus += k_newLine;

		// Add the rows and cols
		const unsigned int iNumCols = ( (resizeRegVal & 0x00F00000) >> 20 ) + 1;
		const unsigned int iNumRows = ( (resizeRegVal & 0x000F0000) >> 16 ) + 1;
		char temp[64];
		sprintf(temp, "Cols: %i\tRows: %i", iNumCols, iNumRows);

		resizeStatus += temp;

		m_pLabelResizeInformation->set_label(resizeStatus);
	}

	void Format7Page::GetF7InfoFromPage( Format7ImageSettings* pImageSettings )
	{
		pImageSettings->mode = GetActiveModeComboBox();
		pImageSettings->offsetX = static_cast<unsigned int>(m_pAdjustmentF7Left->get_value());
		pImageSettings->offsetY = static_cast<unsigned int>(m_pAdjustmentF7Top->get_value());
		pImageSettings->width = static_cast<unsigned int>(m_pAdjustmentF7Width->get_value());
		pImageSettings->height = static_cast<unsigned int>(m_pAdjustmentF7Height->get_value());
		pImageSettings->pixelFormat = GetActivePixelFormatComboBox();
	}

	void Format7Page::GetGigEImageInfoFromPage( GigEImageSettings* pImageSettings )
	{
		pImageSettings->offsetX = static_cast<unsigned int>(m_pAdjustmentF7Left->get_value());
		pImageSettings->offsetY = static_cast<unsigned int>(m_pAdjustmentF7Top->get_value());
		pImageSettings->width = static_cast<unsigned int>(m_pAdjustmentF7Width->get_value());
		pImageSettings->height = static_cast<unsigned int>(m_pAdjustmentF7Height->get_value());
		pImageSettings->pixelFormat = GetActivePixelFormatComboBox();
	}

	bool Format7Page::GetF7ImageParametersFromCamera( Mode mode, unsigned int* pLeft, unsigned int* pTop, unsigned int* pWidth, unsigned int* pHeight, PixelFormat* pixelFormat, unsigned int* packetSize )
	{
		if( !GetF7ImageParametersFromCamera(mode, pLeft, pTop, pWidth, pHeight))
			return false;

		Error error;

		// Get the proper mode offset
		unsigned int modeOffset = 0;
		unsigned int modeOffsetRegister = 0x2E0 + (4 * mode);

		error = m_pCamera->ReadRegister( modeOffsetRegister, &modeOffset );
		if( error != PGRERROR_OK )
		{
			return false;
		}

		modeOffset *= 4;
		modeOffset &= 0x000FFFFF;

		// Get pixel format
		unsigned int regVal;
		error = m_pCamera->ReadRegister( modeOffset + 0x010, &regVal );
		if( error != PGRERROR_OK )
		{
			return false;
		}

		*pixelFormat = (PixelFormat) (0x1 << (31 - (regVal >> 24)));

		// Get packet size
		error = m_pCamera->ReadRegister(modeOffset + 0x044, &regVal);
		if( error != PGRERROR_OK )
		{
			return false;
		}

		*packetSize = regVal >> 16;

		return true;
	}

	bool Format7Page::GetF7ImageParametersFromCamera( Mode mode, unsigned int* pLeft, unsigned int* pTop, unsigned int* pWidth, unsigned int* pHeight )
	{
		Error error;

		// Get the proper mode offset
		unsigned int modeOffset = 0;
		unsigned int modeOffsetRegister = 0x2E0 + (4 * mode);

		error = m_pCamera->ReadRegister( modeOffsetRegister, &modeOffset );
		if( error != PGRERROR_OK )
		{
			return false;
		}

		modeOffset *= 4;
		modeOffset &= 0x000FFFFF;

		unsigned int imageSize;
		error = m_pCamera->ReadRegister( modeOffset + 0x008, &imageSize );
		if( error != PGRERROR_OK )
		{
			return false;
		}

		*pLeft = imageSize >> 16;
		*pTop = imageSize & 0x0000FFFF;

		unsigned int imagePosition;
		error = m_pCamera->ReadRegister( modeOffset + 0x00C, &imagePosition );
		if( error != PGRERROR_OK )
		{
			return false;
		}

		*pWidth = imagePosition >> 16;
		*pHeight = imagePosition & 0x0000FFFF;

		return true;
	}

	bool Format7Page::ValidateImageSize()
	{
		Gdk::Color color_red = GetColorAccentRed();
		Gdk::Color color_green = GetColorAccentGreen();

		bool offsetXOk = false;
		bool offsetYOk = false;
		bool widthOk = false;
		bool heightOk = false;

		if ( IsIIDC() == true )
		{
			Format7ImageSettings settings;
			GetF7InfoFromPage( &settings );

			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

			Error error;
			Format7Info fmt7Info;
			fmt7Info.mode = settings.mode;
			bool supported;
			error = pCamera->GetFormat7Info( &fmt7Info, &supported );
			if ( error != PGRERROR_OK )
			{
				// Error
				m_pSpinF7Left->modify_base( Gtk::STATE_NORMAL, color_red );
				m_pSpinF7Top->modify_base( Gtk::STATE_NORMAL, color_red );
				m_pSpinF7Width->modify_base( Gtk::STATE_NORMAL, color_red );
				m_pSpinF7Height->modify_base( Gtk::STATE_NORMAL, color_red );

				return false;
			}

			// Update the drawing area with the new values
			m_pDrawingArea->UpdateSettings( &fmt7Info, &settings );

			offsetXOk = ValidateImageLeft( settings.offsetX, settings.width, fmt7Info.offsetHStepSize, fmt7Info.maxWidth );
			offsetYOk = ValidateImageTop( settings.offsetY, settings.height, fmt7Info.offsetVStepSize, fmt7Info.maxHeight );
			widthOk = ValidateImageWidth( settings.offsetX, settings.width, fmt7Info.imageHStepSize, fmt7Info.maxWidth );
			heightOk = ValidateImageHeight( settings.offsetY, settings.height, fmt7Info.imageVStepSize, fmt7Info.maxHeight );
		}
		else if ( IsGEV() == true )
		{
			GigEImageSettings settings;
			GetGigEImageInfoFromPage( &settings );

			GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);

			GigEImageSettingsInfo imageSettingsInfo;
			Error error = pCamera->GetGigEImageSettingsInfo( &imageSettingsInfo );
			if ( error != PGRERROR_OK )
			{
				// Error
				m_pSpinF7Left->modify_base( Gtk::STATE_NORMAL, color_red );
				m_pSpinF7Top->modify_base( Gtk::STATE_NORMAL, color_red );
				m_pSpinF7Width->modify_base( Gtk::STATE_NORMAL, color_red );
				m_pSpinF7Height->modify_base( Gtk::STATE_NORMAL, color_red );

				return false;
			}

			// Update the drawing area with the new values
			m_pDrawingArea->UpdateSettings( &imageSettingsInfo, &settings );

			offsetXOk = ValidateImageLeft( settings.offsetX, settings.width, imageSettingsInfo.offsetHStepSize, imageSettingsInfo.maxWidth );
			offsetYOk = ValidateImageTop( settings.offsetY, settings.height, imageSettingsInfo.offsetVStepSize, imageSettingsInfo.maxHeight );
			widthOk = ValidateImageWidth( settings.offsetX, settings.width, imageSettingsInfo.imageHStepSize, imageSettingsInfo.maxWidth );
			heightOk = ValidateImageHeight( settings.offsetY, settings.height, imageSettingsInfo.imageVStepSize, imageSettingsInfo.maxHeight );
		}

		m_pSpinF7Left->modify_base( Gtk::STATE_NORMAL, offsetXOk ? color_green : color_red );
		m_pSpinF7Top->modify_base( Gtk::STATE_NORMAL, offsetYOk ? color_green : color_red );
		m_pSpinF7Width->modify_base( Gtk::STATE_NORMAL, widthOk ? color_green : color_red );
		m_pSpinF7Height->modify_base( Gtk::STATE_NORMAL, heightOk ? color_green : color_red );

		// TODO: If there is any failure, maybe we should display a little
		// message to prompt the user why it failed

		if (offsetXOk && offsetYOk && widthOk && heightOk)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Format7Page::ValidateImageLeft( unsigned int left, unsigned int width, unsigned int offsetHStepSize, unsigned int maxWidth )
	{
		// Offset must be a multiple of the step size
		// Offset and width combined must be less than the maximum width
		if ((left % offsetHStepSize == 0) &&
				(left + width <= maxWidth))
		{
			return true;
		}

		return false;
	}

	bool Format7Page::ValidateImageTop( unsigned int top, unsigned int height, unsigned int offsetVStepSize, unsigned int maxHeight )
	{
		// Offset must be a multiple of the step size
		// Offset and height combined must be less than the maximum height
		if ((top % offsetVStepSize == 0) &&
				(top + height <= maxHeight))
		{
			return true;
		}

		return false;
	}

	bool Format7Page::ValidateImageWidth( unsigned int left, unsigned int width, unsigned int imageHStepSize, unsigned int maxWidth )
	{
		// Width must be a multiple of the step size
		// Offset and width combined must be less than the maximum width
		// Width can't be zero
		if ((width % imageHStepSize == 0) &&
				(left + width <= maxWidth) &&
				(width != 0))
		{
			return true;
		}

		return false;
	}

	bool Format7Page::ValidateImageHeight( unsigned int top, unsigned int height, unsigned int offsetVStepSize, unsigned int maxHeight )
	{
		// Height must be a multiple of the step size
		// Offset and height combined must be less than the maximum height
		// Height can't be zero
		if ((height % offsetVStepSize == 0) &&
				(top + height <= maxHeight) &&
				(height != 0))
		{
			return true;
		}

		return false;
	}

	bool Format7Page::ValidatePacketSize()
	{
		unsigned long max = strtoul( m_pLabelMaxPacketSize->get_text().c_str(), NULL, 10 );
		unsigned long min = strtoul( m_pLabelMinPacketSize->get_text().c_str(), NULL, 10 );
		unsigned long curr = static_cast<unsigned int>(m_pAdjustmentPacketSize->get_value());

		Gdk::Color color_red = GetColorAccentRed();
		Gdk::Color color_green = GetColorAccentGreen();

		if( min == 0 )
		{
			min = 8;
		}

		if ( curr > max ||
				curr < min ||
				curr % min != 0 )
		{
			m_pSpinCurrPacketSize->modify_base( Gtk::STATE_NORMAL, color_red );
			return false;
		}
		else
		{
			m_pSpinCurrPacketSize->modify_base( Gtk::STATE_NORMAL, color_green );
			return true;
		}
	}

	bool Format7Page::IsCurrentlyInFormat7()
	{
		if ( IsGEV() == true )
		{
			return true;
		}

		Error error;
		VideoMode currVideoMode;
		FrameRate currFrameRate;

		Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);
		error = pCamera->GetVideoModeAndFrameRate( &currVideoMode, &currFrameRate );
		if ( error != PGRERROR_OK )
		{
			ShowErrorMessageDialog( "Error getting current video mode and frame rate", error );
			return false;
		}

		return (currVideoMode == VIDEOMODE_FORMAT7);
	}

	Mode Format7Page::GetLowestMode()
	{
		Error error;
		int lowest = 0;
		Mode lowestMode = MODE_0;
		bool supported = false;

		if ( IsIIDC() )
		{
			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);
			while ( supported != true )
			{
				if ( (Mode)lowest == NUM_MODES )
				{
					break;
				}

				Format7Info fmt7Info;
				fmt7Info.mode = (Mode)lowest;
				error = pCamera->GetFormat7Info( &fmt7Info, &supported );
				if ( error != PGRERROR_OK )
				{
					ShowErrorMessageDialog( "Error querying Format7 information", error );
					supported = false;
				}

				if ( supported != true )
				{
					lowest++;
				}
			}

			lowestMode = (Mode)lowest;
		}

		return lowestMode;
	}

	PixelFormat Format7Page::GetLowestPixelFormat( Mode mode )
	{
		unsigned int pixelFormats = 0;
		unsigned int vendorPixelFormats = 0;

		if ( IsIIDC() == true )
		{
			bool supported = false;
			Format7Info fmt7Info;
			fmt7Info.mode = mode;

			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);

			Error error = pCamera->GetFormat7Info( &fmt7Info, &supported );
			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error querying Format7 information", error );
				return PIXEL_FORMAT_MONO8;
			}

			pixelFormats = fmt7Info.pixelFormatBitField;
			vendorPixelFormats = fmt7Info.vendorPixelFormatBitField;
		}
		else if ( IsGEV() == true )
		{
			GigEImageSettingsInfo imageSettingsInfo;

			GigECamera* pCamera = dynamic_cast<GigECamera*>(m_pCamera);
			Error error = pCamera->GetGigEImageSettingsInfo( &imageSettingsInfo );
			if ( error != PGRERROR_OK )
			{
				ShowErrorMessageDialog( "Error querying GigE image settings information", error );
				return PIXEL_FORMAT_MONO8;
			}

			pixelFormats = imageSettingsInfo.pixelFormatBitField;
			vendorPixelFormats = imageSettingsInfo.vendorPixelFormatBitField;
		}

		if ( (pixelFormats & PIXEL_FORMAT_MONO8) != 0 )
		{
			return PIXEL_FORMAT_MONO8;
		}

		if ( (pixelFormats & PIXEL_FORMAT_MONO12) != 0 )
		{
			return PIXEL_FORMAT_MONO12;
		}

		if ( (pixelFormats & PIXEL_FORMAT_MONO16) != 0 )
		{
			return PIXEL_FORMAT_MONO16;
		}

		if ( (pixelFormats & PIXEL_FORMAT_RAW8) != 0 )
		{
			return PIXEL_FORMAT_RAW8;
		}

		if ( (pixelFormats & PIXEL_FORMAT_RAW12) != 0 )
		{
			return PIXEL_FORMAT_RAW12;
		}

		if ( (pixelFormats & PIXEL_FORMAT_RAW16) != 0 )
		{
			return PIXEL_FORMAT_RAW16;
		}

		if ( (pixelFormats & PIXEL_FORMAT_411YUV8) != 0 )
		{
			return PIXEL_FORMAT_411YUV8;
		}

		if ( (pixelFormats & PIXEL_FORMAT_422YUV8) != 0 )
		{
			return PIXEL_FORMAT_422YUV8;
		}

		if ( (pixelFormats & PIXEL_FORMAT_444YUV8) != 0 )
		{
			return PIXEL_FORMAT_444YUV8;
		}

		if ( (pixelFormats & PIXEL_FORMAT_RGB8) != 0 )
		{
			return PIXEL_FORMAT_RGB8;
		}

		if ( (pixelFormats & PIXEL_FORMAT_RGB16) != 0 )
		{
			return PIXEL_FORMAT_RGB16;
		}

		if ( (pixelFormats & PIXEL_FORMAT_S_MONO16) != 0 )
		{
			return PIXEL_FORMAT_S_MONO16;
		}

		if ( (pixelFormats & PIXEL_FORMAT_S_RGB16) != 0 )
		{
			return PIXEL_FORMAT_S_RGB16;
		}

		if ( (vendorPixelFormats & PIXEL_FORMAT_422YUV8_JPEG) != 0 )
		{
			return PIXEL_FORMAT_422YUV8_JPEG;
		}

		return PIXEL_FORMAT_MONO8;
	}

	void Format7Page::EnableWidgets()
	{
		m_pComboBoxMode->set_sensitive( true );
		m_pComboBoxPixelFormat->set_sensitive( true );
		m_pLabelMaxImageSize->set_sensitive( true );
		m_pLabelImageSizeUnits->set_sensitive( true );
		m_pLabelOffsetUnits->set_sensitive( true );
		m_pLabelResizeInformation->set_sensitive( true );
		m_pSpinF7Left->set_sensitive( true );
		m_pSpinF7Top->set_sensitive( true );
		m_pSpinF7Width->set_sensitive( true );
		m_pSpinF7Height->set_sensitive( true );
		m_pButtonCenterROI->set_sensitive( true );
		m_pSpinCurrPacketSize->set_sensitive( true );
		m_pHScalePacketSize->set_sensitive( true );
		m_pBtnApply->set_sensitive( true );
	}

	void Format7Page::DisableWidgets()
	{
		m_pComboBoxMode->set_sensitive( false );
		m_pComboBoxPixelFormat->set_sensitive( false );
		m_pLabelMaxImageSize->set_sensitive( false );
		m_pLabelImageSizeUnits->set_sensitive( false );
		m_pLabelOffsetUnits->set_sensitive( false );
		m_pLabelResizeInformation->set_sensitive( false );
		m_pSpinF7Left->set_sensitive( false );
		m_pSpinF7Top->set_sensitive( false );
		m_pSpinF7Width->set_sensitive( false );
		m_pSpinF7Height->set_sensitive( false );
		m_pButtonCenterROI->set_sensitive( false );
		m_pSpinCurrPacketSize->set_sensitive( false );
		m_pHScalePacketSize->set_sensitive( false );
		m_pBtnApply->set_sensitive( false );

		m_pDrawingArea->Disable();
	}

	bool Format7Page::IsLadybugDLLPresent()
	{
		static const char* sk_modules[] = { "LadybugGUI.dll", "LadybugGUId.dll" };

#if defined(_WIN32) || defined(_WIN64)
		int numModules = sizeof ( sk_modules) / sizeof ( char*);
		// Try to search the specified modules.
		HMODULE module;
		int i = 0;
		do{
			module = ::GetModuleHandleA( sk_modules[ i++ ]);
		}while ( module == NULL && i < numModules);

		// Return true if the current module is for ladybug
		if ( module == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
#else
		//
		// For non-Windows, do not care for now.
		//
		return false;
#endif
	}


	void Format7Page::UpdateModeSettings()
	{
		if (m_pCamera == NULL || !IsUpdateable() || !m_isLadybugCamera )
		{
			// Do nothing if the camera is not for ladybugGUI
			return;
		}

		unsigned int currRegVal_ISO_EN = 0;
		Error error = m_pCamera->ReadRegister( 0x614, &currRegVal_ISO_EN );
		if ( error != PGRERROR_OK )
		{
			// Error
			ShowErrorMessageDialog( "Error reading current video mode", error );
		}

		// Do nothing if the camera is not running
		if (  currRegVal_ISO_EN & 0x80000000 )
		{
			// Camera is running
			Camera* pCamera = dynamic_cast<Camera*>(m_pCamera);
			Mode modeToPopulate;
			PixelFormat pixelFormatToPopulate;

			// Currently in Format 7, get the current settings
			Format7ImageSettings imageSettings;
			unsigned int packetSize;
			float speed;
			Error error = pCamera->GetFormat7Configuration( &imageSettings, &packetSize, &speed );
			if ( error != PGRERROR_OK )
			{
				// Error
				ShowErrorMessageDialog( "Error getting current Format7 configuration", error );
			}

			modeToPopulate = imageSettings.mode;
			pixelFormatToPopulate = imageSettings.pixelFormat;
			// Populate fields with camera settings for current mode
			SetActiveModeComboBox( modeToPopulate );
			OnComboBoxModeChanged();

			// Do not allow changing mode and pixel format when LB camera is running
			m_pComboBoxMode->set_sensitive( false );
			m_pComboBoxPixelFormat->set_sensitive( false );

			if ( modeToPopulate != MODE_3 && modeToPopulate != MODE_7 )
			{
				// Non JPEG mode, do not allow changing image size
				m_pSpinF7Height->set_sensitive( false );
				m_pDrawingArea->set_sensitive( false );
			}
			else
			{
				// JPEG mode, allow changing image size
				m_pSpinF7Height->set_sensitive( true );
				m_pDrawingArea->set_sensitive( true );
			}

		}

		return;
	}

	sigc::signal<void> Format7Page::signal_format7_applied()
	{
		return m_signal_format7_applied;
	}
}
