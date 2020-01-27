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

using System;
using System.Collections.Generic;
using System.Text;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    internal class BusSpeedTranslator
    {
        public static string GetBusSpeedString(BusSpeed speed)
        {
            switch (speed)
            {
                case BusSpeed.S100: return "S100";
                case BusSpeed.S200: return "S200";
                case BusSpeed.S400: return "S400";
                case BusSpeed.S480: return "S480";
                case BusSpeed.S800: return "S800";
                case BusSpeed.S1600: return "S1600";
                case BusSpeed.S5000: return "S5000";
                default: return "Unknown bus speed";
            }
        }

        public static string GetPCIeBusSpeedString(PCIeBusSpeed speed)
        {
            switch (speed)
            {
                case PCIeBusSpeed.Speed_2_5: return "2.5 GT/s";
                case PCIeBusSpeed.Speed_5_0: return "5.0 GT/s";                
                default: return "Unknown PCIe bus speed";
            }
        }
    }
}
