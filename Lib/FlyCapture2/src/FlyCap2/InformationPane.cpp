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
#include <time.h>
#include "stdafx.h"
#include "InformationPane.h"

using namespace FlyCapture2;

InformationPane::InformationPane()
{
	VERIFY(m_monospaceFont.CreatePointFont(80, _T("Lucida Sans Unicode")));
}

InformationPane::~InformationPane()
{
	m_monospaceFont.DeleteObject();
}

bool InformationPane::Initialize(CTreeCtrlX* pCamInfoTreeView)
{
	if (pCamInfoTreeView == NULL)
	{
		return false;
	}

	pCamInfoTreeView->ResetMap();
	pCamInfoTreeView->DeleteAllItems();
	pCamInfoTreeView->SetFont(&m_monospaceFont,TRUE);
	//HTREEITEM root = TVI_ROOT;
	HTREEITEM root = pCamInfoTreeView->InsertItem("Camera Information");
	pCamInfoTreeView->SetItem(root, TVIF_STATE, NULL, 0, 0, TVIS_BOLD,TVIS_BOLD, 0);

	HTREEITEM rootItem = pCamInfoTreeView->InsertItem("Frame rate",root);
	pCamInfoTreeView->SetItem(rootItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD,TVIS_BOLD, 0);

	m_pLblProcessedFPS = pCamInfoTreeView->InsertItem("Processed: 0 fps",rootItem);
	m_pLblDisplayedFPS = pCamInfoTreeView->InsertItem("Displayed: 0 fps",rootItem);
	m_pLblRequestedFPS = pCamInfoTreeView->InsertItem("Requested: 0 fps",rootItem);
	m_pLblReceivedFPS = pCamInfoTreeView->InsertItem("Received:  0 fps",rootItem);
	pCamInfoTreeView->Expand(rootItem,TVE_EXPAND);


	rootItem = pCamInfoTreeView->InsertItem("Timestamp",root);
	pCamInfoTreeView->SetItem(rootItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD,TVIS_BOLD, 0);

	m_pLblTimestampSeconds = pCamInfoTreeView->InsertItem("Seconds: N/A",rootItem);
	m_pLblTimestampMicroseconds = pCamInfoTreeView->InsertItem("Microseconds: 0",rootItem);
	m_pLbl1394CycleTimeSeconds = pCamInfoTreeView->InsertItem("Camera timestamp seconds: 0",rootItem);
	m_pLbl1394CycleTimeCount = pCamInfoTreeView->InsertItem("Camera timestamp count: 0000",rootItem);
	m_pLbl1394CycleTimeOffset = pCamInfoTreeView->InsertItem("Camera timestamp offset: 0000",rootItem);
	pCamInfoTreeView->Expand(rootItem,TVE_EXPAND);


	rootItem = pCamInfoTreeView->InsertItem("Image",root);
	pCamInfoTreeView->SetItem(rootItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD,TVIS_BOLD, 0);

	m_pLblImageWidth = pCamInfoTreeView->InsertItem("Width: 0",rootItem);
	m_pLblImageHeight = pCamInfoTreeView->InsertItem("Height: 0",rootItem);
	m_pLblImagePixFmt = pCamInfoTreeView->InsertItem("Pixel format: Unknown",rootItem);
	m_pLblImageBitsPerPixel = pCamInfoTreeView->InsertItem("Bits per pixel: 0",rootItem);
	pCamInfoTreeView->Expand(rootItem,TVE_EXPAND);


	rootItem = pCamInfoTreeView->InsertItem("Embedded image information",root);
	pCamInfoTreeView->SetItem(rootItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD,TVIS_BOLD, 0);

	m_pLblEmbeddedGain = pCamInfoTreeView->InsertItem("Gain: 00000000",rootItem);
	m_pLblEmbeddedShutter = pCamInfoTreeView->InsertItem("Shutter: 00000000",rootItem);
	m_pLblEmbeddedBrightness = pCamInfoTreeView->InsertItem("Brightness: 00000000",rootItem);
	m_pLblEmbeddedExposure = pCamInfoTreeView->InsertItem("Exposure: 00000000",rootItem);
	m_pLblEmbeddedWhiteBalance = pCamInfoTreeView->InsertItem("White balance 00000000",rootItem);
	m_pLblEmbeddedFrameCounter = pCamInfoTreeView->InsertItem("Frame counter: 00000000",rootItem);
	m_pLblEmbeddedStrobePattern = pCamInfoTreeView->InsertItem("Strobe pattern: 00000000",rootItem);
	m_pLblEmbeddedGPIOPinState = pCamInfoTreeView->InsertItem("GPIO pin state: 00000000",rootItem);
	m_pLblEmbeddedROIPosition = pCamInfoTreeView->InsertItem("ROI position: 00000000",rootItem);
	//pCamInfoTreeView->Expand(rootItem,TVE_EXPAND);

	m_pLblDiagnosticRootItem = pCamInfoTreeView->InsertItem("Diagnostics",root);
	pCamInfoTreeView->SetItem(m_pLblDiagnosticRootItem, TVIF_STATE, NULL, 0, 0, TVIS_BOLD,TVIS_BOLD, 0);
	m_pLblSkippedFrames = pCamInfoTreeView->InsertItem("Skipped frames: 0",m_pLblDiagnosticRootItem);
	m_pLblLinkRecoveryCount = pCamInfoTreeView->InsertItem("Link recovery count (camera): 0",m_pLblDiagnosticRootItem);
	m_pLblLinkerErrors = pCamInfoTreeView->InsertItem("Link recovery count (host): 0",m_pLblDiagnosticRootItem);
	m_pLblTransmitFailures = pCamInfoTreeView->InsertItem("Transmit failures: 0",m_pLblDiagnosticRootItem);
	m_pLblPacketResendRequested = pCamInfoTreeView->InsertItem("Packet Resend requested: 0",m_pLblDiagnosticRootItem);
	m_pLblPacketResendReceived = pCamInfoTreeView->InsertItem("Packet Resend Received: 0",m_pLblDiagnosticRootItem);
	m_pLblTimeSinceInitialization = pCamInfoTreeView->InsertItem("Time since initialization: N/A",m_pLblDiagnosticRootItem);
	m_pLblTimeSinceLastBusReset = pCamInfoTreeView->InsertItem("Time since last bus reset: N/A",m_pLblDiagnosticRootItem);
	//pCamInfoTreeView->Expand(rootItem,TVE_EXPAND);

	pCamInfoTreeView->EnableToolTips();

	pCamInfoTreeView->Expand(root,TVE_EXPAND);
	return true;
}

void InformationPane::UpdateInformationPane(CTreeCtrlX* pCamInfoTreeView, InformationPaneStruct infoStruct )
{
	if (pCamInfoTreeView == NULL)
	{
		return;
	}
	UpdateFrameRateInfo(pCamInfoTreeView, infoStruct.fps);
	UpdateTimestampInfo(pCamInfoTreeView, infoStruct.timestamp);
	UpdateImageInfo(pCamInfoTreeView, infoStruct.imageInfo);
	UpdateEmbeddedInfo(pCamInfoTreeView, infoStruct.embeddedInfo );
	UpdateDiagnostics(pCamInfoTreeView, infoStruct.diagnostics );
	UpdateDiagnosticTreeItemColor(pCamInfoTreeView);
}

void InformationPane::UpdateFrameRateInfo(CTreeCtrlX* pCamInfoTreeView, FPSStruct fps )
{
	char info[512];

	sprintf( info, "Processed: %3.2f fps", fps.processedFrameRate );
	pCamInfoTreeView->SetItem(m_pLblProcessedFPS, TVIF_TEXT, info, 0, 0, 0, 0, 0);

	sprintf( info, "Displayed: %3.2f fps", fps.displayedFrameRate );
	pCamInfoTreeView->SetItem(m_pLblDisplayedFPS, TVIF_TEXT, info, 0, 0, 0, 0, 0);

	sprintf( info, "Requested: %3.2f fps", fps.requestedFrameRate );
	pCamInfoTreeView->SetItem(m_pLblRequestedFPS, TVIF_TEXT, info, 0, 0, 0, 0, 0);

	if(fps.receivedFrameRate != 0.00)
	{
		sprintf( info, "Received: %3.2f fps", fps.receivedFrameRate );
	}
	else
	{
		sprintf( info, "Received: Timestamp N/A" );
	}
	pCamInfoTreeView->SetItem(m_pLblReceivedFPS, TVIF_TEXT, info, 0, 0, 0, 0, 0);

}

void InformationPane::UpdateTimestampInfo(CTreeCtrlX* pCamInfoTreeView, TimeStamp timestamp )
{
	char timestampBuff[512];

	if ( timestamp.seconds != 0)
	{
		const time_t t = timestamp.seconds;
		char ctimeStr[256];
		sprintf(ctimeStr,"Seconds: %s",ctime( (const time_t *)&t));
		ctimeStr[strlen( ctimeStr) - 1] = 0; // remove the line feed at the end of the string
		pCamInfoTreeView->SetItem(m_pLblTimestampSeconds, TVIF_TEXT, ctimeStr , 0, 0, 0, 0, 0);

		sprintf( timestampBuff, "Microseconds: %u", timestamp.microSeconds );
		pCamInfoTreeView->SetItem(m_pLblTimestampMicroseconds,TVIF_TEXT,timestampBuff,0,0,0,0,0);
	}


	sprintf( timestampBuff, "Camera timestamp seconds: %u", timestamp.cycleSeconds );
	pCamInfoTreeView->SetItem(m_pLbl1394CycleTimeSeconds,TVIF_TEXT,timestampBuff,0,0,0,0,0);


	sprintf( timestampBuff, "Camera timestamp count:  %04u", timestamp.cycleCount );
	pCamInfoTreeView->SetItem(m_pLbl1394CycleTimeCount,TVIF_TEXT,timestampBuff,0,0,0,0,0);


	sprintf( timestampBuff, "Camera timestamp offset: %04u", timestamp.cycleOffset );
	pCamInfoTreeView->SetItem(m_pLbl1394CycleTimeOffset,TVIF_TEXT,timestampBuff,0,0,0,0,0);
}

void InformationPane::UpdateImageInfo(CTreeCtrlX* pCamInfoTreeView, ImageInfoStruct imageInfo )
{
	double bitsPerPixel;

	char info[512];

	bitsPerPixel = (imageInfo.stride * 8) / static_cast<double>(imageInfo.width);

	sprintf( info, "Width: %u", imageInfo.width );
	pCamInfoTreeView->SetItem(m_pLblImageWidth,TVIF_TEXT,info,0,0,0,0,0);

	sprintf( info, "Height: %u", imageInfo.height );
	pCamInfoTreeView->SetItem(m_pLblImageHeight,TVIF_TEXT,info,0,0,0,0,0);

	sprintf( info, "Pixel format: %s", GetPixelFormatStr(imageInfo.pixFmt).c_str() );
	pCamInfoTreeView->SetItem(m_pLblImagePixFmt,TVIF_TEXT,info,0,0,0,0,0);

	sprintf( info, "Bits per pixel: %2.0f", bitsPerPixel );
	pCamInfoTreeView->SetItem(m_pLblImageBitsPerPixel,TVIF_TEXT,info,0,0,0,0,0);
}

void InformationPane::UpdateEmbeddedInfo(CTreeCtrlX* pCamInfoTreeView, EmbeddedImageInfoStruct embeddedInfo )
{
	char entry[128];

	sprintf( entry, "Gain:           %08X", embeddedInfo.Individual.gain );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedGain,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "Shutter:        %08X", embeddedInfo.Individual.shutter );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedShutter,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "Brightness:     %08X", embeddedInfo.Individual.brightness );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedBrightness,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "Exposure:       %08X", embeddedInfo.Individual.exposure );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedExposure,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "White balance:  %08X", embeddedInfo.Individual.whiteBalance );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedWhiteBalance,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "Frame counter:  %08X", embeddedInfo.Individual.frameCounter );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedFrameCounter,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "Strobe pattern: %08X", embeddedInfo.Individual.strobePattern );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedStrobePattern,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "GPIO pin state: %08X", embeddedInfo.Individual.GPIOPinState );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedGPIOPinState,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "ROI position:   %08X", embeddedInfo.Individual.ROIPosition );
	pCamInfoTreeView->SetItem(m_pLblEmbeddedROIPosition,TVIF_TEXT,entry,0,0,0,0,0);

}

void InformationPane::UpdateDiagnostics(CTreeCtrlX* pCamInfoTreeView, DiagnosticsStruct diagnostics )
{
	char entry[512];

	if (diagnostics.skippedFrames != -1)
	{
		sprintf( entry, "Skipped frames: %d", diagnostics.skippedFrames );
	}
	else
	{
		sprintf( entry, "Skipped frames: 0");
	}
	pCamInfoTreeView->SetItem(m_pLblSkippedFrames,TVIF_TEXT,entry,0,0,0,0,0);

	if (diagnostics.linkRecoveryCount != -1)
	{
		sprintf( entry, "Link recovery count (camera): %d", diagnostics.linkRecoveryCount );
	}
	else
	{
		sprintf( entry, "Link recovery count (camera): 0" );
	}
	pCamInfoTreeView->SetItem(m_pLblLinkRecoveryCount,TVIF_TEXT,entry,0,0,0,0,0);

	if (diagnostics.transmitFailures != -1)
	{
		sprintf( entry, "Transmit failures: %d", diagnostics.transmitFailures );
	}
	else
	{
		sprintf( entry, "Transmit failures: 0" );
	}
	pCamInfoTreeView->SetItem(m_pLblTransmitFailures,TVIF_TEXT,entry,0,0,0,0,0);

	if (diagnostics.linkerErrors != -1)
	{
		sprintf( entry, "Link recovery count (host): %d", diagnostics.linkerErrors );
	}
	else
	{
		sprintf( entry, "Link recovery count (host): 0" );
	}
	pCamInfoTreeView->SetItem(m_pLblLinkerErrors,TVIF_TEXT,entry,0,0,0,0,0);

	//Pakcet Resend Requested
	if (diagnostics.packetResendRequested != -1)
	{
		sprintf( entry, "Packet Resend Requested: %d", diagnostics.packetResendRequested );
	}
	else
	{
		sprintf( entry, "Packet Resend Requested: 0" );
	}
	pCamInfoTreeView->SetItem(m_pLblPacketResendRequested,TVIF_TEXT,entry,0,0,0,0,0);

	// Packet Resend Received
	if (diagnostics.packetResendReceived != -1)
	{
		sprintf( entry, "Packet Resend Received: %d", diagnostics.packetResendReceived );
	}
	else
	{
		sprintf( entry, "Packet Resend Received: 0" );
	}
	pCamInfoTreeView->SetItem(m_pLblPacketResendReceived,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "Time since initialization: %s", diagnostics.timeSinceInitialization.c_str());
	pCamInfoTreeView->SetItem(m_pLblTimeSinceInitialization,TVIF_TEXT,entry,0,0,0,0,0);

	sprintf( entry, "Time since last bus reset: %s", diagnostics.timeSinceLastBusReset.c_str() );
	pCamInfoTreeView->SetItem(m_pLblTimeSinceLastBusReset,TVIF_TEXT,entry,0,0,0,0,0);
}

void InformationPane::ExpandDiagnosticTree(CTreeCtrlX* pCamInfoTreeView)
{
	pCamInfoTreeView->Expand(m_pLblDiagnosticRootItem, TVE_EXPAND);
	UpdateDiagnosticTreeItemColor(pCamInfoTreeView);
}

void InformationPane::UpdateDiagnosticTreeItemColor(CTreeCtrlX* pCamInfoTreeView)
{
	// Change Skipped frames font color to red if there were errors
	if(pCamInfoTreeView->GetItemText(m_pLblSkippedFrames)!= "Skipped frames: 0")
	{
		pCamInfoTreeView->SetItemColor(m_pLblSkippedFrames, RGB(255,0,0));
	}
	else
	{
		pCamInfoTreeView->SetItemColor(m_pLblSkippedFrames, RGB(0,0,0));
	}

	// Change Link recovery count font color to red if there were errors
	if(pCamInfoTreeView->GetItemText(m_pLblLinkRecoveryCount)!= "Link recovery count (camera): 0")
	{
		pCamInfoTreeView->SetItemColor(m_pLblLinkRecoveryCount, RGB(255,0,0));
	}
	else
	{
		pCamInfoTreeView->SetItemColor(m_pLblLinkRecoveryCount, RGB(0,0,0));
	}

	// Change Transmit failures font color to red if there were errors
	if(pCamInfoTreeView->GetItemText(m_pLblTransmitFailures)!= "Transmit failures: 0")
	{
		pCamInfoTreeView->SetItemColor(m_pLblTransmitFailures, RGB(255,0,0));
	}
	else
	{
		pCamInfoTreeView->SetItemColor(m_pLblTransmitFailures, RGB(0,0,0));
	}

	// Change Linker error count font color to red if there were errors
	if(pCamInfoTreeView->GetItemText(m_pLblLinkerErrors)!= "Link recovery count (host): 0")
	{
		pCamInfoTreeView->SetItemColor(m_pLblLinkerErrors, RGB(255,0,0));
	}
	else
	{
		pCamInfoTreeView->SetItemColor(m_pLblLinkerErrors, RGB(0,0,0));
	}
}

bool InformationPane::IsItemFromDiagosticBranch(HTREEITEM hCurSel)
{
	if(hCurSel == m_pLblSkippedFrames ||  hCurSel == m_pLblLinkRecoveryCount || hCurSel == m_pLblTransmitFailures || hCurSel == m_pLblTimeSinceInitialization || hCurSel == m_pLblTimeSinceLastBusReset || hCurSel == m_pLblLinkerErrors || hCurSel == m_pLblPacketResendRequested || hCurSel == m_pLblPacketResendReceived)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string InformationPane::GetPixelFormatStr(PixelFormat pixFmt)
{
	std::string pixelFormatStr("Unknown");

	switch( pixFmt )
	{
		case PIXEL_FORMAT_MONO8:
			pixelFormatStr = "Mono 8"; break;
		case PIXEL_FORMAT_MONO12:
			pixelFormatStr = "Mono 12"; break;
		case PIXEL_FORMAT_MONO16:
			pixelFormatStr = "Mono 16"; break;
		case PIXEL_FORMAT_RAW8:
			pixelFormatStr = "Raw 8"; break;
		case PIXEL_FORMAT_RAW12:
			pixelFormatStr = "Raw 12"; break;
		case PIXEL_FORMAT_RAW16:
			pixelFormatStr = "Raw 16"; break;
		case PIXEL_FORMAT_411YUV8:
			pixelFormatStr = "YUV 411"; break;
		case PIXEL_FORMAT_422YUV8:
			pixelFormatStr = "YUV 422"; break;
		case PIXEL_FORMAT_444YUV8:
			pixelFormatStr = "YUV 444"; break;
		case PIXEL_FORMAT_RGB8: // Also RGB
			pixelFormatStr = "RGB 8"; break;
		case PIXEL_FORMAT_S_MONO16:
			pixelFormatStr = "Signed Mono 16"; break;
		case PIXEL_FORMAT_S_RGB16:
			pixelFormatStr = "Signed RGB 16"; break;
		case PIXEL_FORMAT_BGR:
			pixelFormatStr = "BGR"; break;
		case PIXEL_FORMAT_BGRU:
			pixelFormatStr = "BGRU"; break;
		case PIXEL_FORMAT_RGBU:
			pixelFormatStr = "RGBU"; break;
		case PIXEL_FORMAT_422YUV8_JPEG:
			pixelFormatStr = "YUV 422 (JPEG)"; break;
		default:
			pixelFormatStr = "Unknown"; break;
	}

	return pixelFormatStr;
}
