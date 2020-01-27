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

#ifndef EVENTSTATISTICSWINDOW_H_INCLUDED
#define EVENTSTATISTICSWINDOW_H_INCLUDED

#include "FlyCapture2.h"

enum EventType
{
	TOTAL_NUMBER_OF_FRAMES = 0,
	IMAGE_CONSISTENCY_ERRORS,
	IMAGE_CONVERSION_ERRORS,
	TRANSMIT_FAILURES,
	RECOVERY_COUNT,
	SKIPPED_IMAGES,
	NUMBER_OF_BUS_RESETS,
	NUMBER_OF_BUS_ARRIVALS,
	NUMBER_OF_BUS_REMOVALS,
	NUMBER_OF_PACKET_RESEND_REQUESTED,
	NUMBER_OF_PACKET_RESEND_RECEIVED
};

class EventStatisticsColumns : public Gtk::TreeModelColumnRecord
{
	public:
		Gtk::TreeModelColumn<Glib::ustring> m_colEventTypeString;
		Gtk::TreeModelColumn<unsigned int> m_colTimeslice1;
		Gtk::TreeModelColumn<unsigned int> m_colTimeslice2;
		Gtk::TreeModelColumn<unsigned int> m_colTimeslice3;
		Gtk::TreeModelColumn<unsigned int> m_colTimeslice4;
		Gtk::TreeModelColumn<EventType> m_colEventType;

		EventStatisticsColumns()
		{
			add(m_colEventTypeString);
			add(m_colTimeslice1);
			add(m_colTimeslice2);
			add(m_colTimeslice3);
			add(m_colTimeslice4);
			add(m_colEventType);
		}
};

class EventStatisticsWindow : public Gtk::Window
{
	public:
		EventStatisticsWindow(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
		~EventStatisticsWindow() {}

		void AddEvent(EventType eventType);
		void Update();
		void Reset();

	private:
		Glib::RefPtr<Gnome::Glade::Xml> m_refXml;
		Glib::RefPtr<Gdk::Pixbuf> m_iconPixBuf;

		static const char* sk_treeviewEventStatistics;
		Gtk::TreeView* m_pTreeviewEventStatistics;

		Glib::RefPtr<Gtk::ListStore> m_refListStoreEventStatistics;
		EventStatisticsColumns m_eventStatisticsColumns;

		// String mapping of the event type
		std::map<EventType, Glib::ustring> m_eventTypeMap;

		// Raw storage of event timestamps
		std::map<EventType, std::deque<time_t> > m_eventTimelines;

		// Event totals for each timeslice for each event
		std::map<EventType, std::vector<unsigned int> > m_eventTotalCounters;

		// Available timeslices
		std::vector<unsigned int> m_timeIntervals;

		Glib::Mutex m_eventTimelineMutex;

		time_t m_lastUpdateTime;

		void LoadIcon();
		bool Initialize();
		void GetWidgets();
		void AttachSignals();

		void CreateTreeViewColumnHeaders();
		void CreateTreeViewRows();

		bool OnTimer();
};

#endif // EVENTSTATISTICSWINDOW_H_INCLUDED
