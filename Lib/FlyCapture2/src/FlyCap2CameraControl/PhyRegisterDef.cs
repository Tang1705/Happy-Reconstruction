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
using System.Text;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    internal partial class BusTopologyPage
    {
        //defined constant
        private const uint k_basePage = 0;
        private const uint k_portPage = 0;
        private const uint k_vendorPage = 1;
        private const uint k_totalPortsField = 7;

        /** Multiplier used to generate original image surface area. */
        private const float k_multiplier = 8.0f;

        /** Vertical spacing between nodes. */
        private const int k_vertSpacing = 20;

        private Field[] k_vendorList = new Field[]
        {
            new Field("FLIR Integrated Imaging Solutions", 0x00B09D),
            new Field("Texas Instruments",   0x080028), 
            new Field("LSI/Agere Systems",   0x00053D),
            new Field("Lucent Technologies", 0x00601D),
            new Field("Node",                0x000000)
        };

        private Register[] k_baseRegisterInfo = new Register[]
        {
            new Register("Physical_ID",           0, 0xFC),
            new Register("R",                     0, 0x02),
            new Register("PS",                    0, 0x01),
            new Register("RHB",                   1, 0x80),
            new Register("IBR",                   1, 0x40),
            new Register("Gap_count",             1, 0x3F),
            new Register("Extended",              2, 0xE0),
            new Register("Total_Ports",           2, 0x1F),
            new Register("Max_speed",             3, 0xE0),
            new Register("Enable_standby",        3, 0x10),
            new Register("Delay",                 3, 0x0F),
            new Register("LCtrl",                 4, 0x80),
            new Register("Contender",             4, 0x40),
            new Register("Jitter",                4, 0x38),
            new Register("Pwr_class",             4, 0x07),
            new Register("Watchdog",              5, 0x80),
            new Register("ISBR",                  5, 0x40),
            new Register("Loop",                  5, 0x20),
            new Register("Pwr_fail",              5, 0x10),
            new Register("Timeout",               5, 0x08),
            new Register("Port_event",            5, 0x04),
            new Register("Enab_accel",            5, 0x02),
            new Register("Enab_multi",            5, 0x01),
            new Register("Max_legacy_path_speed", 6, 0xE0),
            new Register("B_link",                6, 0x10),
            new Register("Bridge",                6, 0x0C),
            new Register("Page_select",           7, 0xE0),
            new Register("Port_select",           7, 0x0F)
        };

        private Register[] k_portStatusInfo = new Register[]
        {
            new Register("AStat",                 8,  0xC0),
            new Register("BStat",                 8,  0x30),
            new Register("Child",                 8,  0x08),
            new Register("Connected",             8,  0x04),
            new Register("Receive_OK",            8,  0x02),
            new Register("Disabled",              8,  0x01),
            new Register("Negotiated_speed",      9,  0xE0),
            new Register("Int_enable",            9,  0x10),
            new Register("Fault",                 9,  0x08),
            new Register("Standby_fault",         9,  0x04),
            new Register("Disable_scrambler",     9,  0x02),
            new Register("Beta_mode_only_port",   9,  0x01),
            new Register("DC_connected",          10, 0x80),
            new Register("Max_port_speed",        10, 0x70),
            new Register("LPP",                   10, 0x08),
            new Register("Cable_speed",           10, 0x07),
            new Register("Connection_unreliable", 11, 0x80),
            new Register("Beta_mode",             11, 0x08),
            new Register("Port_error",            12, 0xFF),
            new Register("Loop_diable",           13, 0x04),
            new Register("In_standby",            13, 0x02),
            new Register("Hard_disable",          13, 0x01)
        };
    }

    internal class Field
    {
        private string m_name = "N/A";
        private uint m_id = 0;

        public Field(string name, uint id)
        {
            m_name = name;
            m_id = id;
        }

        public string Name
        {
            get
            {
                return m_name;
            }

            set
            {
                m_name = value;
            }
        }

        public uint ID
        {
            get
            {
                return m_id;
            }

            set
            {
                m_id = value;
            }
        }
    }

    internal class Register
    {
        private string m_name;
        private uint m_addr;
        private ushort m_mask;

        public Register(string name, uint address, ushort mask)
        {
            m_name = name;
            m_addr = address;
            m_mask = mask;
        }

        public string Name
        {
            get
            {
                return m_name;
            }
        }

        public uint Address
        {
            get
            {
                return m_addr;
            }
        }

        public ushort Mask
        {
            get
            {
                return m_mask;
            }
        }
    }

    internal class NodeDesc
    {
        private string m_name = "N/A";
        private ManagedPGRGuid m_guid;

        public NodeDesc()
        {
            m_guid = new ManagedPGRGuid();
        }

        public string Name
        {
            get
            {
                return m_name;
            }

            set
            {
                m_name = value;
            }
        }

        public ManagedPGRGuid Guid
        {
            get
            {
                return m_guid;
            }

            set
            {
                m_guid = value;
            }
        }
    }
}