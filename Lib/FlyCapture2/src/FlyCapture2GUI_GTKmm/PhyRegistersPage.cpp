//=============================================================================
// Copyright © 2008 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with PGR.
//
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#include "Precompiled.h"
#include "PhyRegistersPage.h"

namespace FlyCapture2
{
	const char* PhyRegistersPage::sk_nodeList = "treeviewNodeList";
	const char* PhyRegistersPage::sk_registerList = "treeviewRegisterList";
	const char* PhyRegistersPage::sk_scrolledWindowRegister = "scrolledwindowRegister";
	const char* PhyRegistersPage::sk_scrolledWindowNode = "scrolledwindowNode";

	const Glib::ustring PhyRegistersPage::sk_nodeColumnName = "Node";
	const Glib::ustring PhyRegistersPage::sk_registerColumnName = "Register";
	const Glib::ustring PhyRegistersPage::sk_valueColumnName = "Value";

	const Glib::ustring sk_card = "Card";
	const Glib::ustring sk_camera = "Camera";

	const unsigned int k_basePage = 0;
	const unsigned int k_portPage = 0;
	const unsigned int k_vendorPage = 1;
	const unsigned int k_totalPortsField = 7;

	const Field k_vendorList[] = {
		{ "Point Grey Research", 0x00B09D },
		{ "Texas Instruments",   0x080028 },
		{ "LSI/Agere Systems",   0x00053D },
		{ "Lucent Technologies", 0x00601D },
		{ "Node",                0x000000 }		// unknown vendor
	};

	const Register k_baseRegisterInfo[] =
	{
		{ "Physical_ID",           0, 0xFC },
		{ "R",                     0, 0x02 },
		{ "PS",                    0, 0x01 },
		{ "RHB",                   1, 0x80 },
		{ "IBR",                   1, 0x40 },
		{ "Gap_count",             1, 0x3F },
		{ "Extended",              2, 0xE0 },
		{ "Total_Ports",		   2, 0x1F },
		{ "Max_speed",             3, 0xE0 },
		{ "Enable_standby",        3, 0x10 },
		{ "Delay",                 3, 0x0F },
		{ "LCtrl",                 4, 0x80 },
		{ "Contender",             4, 0x40 },
		{ "Jitter",                4, 0x38 },
		{ "Pwr_class",             4, 0x07 },
		{ "Watchdog",              5, 0x80 },
		{ "ISBR",                  5, 0x40 },
		{ "Loop",                  5, 0x20 },
		{ "Pwr_fail",              5, 0x10 },
		{ "Timeout",               5, 0x08 },
		{ "Port_event",            5, 0x04 },
		{ "Enab_accel",            5, 0x02 },
		{ "Enab_multi",            5, 0x01 },
		{ "Max_legacy_path_speed", 6, 0xE0 },
		{ "B_link",                6, 0x10 },
		{ "Bridge",                6, 0x0C },
		{ "Page_select",           7, 0xE0 },
		{ "Port_select",           7, 0x0F }
	};

	const Register k_portStatusInfo[] = {
		{ "AStat",                 8,  0xC0 },
		{ "BStat",                 8,  0x30 },
		{ "Child",                 8,  0x08 },
		{ "Connected",             8,  0x04 },
		{ "Receive_OK",            8,  0x02 },
		{ "Disabled",              8,  0x01 },
		{ "Negotiated_speed",      9,  0xE0 },
		{ "Int_enable",            9,  0x10 },
		{ "Fault",                 9,  0x08 },
		{ "Standby_fault",         9,  0x04 },
		{ "Disable_scrambler",     9,  0x02 },
		{ "Beta_mode_only_port",   9,  0x01 },
		{ "DC_connected",          10, 0x80 },
		{ "Max_port_speed",        10, 0x70 },
		{ "LPP",                   10, 0x08 },
		{ "Cable_speed",           10, 0x07 },
		{ "Connection_unreliable", 11, 0x80 },
		{ "Beta_mode",             11, 0x08 },
		{ "Port_error",            12, 0xFF },
		{ "Loop_diable",           13, 0x04 },
		{ "In_standby",            13, 0x02 },
		{ "Hard_disable",          13, 0x01 }
	};

	PhyRegistersPage::PhyRegistersPage( CameraBase* pCamera, Glib::RefPtr<Gnome::Glade::Xml> refXml ) : BasePage( pCamera, refXml )
	{
	}

	PhyRegistersPage::~PhyRegistersPage()
	{
	}

	void PhyRegistersPage::GetWidgets()
	{
		m_refXml->get_widget( sk_nodeList, m_pNodeList );
		m_refXml->get_widget( sk_registerList, m_pRegisterList );

		m_refXml->get_widget(sk_scrolledWindowNode, m_pScrolledWindowNode);
		m_refXml->get_widget(sk_scrolledWindowRegister, m_pScrolledWindowRegister);

		m_pScrolledWindowNode->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		m_pScrolledWindowRegister->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);


		m_nodeColumnRecord.add( m_nodeColumn );
		m_registerColumnRecord.add( m_registerColumn );
		m_registerColumnRecord.add( m_valueColumn );

		// Create node and register model
		m_refNodeModel = Gtk::TreeStore::create(m_nodeColumnRecord);
		m_pNodeList->set_model( m_refNodeModel );

		m_refRegisterModel = Gtk::ListStore::create( m_registerColumnRecord );
		m_pRegisterList->set_model( m_refRegisterModel );

		m_pNodeList->append_column(sk_nodeColumnName, m_nodeColumn);
		m_pRegisterList->append_column(sk_registerColumnName, m_registerColumn);
		m_pRegisterList->append_column(sk_valueColumnName, m_valueColumn);

		m_refTreeSelection = m_pNodeList->get_selection();
	}

	void PhyRegistersPage::UpdateWidgets()
	{
		BusManager busMgr;
		unsigned int numCards, numCameras;
		Error error;

		// get number of cameras
		error = busMgr.GetNumOfCameras(&numCameras);
		if (error != PGRERROR_OK)
		{
			printf("Error - GetNumOfCameras\n");
		}

		// get number of cards
		error = busMgr.GetNumOfDevices(&numCards);
		if (error != PGRERROR_OK)
		{
			printf("Error - GetNumOfDevices\n");
		}

		//update model with register/ports for each detected node
		unsigned int count = 0;
		Glib::ustring type = sk_card;
		PGRGuid cardGuid, camGuid, prevGuid;

		for (unsigned int i = 0; i < numCards; i++)
		{
			error = busMgr.GetDeviceFromIndex(i, &cardGuid);
			updateModel(&count, &cardGuid, &type);
		}

		type = sk_camera;
		for (unsigned int i = 0; i < numCameras; i++)
		{
			error = busMgr.GetCameraFromIndex(i, &camGuid);
			updateModel(&count, &camGuid, &type);
		}
	}

	void PhyRegistersPage::updateModel(unsigned int* count, PGRGuid* guid, Glib::ustring* type)
	{
		// read vendorID, add to list
		Field vendorid;
		if(!getVendorID(guid, &vendorid))
			return;

		// construct node string
		Glib::ustring vendorName = Glib::ustring::compose("%1. %2 (%3)", (*count)++, vendorid.name, *type );

		// insert into model
		Gtk::TreeModel::Row row = *(m_refNodeModel->append());
		row[m_nodeColumn] = vendorName;

		NodeDesc nodeDesc;
		nodeDesc.guid = *guid;
		nodeDesc.name = vendorName;
		m_NodeDescList.push_back(nodeDesc);

		// get number of ports
		unsigned int numPorts = 0;
		getNumberOfPorts(guid, &numPorts);

		// add base register heading
		Gtk::TreeModel::Row childrow = *(m_refNodeModel->append(row.children()));
		childrow[m_nodeColumn] = "Base Registers";

		// add port headings
		char tempBuffer[64];
		for (unsigned int t = 0; t < numPorts; t++)
		{
			sprintf(tempBuffer, "Port %d", t);
			childrow = *(m_refNodeModel->append(row.children()));
			childrow[m_nodeColumn] = tempBuffer;
		}
	}

	void PhyRegistersPage::resetRegisterPane()
	{
		m_refRegisterModel->clear();
	}

	bool PhyRegistersPage::getVendorID(PGRGuid* guid, Field* vendorID)
	{
		BusManager busMgr;
		unsigned int regVal = 0;
		unsigned int vendorVal = 0;

		// read vendor id registers
		for (int i = 10; i <= 12; i++)
		{
			Error error = busMgr.ReadPhyRegister(*guid, k_vendorPage, 0, i, &regVal);
			if(error != PGRERROR_OK)
			{
				return false;
			}
			else
			{
				vendorVal = (vendorVal << 8) | regVal;
			}
		}

		unsigned int count = 0;

		// lookup vendor id in string table
		while (k_vendorList[count].id != 0)
		{
			if (vendorVal == k_vendorList[count].id)
				break;
			count++;
		}

		vendorID->id = vendorVal;
		vendorID->name = k_vendorList[count].name;
		return true;
	}

	void PhyRegistersPage::getNumberOfPorts(PGRGuid* guid, unsigned int* numPorts)
	{
		BusManager busMgr;
		unsigned int regVal;

		// read totalPorts field
		Error error = busMgr.ReadPhyRegister(*guid, k_basePage, 0, k_baseRegisterInfo[k_totalPortsField].addr, &regVal);
		getField(&(k_baseRegisterInfo[k_totalPortsField]), &regVal, numPorts);
	}

	void PhyRegistersPage::getField(const Register* field, unsigned int* regVal, unsigned int* fieldVal)
	{
		unsigned int shiftCount = 0;
		unsigned int tempMask = field->mask;

		while ((tempMask & 0x01) == 0)
		{
			tempMask = tempMask >> 1;
			shiftCount++;
		}

		*fieldVal = (*regVal & field->mask) >> shiftCount;
	}

	void PhyRegistersPage::AttachSignals()
	{
		m_refTreeSelection->signal_changed().connect(
				sigc::mem_fun(*this, &PhyRegistersPage::OnNodeChanged));
	}

	void PhyRegistersPage::OnNodeChanged()
	{
		std::vector<Gtk::TreeModel::Path> path = m_refTreeSelection->get_selected_rows();

		if(path.empty())
			return;

		std::vector<Gtk::TreeModel::Path>::iterator pathIter;
		pathIter = path.begin();
		Glib::ustring strText = (*pathIter).to_string();

		resetRegisterPane();

		PGRGuid guid;
		unsigned int port;

		if(getNodeFromPath(&strText, &guid, &port))
		{
			populateRegisterPage(&guid, port);
		}
		else
		{
			// reset register pane
			resetRegisterPane();
		}
	}

	void PhyRegistersPage::populateRegisterPage(PGRGuid* guid, unsigned int port)
	{
		Gtk::ListStore::Row row;
		BusManager busMgr;
		std::vector<Register>* regVector;

		if (port == 0)	// base register
			regVector = new std::vector<Register>(k_baseRegisterInfo, k_baseRegisterInfo + sizeof(k_baseRegisterInfo) / sizeof(Register));
		else
		{
			// port status register
			regVector = new std::vector<Register>(k_portStatusInfo, k_portStatusInfo + sizeof(k_portStatusInfo) / sizeof(Register));
			port--;  // port numbers start at 0
		}

		// populate register page
		unsigned int regVal;
		unsigned int fieldVal;
		bool isFirst = true;
		std::vector<Register>::iterator iter;
		unsigned int currAddr = 0, prevAddr = 0;

		for(iter = regVector->begin(); iter != regVector->end(); iter++)
		{
			prevAddr = currAddr;
			currAddr = (*iter).addr;

			if (isFirst || currAddr != prevAddr)
			{
				busMgr.ReadPhyRegister(*guid, 0, port, (*iter).addr, &regVal);
				isFirst = false;
			}

			// get field
			getField(& (*iter), &regVal, &fieldVal);

			// insert into page
			row = *(m_refRegisterModel->append());
			row[m_registerColumn] = (*iter).name;
			row[m_valueColumn] = fieldVal;
		}
	}

	bool PhyRegistersPage::getNodeFromPath(Glib::ustring* strText, PGRGuid* guid, unsigned int* port)
	{
		size_t pos = strText->find(':');

		if(pos == Glib::ustring::npos)
		{
			return false;
		}

		Glib::ustring nodeNum = strText->substr(0, pos);
		Glib::ustring statusRegister = strText->substr(pos+1);

		unsigned int node = atoi(nodeNum.c_str());
		*port = atoi(statusRegister.c_str());

		*guid = m_NodeDescList[node].guid;
		return true;
	}
}
