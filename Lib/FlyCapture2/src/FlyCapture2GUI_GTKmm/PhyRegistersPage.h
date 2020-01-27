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

#ifndef _PHYREGISTERSPAGE_H_
#define _PHYREGISTERSPAGE_H_

#include "BasePage.h"

namespace FlyCapture2
{
	typedef struct FieldType
	{
		Glib::ustring name;
		unsigned int id;
	} Field;

	typedef struct RegisterType
	{
		char name[64];
		unsigned int addr;
		unsigned char mask;
	} Register;

	typedef struct NodeDescType
	{
		PGRGuid guid;
		Glib::ustring name;
	} NodeDesc;


	class PhyRegistersPage : public BasePage
	{
		public:
			/**
			 * Constructor. Initialize the object with the specified parameters.
			 *
			 * @param pCamera Pointer to a valid Camera object.
			 * @param refXml RefPtr to a Glade XML object.
			 */
			PhyRegistersPage( CameraBase* pCamera, Glib::RefPtr<Gnome::Glade::Xml> refXml );

			/** Destructor. */
			~PhyRegistersPage();

			/** Update widgets on page. */
			void UpdateWidgets();

			void AttachSignals();
			void OnNodeChanged();

		protected:
			/** Load widgets. */
			void GetWidgets();

		private:
			std::vector<NodeDesc> m_NodeDescList;
			Gtk::TreeView* m_pNodeList;
			Gtk::TreeView* m_pRegisterList;
			Gtk::ScrolledWindow* m_pScrolledWindowNode;
			Gtk::ScrolledWindow* m_pScrolledWindowRegister;

			Glib::RefPtr<Gtk::ListStore> m_refRegisterModel;
			Glib::RefPtr<Gtk::TreeStore> m_refNodeModel;
			Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;

			Gtk::TreeModel::ColumnRecord m_nodeColumnRecord;
			Gtk::TreeModelColumn<Glib::ustring> m_nodeColumn;

			Gtk::TreeModel::ColumnRecord m_registerColumnRecord;
			Gtk::TreeModelColumn<Glib::ustring> m_registerColumn;
			Gtk::TreeModelColumn<unsigned int> m_valueColumn;

			bool getVendorID(PGRGuid* guid, Field* vendorID);
			void getNumberOfPorts(PGRGuid* guid, unsigned int* numPorts);
			void getField(const Register* field, unsigned int* regVal, unsigned int* fieldVal);
			bool getNodeFromPath(Glib::ustring* strText, PGRGuid* guid, unsigned int* port);
			void populateRegisterPage(PGRGuid* guid, unsigned int port);
			void resetRegisterPane();
			void updateModel(unsigned int* count, PGRGuid* guid, Glib::ustring* type);

			static const char* sk_nodeList;
			static const char* sk_registerList;
			static const char* sk_scrolledWindowRegister;
			static const char* sk_scrolledWindowNode;

			static const Glib::ustring sk_nodeColumnName;
			static const Glib::ustring sk_registerColumnName;
			static const Glib::ustring sk_valueColumnName;
	};
}

#endif // _PHYREGISTERSPAGE_H_
