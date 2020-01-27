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
#ifndef PGR_FC2_INFORMATIONPANE_H
#define PGR_FC2_INFORMATIONPANE_H

#include <string>
#include "TreeCtrlX.h"
class InformationPane
{
	public:
		struct FPSStruct
		{
			double processedFrameRate;
			double displayedFrameRate;
			double requestedFrameRate;
			double receivedFrameRate;

			FPSStruct()
			{
				processedFrameRate = 0.0;
				displayedFrameRate = 0.0;
				requestedFrameRate = 0.0;
				receivedFrameRate = 0.0;
			}
		};

		struct ImageInfoStruct
		{
			unsigned int width;
			unsigned int height;
			unsigned int stride;
			FlyCapture2::PixelFormat pixFmt;

			ImageInfoStruct()
			{
				width = 0;
				height = 0;
				stride = 0;
				pixFmt = FlyCapture2::NUM_PIXEL_FORMATS;
			}
		};

		struct EmbeddedImageInfoStruct
		{
			union
			{
				unsigned int arEmbeddedInfo[10];

				struct
				{
					unsigned int timestamp;
					unsigned int gain;
					unsigned int shutter;
					unsigned int brightness;
					unsigned int exposure;
					unsigned int whiteBalance;
					unsigned int frameCounter;
					unsigned int strobePattern;
					unsigned int GPIOPinState;
					unsigned int ROIPosition;
				} Individual;
			};

			EmbeddedImageInfoStruct()
			{
				memset(arEmbeddedInfo, 0x0, 10);
			}
		};

		struct DiagnosticsStruct
		{
			int skippedFrames;
			int linkRecoveryCount;
			int linkerErrors;
			int transmitFailures;
			int packetResendRequested;
			int packetResendReceived;
			std::string timeSinceInitialization;
			std::string timeSinceLastBusReset;

			DiagnosticsStruct()
			{
				skippedFrames = -1;
				linkRecoveryCount = -1;
				linkerErrors = -1;
				transmitFailures = -1;
				packetResendRequested = -1;
				packetResendReceived = -1;
				timeSinceInitialization = "";
				timeSinceLastBusReset = "";
			}
		};

		struct InformationPaneStruct
		{
			FPSStruct fps;
			FlyCapture2::TimeStamp timestamp;
			ImageInfoStruct imageInfo;
			EmbeddedImageInfoStruct embeddedInfo;
			DiagnosticsStruct diagnostics;
		};

		InformationPane();
		virtual ~InformationPane(void);
		bool Initialize(CTreeCtrlX* pCamInfoTreeView);
		void UpdateInformationPane(CTreeCtrlX* pCamInfoTreeView, InformationPaneStruct infoStruct );
		void ExpandDiagnosticTree(CTreeCtrlX* pCamInfoTreeView);
		bool IsItemFromDiagosticBranch(HTREEITEM hCurSel);
	protected:

	private:
		static std::string GetPixelFormatStr( FlyCapture2::PixelFormat pixFmt);
		CFont m_monospaceFont;
		CFont m_Font;
		// FPS
		HTREEITEM m_pLblDisplayedFPS;
		HTREEITEM m_pLblProcessedFPS;
		HTREEITEM m_pLblRequestedFPS;
		HTREEITEM m_pLblReceivedFPS;

		// Timestamp
		HTREEITEM m_pLblTimestampSeconds;
		HTREEITEM m_pLblTimestampMicroseconds;
		HTREEITEM m_pLbl1394CycleTimeSeconds;
		HTREEITEM m_pLbl1394CycleTimeCount;
		HTREEITEM m_pLbl1394CycleTimeOffset;

		// Image info
		HTREEITEM m_pLblImageWidth;
		HTREEITEM m_pLblImageHeight;
		HTREEITEM m_pLblImagePixFmt;
		HTREEITEM m_pLblImageBitsPerPixel;

		// Embedded image info
		HTREEITEM m_pLblEmbeddedGain;
		HTREEITEM m_pLblEmbeddedShutter;
		HTREEITEM m_pLblEmbeddedBrightness;
		HTREEITEM m_pLblEmbeddedExposure;
		HTREEITEM m_pLblEmbeddedWhiteBalance;
		HTREEITEM m_pLblEmbeddedFrameCounter;
		HTREEITEM m_pLblEmbeddedStrobePattern;
		HTREEITEM m_pLblEmbeddedGPIOPinState;
		HTREEITEM m_pLblEmbeddedROIPosition;

		// Diagnostics
		HTREEITEM m_pLblDiagnosticRootItem;
		HTREEITEM m_pLblSkippedFrames;
		HTREEITEM m_pLblLinkRecoveryCount;
		HTREEITEM m_pLblTransmitFailures;
		HTREEITEM m_pLblLinkerErrors;
		HTREEITEM m_pLblTimeSinceInitialization;
		HTREEITEM m_pLblTimeSinceLastBusReset;
		HTREEITEM m_pLblPacketResendRequested;
		HTREEITEM m_pLblPacketResendReceived;


		void UpdateFrameRateInfo(CTreeCtrlX* pCamInfoTreeView, FPSStruct fps );
		void UpdateTimestampInfo(CTreeCtrlX* pCamInfoTreeView, FlyCapture2::TimeStamp timestamp );
		void UpdateImageInfo(CTreeCtrlX* pCamInfoTreeView, ImageInfoStruct imageInfo );
		void UpdateEmbeddedInfo(CTreeCtrlX* pCamInfoTreeView, EmbeddedImageInfoStruct embeddedInfo );
		void UpdateDiagnostics(CTreeCtrlX* pCamInfoTreeView, DiagnosticsStruct diagnostics );
		void UpdateDiagnosticTreeItemColor(CTreeCtrlX* pCamInfoTreeView);
};

#endif // PGR_FC2_INFORMATIONPANE_H
