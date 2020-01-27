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
// $Id: EnumerationController.cs,v 1.2 2010-08-12 21:17:08 soowei Exp $
//=============================================================================

using System;

using Microsoft.Win32;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /** Controls enumeration of specific interfaces. */ 
    internal class EnumerationController
    {
        public static bool IsEnumerationDisabled(InterfaceType interfaceType)
        {
            RegistryKey key = Registry.LocalMachine;
            RegistryKey subKey = key.OpenSubKey(@"SOFTWARE\Point Grey Research, Inc.\FlyCapture2");
            if (subKey != null)
            {
                string keyName = GetKeyName(interfaceType);
                int keyValue = 0;
                try
                {
                    keyValue = (int)subKey.GetValue(keyName);
                }
                catch (System.Exception ex)
                {
                    return false;
                }
                
                return keyValue == 1;
            }

            return false;
        }

        public static void SetEnumerationDisabled(InterfaceType interfaceType, bool isDisabled)
        {
            RegistryKey key = Registry.LocalMachine;
            RegistryKey subKey = key.OpenSubKey(
                @"SOFTWARE\Point Grey Research, Inc.\FlyCapture2",
                RegistryKeyPermissionCheck.ReadWriteSubTree);
            if (subKey != null)
            {
                string keyName = GetKeyName(interfaceType);
                subKey.SetValue(keyName, isDisabled ? 1 : 0);
            }
        }

        private static string GetKeyName(InterfaceType interfaceType)
        {
            switch(interfaceType)
            {
                case FlyCapture2Managed.InterfaceType.Ieee1394: return "Disable1394Enumeration";
                case FlyCapture2Managed.InterfaceType.Usb2: return "DisableUSBEnumeration";
                case FlyCapture2Managed.InterfaceType.GigE: return "DisableGigEEnumeration";                    
                default: return "Unknown";
            }
        }
    }
}

//=============================================================================
// $Log: not supported by cvs2svn $
// Revision 1.1  2010/08/10 22:20:16  soowei
// [1] Add functionality to enable GigE enumeration upon startup if it is disabled through the registry
//
//=============================================================================
