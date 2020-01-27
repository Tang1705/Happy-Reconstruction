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

#include "Precompiled.h"
#include "EventStatisticsWindow.h"

using namespace FlyCapture2;

const char* EventStatisticsWindow::sk_treeviewEventStatistics = "treeviewEventStatistics";

EventStatisticsWindow::EventStatisticsWindow(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade) : Gtk::Window(cobject)
{
	m_refXml = refGlade;

	m_timeIntervals.push_back(10);
	m_timeIntervals.push_back(30);
	m_timeIntervals.push_back(60);
	m_timeIntervals.push_back(300);

	m_eventTypeMap.clear();
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(TOTAL_NUMBER_OF_FRAMES, "Total number of frames"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(IMAGE_CONSISTENCY_ERRORS, "Image consistency errors"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(IMAGE_CONVERSION_ERRORS, "Image conversion errors"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(TRANSMIT_FAILURES, "Transmit failures"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(RECOVERY_COUNT, "Recovery count"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(SKIPPED_IMAGES, "Skipped images"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(NUMBER_OF_BUS_RESETS, "Number of bus resets"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(NUMBER_OF_BUS_ARRIVALS, "Number of bus arrivals"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(NUMBER_OF_BUS_REMOVALS, "Number of bus removals"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(NUMBER_OF_PACKET_RESEND_REQUESTED, "Packet resend requested"));
	m_eventTypeMap.insert(std::pair<EventType, Glib::ustring>(NUMBER_OF_PACKET_RESEND_RECEIVED, "Packet resend received"));

	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(TOTAL_NUMBER_OF_FRAMES, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(IMAGE_CONSISTENCY_ERRORS, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(IMAGE_CONVERSION_ERRORS, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(TRANSMIT_FAILURES, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(RECOVERY_COUNT, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(SKIPPED_IMAGES, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(NUMBER_OF_BUS_RESETS, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(NUMBER_OF_BUS_ARRIVALS, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(NUMBER_OF_BUS_REMOVALS, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(NUMBER_OF_PACKET_RESEND_REQUESTED, std::deque<time_t>()));
	m_eventTimelines.insert(std::pair<EventType, std::deque<time_t> >(NUMBER_OF_PACKET_RESEND_RECEIVED, std::deque<time_t>()));


	const unsigned int k_numIntervals = m_timeIntervals.size();

	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(TOTAL_NUMBER_OF_FRAMES, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(IMAGE_CONSISTENCY_ERRORS, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(IMAGE_CONVERSION_ERRORS, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(TRANSMIT_FAILURES, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(RECOVERY_COUNT, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(SKIPPED_IMAGES, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(NUMBER_OF_BUS_RESETS, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(NUMBER_OF_BUS_ARRIVALS, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(NUMBER_OF_BUS_REMOVALS, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(NUMBER_OF_PACKET_RESEND_REQUESTED, std::vector<unsigned int>(k_numIntervals, 0)));
	m_eventTotalCounters.insert(std::pair<EventType, std::vector<unsigned int> >(NUMBER_OF_PACKET_RESEND_RECEIVED, std::vector<unsigned int>(k_numIntervals, 0)));
	time(&m_lastUpdateTime);

	Initialize();
}

void EventStatisticsWindow::LoadIcon()
{
	m_iconPixBuf = Gdk::Pixbuf::create_from_inline( sizeof(PGRIcon), PGRIcon, false );
}

bool EventStatisticsWindow::Initialize()
{
	GetWidgets();
	AttachSignals();

	// Load the PGR icon
	LoadIcon();
	set_default_icon( m_iconPixBuf );

	return true;
}

void EventStatisticsWindow::GetWidgets()
{
	m_refXml->get_widget( sk_treeviewEventStatistics, m_pTreeviewEventStatistics );
	m_refListStoreEventStatistics = Gtk::ListStore::create(m_eventStatisticsColumns);
	m_pTreeviewEventStatistics->set_model( m_refListStoreEventStatistics );
	CreateTreeViewColumnHeaders();
	CreateTreeViewRows();
}

void EventStatisticsWindow::AttachSignals()
{
	//Glib::signal_timeout().connect(sigc::mem_fun(*this, &EventStatisticsWindow::OnTimer), 1000);
}

void EventStatisticsWindow::CreateTreeViewColumnHeaders()
{
	m_pTreeviewEventStatistics->append_column( "Event Type", m_eventStatisticsColumns.m_colEventTypeString );
	m_pTreeviewEventStatistics->append_column( "Last 10s", m_eventStatisticsColumns.m_colTimeslice1 );
	m_pTreeviewEventStatistics->append_column( "Last 30s", m_eventStatisticsColumns.m_colTimeslice2 );
	m_pTreeviewEventStatistics->append_column( "Last 1m", m_eventStatisticsColumns.m_colTimeslice3 );
	m_pTreeviewEventStatistics->append_column( "Last 5m", m_eventStatisticsColumns.m_colTimeslice4 );
}

void EventStatisticsWindow::CreateTreeViewRows()
{
	std::map<EventType, Glib::ustring>::iterator it;
	for (it = m_eventTypeMap.begin(); it != m_eventTypeMap.end(); it++)
	{
		Gtk::TreeModel::Row row = *(m_refListStoreEventStatistics->append());
		row[m_eventStatisticsColumns.m_colEventTypeString] = it->second;
		row[m_eventStatisticsColumns.m_colTimeslice1] = 0;
		row[m_eventStatisticsColumns.m_colTimeslice2] = 0;
		row[m_eventStatisticsColumns.m_colTimeslice3] = 0;
		row[m_eventStatisticsColumns.m_colTimeslice4] = 0;
		row[m_eventStatisticsColumns.m_colEventType] = it->first;
	}
}

void EventStatisticsWindow::AddEvent( EventType eventType )
{
	time_t currentTime;
	time(&currentTime);

	Glib::Mutex::Lock lock(m_eventTimelineMutex);
	m_eventTimelines[eventType].push_back(currentTime);
}

void EventStatisticsWindow::Update()
{
	if (!this->is_visible())
	{
		return;
	}

	Glib::Mutex::Lock lock(m_eventTimelineMutex, Glib::NOT_LOCK );
	if (!lock.try_acquire())
	{
		return;
	}

	time_t nowTime;
	time(&nowTime);

	if (difftime(nowTime, m_lastUpdateTime) < 1)
	{
		return;
	}

	m_lastUpdateTime = nowTime;

	// Clear the total counters
	std::vector<unsigned int> blankTemp = std::vector<unsigned int>(m_timeIntervals.size(), 0);
	m_eventTotalCounters[TOTAL_NUMBER_OF_FRAMES] = blankTemp;
	m_eventTotalCounters[IMAGE_CONSISTENCY_ERRORS] = blankTemp;
	m_eventTotalCounters[IMAGE_CONVERSION_ERRORS] = blankTemp;
	m_eventTotalCounters[TRANSMIT_FAILURES] = blankTemp;
	m_eventTotalCounters[RECOVERY_COUNT] = blankTemp;
	m_eventTotalCounters[SKIPPED_IMAGES] = blankTemp;
	m_eventTotalCounters[NUMBER_OF_BUS_RESETS] = blankTemp;
	m_eventTotalCounters[NUMBER_OF_BUS_ARRIVALS] = blankTemp;
	m_eventTotalCounters[NUMBER_OF_BUS_REMOVALS] = blankTemp;
	m_eventTotalCounters[NUMBER_OF_PACKET_RESEND_RECEIVED] = blankTemp;
	m_eventTotalCounters[NUMBER_OF_PACKET_RESEND_REQUESTED] = blankTemp;

	// Iterate through each timeline
	std::map<EventType, std::deque<time_t> >::iterator currTimeline;
	for (currTimeline = m_eventTimelines.begin();
			currTimeline != m_eventTimelines.end();
			currTimeline++)
	{
		// Parse each time entry in a timeline
		std::deque<time_t>::iterator currTime;
		for (currTime = currTimeline->second.begin();
				currTime != currTimeline->second.end();)
		{
			const double timeDifference = difftime(nowTime, *currTime);

			const unsigned int k_maxNumSeconds = m_timeIntervals.back();
			if (timeDifference > k_maxNumSeconds)
			{
				// This event is too old, get rid of it
				currTimeline->second.pop_front();

				// Reset the iterator to the new start point
				currTime = currTimeline->second.begin();
				continue;
			}
			else
			{
				// Event is new enough to be recorded in one of the event counters
				for (int currTimesliceIdx = 0;
						currTimesliceIdx < m_timeIntervals.size();
						currTimesliceIdx++)
				{
					if (timeDifference <= m_timeIntervals[currTimesliceIdx])
					{
						// Add it to the event counter
						const EventType currEventType = currTimeline->first;
						int currCounterVal = (m_eventTotalCounters[currEventType])[currTimesliceIdx];
						(m_eventTotalCounters[currEventType])[currTimesliceIdx] = currCounterVal + 1;
					}
				}

				// Move to the next entry in the timeline
				currTime++;
			}
		}
	}

	// Completed calculating event totals
	// Iterate and update rows
	Gtk::TreeModel::Children listChildren = m_refListStoreEventStatistics->children();
	for (Gtk::TreeModel::Children::iterator currChild = listChildren.begin();
			currChild != listChildren.end();
			currChild++)
	{
		Gtk::TreeModel::Row currRow = *currChild;

		const EventType currEventType = currRow[m_eventStatisticsColumns.m_colEventType];
		const std::vector<unsigned int> currTotalCounter = m_eventTotalCounters[currEventType];
		currRow[m_eventStatisticsColumns.m_colTimeslice1] = currTotalCounter[0];
		currRow[m_eventStatisticsColumns.m_colTimeslice2] = currTotalCounter[1];
		currRow[m_eventStatisticsColumns.m_colTimeslice3] = currTotalCounter[2];
		currRow[m_eventStatisticsColumns.m_colTimeslice4] = currTotalCounter[3];
	}
}

void EventStatisticsWindow::Reset()
{
	// TODO: Clear timeline and event totals
}
