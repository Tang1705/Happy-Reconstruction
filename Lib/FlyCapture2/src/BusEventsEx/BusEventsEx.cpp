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
// $Id: BusEventsEx.cpp 316528 2017-02-22 00:03:53Z alin $
//=============================================================================

#include "stdafx.h"

#ifdef LINUX
#include <unistd.h>
#endif

#include "FlyCapture2.h"
#include <ctime>
#include <iostream>
#include <sstream>

using namespace FlyCapture2;
using namespace std;

void PrintBuildInfo()
{
    FC2Version fc2Version;
    Utilities::GetLibraryVersion(&fc2Version);

    ostringstream version;
    version << "FlyCapture2 library version: " << fc2Version.major << "."
            << fc2Version.minor << "." << fc2Version.type << "."
            << fc2Version.build;
    cout << version.str() << endl;

    ostringstream timeStamp;
    timeStamp << "Application build date: " << __DATE__ << " " << __TIME__;
    cout << timeStamp.str() << endl << endl;
}

void PrintError(Error error) { error.PrintErrorTrace(); }

std::string GetCurrentTimeString()
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    std::ostringstream formatTime;
    formatTime << (timeinfo->tm_year + 1900) << "-" << (timeinfo->tm_mon + 1)
               << "-" << (timeinfo->tm_mday) << " " << (timeinfo->tm_hour)
               << ":" << (timeinfo->tm_min) << ":" << (timeinfo->tm_sec);

    return formatTime.str();
}

void OnBusReset(void *pParam, unsigned int serialNumber)
{
    std::cout << GetCurrentTimeString() << " - *** BUS RESET ***" << std::endl;
}

void OnBusArrival(void *pParam, unsigned int serialNumber)
{
    std::cout << GetCurrentTimeString() << " - *** BUS ARRIVAL ("
              << serialNumber << ") ***" << std::endl;
}

void OnBusRemoval(void *pParam, unsigned int serialNumber)
{
    std::cout << GetCurrentTimeString() << " - *** BUS REMOVAL ("
              << serialNumber << ") ***" << std::endl;
}

int BusResetLoop()
{
    BusManager busMgr;

    FlyCapture2::CallbackHandle m_resetHandle;
    FlyCapture2::CallbackHandle m_arrivalHandle;
    FlyCapture2::CallbackHandle m_removalHandle;

    // Register bus events
    Error error;
    error = busMgr.RegisterCallback(&OnBusReset, BUS_RESET, NULL, &m_resetHandle);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    error = busMgr.RegisterCallback(&OnBusArrival, ARRIVAL, NULL, &m_arrivalHandle);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    error = busMgr.RegisterCallback(&OnBusRemoval, REMOVAL, NULL, &m_removalHandle);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Prevent exit if CTL+C is pressed.
    std::cout << "Press any key to exit..." << std::endl;
    std::cin.ignore();

    // Unregister bus events
    error = busMgr.UnregisterCallback(m_resetHandle);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    error = busMgr.UnregisterCallback(m_arrivalHandle);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    error = busMgr.UnregisterCallback(m_removalHandle);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    return 0;
}

int main(int /*argc*/, char ** /*argv*/)
{
    PrintBuildInfo();

    // Start bus reset loop
    int retValue = BusResetLoop();
    if (retValue != 0)
    {
        return -1;
    }

    cout << "Done! Press Enter to exit..." << endl;
    cin.ignore();

    return 0;
}
