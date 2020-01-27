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

#include "stdafx.h"
#include "EventStatDialog.h"

IMPLEMENT_DYNAMIC(EventStatDialog, CDialog)

	EventStatDialog::EventStatDialog(CWnd* pParent /*=NULL*/)
: CDialog(EventStatDialog::IDD, pParent)
{
	m_timer = NULL;
	m_hasBadEventRecently = false;
	m_turnOnEventCollection = true;
}

EventStatDialog::~EventStatDialog()
{
}

void EventStatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EVENT, m_eventTable);
	DDX_Control(pDX, IDC_COMBO_TIMESLICE, m_timeSliceComboBox);
	DDX_Control(pDX, IDC_TURN_ON, m_eventCollectionCheckBox);
}


	BEGIN_MESSAGE_MAP(EventStatDialog, CDialog)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_TIMESLICE, &EventStatDialog::OnCbnSelchangeComboTimeslice)
	ON_BN_CLICKED(IDC_TURN_ON, &EventStatDialog::OnBnClickedTurnOn)
END_MESSAGE_MAP()


	// EventStatDialog message handlers

BOOL EventStatDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_eventCollectionCheckBox.SetCheck(m_turnOnEventCollection?TRUE:FALSE);

	m_eventTable.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	if( m_timer == NULL )
	{
		m_timer = ::SetTimer( m_hWnd, NULL, sk_dataRefreshDelay, (TIMERPROC) NULL );
	}

	LVCOLUMN lvColumn;
	CRect tableRect;
	m_eventTable.GetWindowRect(&tableRect);
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvColumn.fmt = LVCFMT_CENTER;

	//set type name header
	static const int sk_typeNameWidth = 150;
	lvColumn.pszText = "Event Type";
	lvColumn.cx = sk_typeNameWidth;
	m_eventTable.InsertColumn(0, &lvColumn);

	//set counter header
	lvColumn.pszText = "Counter";
	lvColumn.cx = (tableRect.Width()- sk_typeNameWidth - 3) / (sk_numOfColumns);
	for (int i = 0; i < sk_numOfColumns; i++)
	{
		m_eventTable.InsertColumn(i+1, &lvColumn);
	}

	for(int i = 0; i < NUMBER_OF_EVENT_TYPES;i++)
	{
		char buff[128];
		GetEventTypeString((EventType)i, buff);
		m_eventTable.InsertItem(i,buff);
		m_numOfRemovedEvents[i] = 0;
	}

	InitializeColumns();
	UpdateEventsData();
	return TRUE;  // return TRUE unless you set the focus to a control

}

void EventStatDialog::GetEventTypeString(EventType eventType, char* pResultString)
{
	switch( eventType )
	{
		case TOTAL_NUMBER_OF_FRAMES:
			strcpy( pResultString, "Total number of frames" ); break;
		case IMAGE_CONSISTENCY_ERRORS:
			strcpy( pResultString, "Image consistency errors" ); break;
		case IMAGE_CONVERSION_ERRORS:
			strcpy( pResultString, "Image conversion errors" ); break;
		case TRANSMIT_FAILURES:
			strcpy( pResultString, "Transmit failures" ); break;
		case RECOVERY_COUNT:
			strcpy( pResultString, "Recovery count (camera)" ); break;
		case LINKER_ERRORS:
			strcpy( pResultString, "Recovery count (host)" ); break;
		case SKIPPED_IMAGES:
			strcpy( pResultString, "Skipped images" ); break;
		case NUMBER_OF_BUS_RESETS:
			strcpy( pResultString, "Number of bus resets" ); break;
		case NUMBER_OF_BUS_ARRIVALS:
			strcpy( pResultString, "Number of bus arrivals"  ); break;
		case NUMBER_OF_BUS_REMOVALS:
			strcpy( pResultString,  "Number of bus removals"  ); break;
		case NUMBER_OF_PACKET_RESEND_REQUESTED:
			strcpy( pResultString, "Number of packet resend requested"  ); break;
		case NUMBER_OF_PACKET_RESEND_RECEIVED:
			strcpy( pResultString,  "Number of packet resend received"  ); break;
		default:
			strcpy( pResultString,  "Unknown Event" );
#ifdef _DEBUG
			//this should not happen,
			//if you added a new type in event type
			//please add a related event string above the default case.
			DebugBreak();
#endif
			break;
	}
}
int EventStatDialog::GetTime(TimeSliceType timeSliceType)
{
	int result;
	switch( timeSliceType )
	{
		case LAST_10S:
			result = 10;
			break;
		case LAST_30S:
			result = 30;
			break;
		case LAST_1MIN:
			result = 60;
			break;
		case LAST_5MINS:
			result = 300; //is 60 * 5 mins
			break;
		case LAST_10MINS:
			result = 600;  //is 60 * 10 mins
			break;
		case LAST_15MINS:
			result = 900; //is 60 * 15 mins
			break;
		case LAST_SINCE_START:
			result = -1; // Max
			break;
		default:
			result = 0;
#ifdef _DEBUG
			//this should not happen,
			//if you added a new type in time slice type
			//please add a related time in seconds above the default case.
			DebugBreak();
#endif
			break;
	}
	return result;
}
void EventStatDialog::GetTimeString(TimeSliceType timeSliceType, char* pResultString)
{
	switch( timeSliceType )
	{
		case LAST_10S:
			strcpy( pResultString, "Last 10 s" ); break;
		case LAST_30S:
			strcpy( pResultString, "Last 30 s" ); break;
		case LAST_1MIN:
			strcpy( pResultString, "Last 1 min" ); break;
		case LAST_5MINS:
			strcpy( pResultString, "Last 5 mins" ); break;
		case LAST_10MINS:
			strcpy( pResultString, "Last 10 mins" ); break;
		case LAST_15MINS:
			strcpy( pResultString, "Last 15 mins" ); break;
		case LAST_SINCE_START:
			strcpy( pResultString, "Since start" ); break;
		default:
			strcpy( pResultString,  "Unknown" );
#ifdef _DEBUG
			//this should not happen,
			//if you added a new type in time slice type
			//please add a related string above the default case.
			DebugBreak();
#endif
			break;
	}
}
void EventStatDialog::InitializeColumns()
{
	//for now, just hard code, if someone find a better way to deal with them, feel free to change it.
	m_timeSliceComboBox.AddString("Last 10s / 30s / 1min / 5mins");
	m_timeSliceComboBox.AddString("Last 5min / 10mins / 15mins / Since Start");
	m_timeSliceComboBox.SetCurSel(0);
	OnCbnSelchangeComboTimeslice();
	UpdateColumnHeader();
}

void EventStatDialog::UpdateColumnHeader()
{
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_TEXT;
	for (int i = 0; i < sk_numOfColumns; i++)
	{
		char buff[32];
		char headerBuff[64];
		GetTimeString(m_columnsData[i],buff);
		sprintf(headerBuff,"%s", buff);
		lvColumn.pszText = headerBuff;
		m_eventTable.SetColumn(i+1, &lvColumn);
	}

}

void EventStatDialog::AddEvent(EventType eventType)
{
	if (m_turnOnEventCollection == false)
	{
		return;
	}
	time_t currentTime;
	time(&currentTime);
	CSingleLock dataLock(&m_csEventData);
	dataLock.Lock();
	m_data[eventType].push_back(currentTime);
	dataLock.Unlock();
}

void EventStatDialog::UpdateEventsData()
{
	CSingleLock dataLock(&m_csEventData);
	/*if (dataLock.IsLocked())
	  {
	  return;
	  }*/
	dataLock.Lock();
	time_t currentTime;
	time(&currentTime);
	m_hasBadEventRecently = false;
	for(int i = 0; i < NUMBER_OF_EVENT_TYPES;i++)
	{
		int eventCnt[NUMBER_OF_TIME_SLICE_TYPES];
		for (int n=0; n < NUMBER_OF_TIME_SLICE_TYPES; n++)
		{
			eventCnt[n]=0;
		}

		TimeSliceType currentTimeSlice = LAST_15MINS;
		TimeSliceType nextTimeSlice = LAST_10MINS;
		deque<time_t>::iterator eventTime;
		for( eventTime = m_data[i].begin(); eventTime != m_data[i].end();)
		{
			if (m_data[i].empty())
			{
				break;
			}
			double timeDiff = difftime(currentTime,(*eventTime));
			/*
			// hard code version
			if (timeDiff > GetTime(LAST_15MINS))
			{
			//delete this item in the queue
			m_data[i].pop_front();
			eventTime = m_data[i].begin();
			continue;
			}
			else if (timeDiff > GetTime(LAST_10MINS))
			{
			eventCnt[LAST_15MINS]++;
			}
			else if (timeDiff > GetTime(LAST_5MINS))
			{
			eventCnt[LAST_10MINS]++;
			}
			else if (timeDiff > GetTime(LAST_1MIN))
			{
			eventCnt[LAST_5MINS]++;
			}
			else if (timeDiff > GetTime(LAST_30S))
			{
			eventCnt[LAST_1MIN]++;
			}
			else if (timeDiff > GetTime(LAST_10S))
			{
			eventCnt[LAST_30S]++;
			}
			else
			{
			eventCnt[LAST_10S]++;
			}
			*/
			if (timeDiff > GetTime(currentTimeSlice))
			{
				if (currentTimeSlice == LAST_15MINS)
				{
					//delete this item in the queue
					m_data[i].pop_front();
					eventTime = m_data[i].begin();

					// Increment the RemovedEvents counter to
					// keep track of # of removed events
					m_numOfRemovedEvents[i]++;
					continue;
				}
				else
				{
					//do nothing, just skip this
				}
			}
			else if (timeDiff > GetTime(nextTimeSlice))
			{
				eventCnt[currentTimeSlice]++;
			}
			else
			{
				if (nextTimeSlice != LAST_10S)
				{
					currentTimeSlice = nextTimeSlice;
					nextTimeSlice = (TimeSliceType)(nextTimeSlice-1);
					continue;
				}
				else
				{
					eventCnt[LAST_10S]++;
				}
			}
			eventTime++;
		}

		//sum up the number of events
		/*
		//hard code version
		eventCnt[LAST_30S]+=eventCnt[LAST_10S];
		eventCnt[LAST_1MIN]+=eventCnt[LAST_30S];
		eventCnt[LAST_5MINS]+=eventCnt[LAST_1MIN];
		eventCnt[LAST_10MINS]+=eventCnt[LAST_5MINS];
		eventCnt[LAST_15MINS]+=eventCnt[LAST_10MINS];
		*/
		for(unsigned int j=0; j < (unsigned int)NUMBER_OF_TIME_SLICE_TYPES - 1; j++)
		{
			eventCnt[j+1] += eventCnt[j];
		}

		// Adding # of removed events back to "Since Start" time slice category
		eventCnt[NUMBER_OF_TIME_SLICE_TYPES - 1] += m_numOfRemovedEvents[i];

		char buff[32];

		for(int cn = 0; cn < sk_numOfColumns; cn++)
		{
			sprintf(buff,"%d",eventCnt[m_columnsData[cn]]);
			m_eventTable.SetItemText(i, cn + 1, buff);
		}

		// check to see if there is bad event
		if (IsBadEvent((EventType)i)&&eventCnt[0])
		{
			m_hasBadEventRecently = true;
		}
	}
	dataLock.Unlock();
}
bool EventStatDialog::IsBadEvent(EventType eventType)
{
	switch (eventType)
	{
		case TOTAL_NUMBER_OF_FRAMES:
			return false;
		default:
			return true;
	}

}
bool EventStatDialog::HasBadEventRecently()
{
	return m_hasBadEventRecently;
}
void EventStatDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (IsWindowVisible() == TRUE)
	{
		UpdateEventsData();
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL EventStatDialog::DestroyWindow()
{
	if( m_timer != NULL )
	{
		::KillTimer( m_hWnd, m_timer );
	}
	return CDialog::DestroyWindow();
}

void EventStatDialog::OnCbnSelchangeComboTimeslice()
{
	CSingleLock dataLock(&m_csEventData);
	dataLock.Lock();
#ifdef _DEBUG
	//if the number of columns is not 4, you need to manually add data below
	ASSERT(sk_numOfColumns == 4);
#endif
	switch (m_timeSliceComboBox.GetCurSel())
	{
		//for now, just hard code, if someone find a better way to deal with them, feel free to change it.
		case 0:
			m_columnsData[0] = LAST_10S;
			m_columnsData[1] = LAST_30S;
			m_columnsData[2] = LAST_1MIN;
			m_columnsData[3] = LAST_5MINS;
			break;
		case 1:
			m_columnsData[0] = LAST_5MINS;
			m_columnsData[1] = LAST_10MINS;
			m_columnsData[2] = LAST_15MINS;
			m_columnsData[3] = LAST_SINCE_START;
			break;
		default:
			//do nothing
			break;
	}
	UpdateColumnHeader();
	dataLock.Unlock();

}
void EventStatDialog::CleanUpCounters()
{
	CSingleLock dataLock(&m_csEventData);
	dataLock.Lock();
	for(int i = 0; i < NUMBER_OF_EVENT_TYPES;i++)
	{
		m_data[i].clear();
	}
	dataLock.Unlock();
}
void EventStatDialog::OnBnClickedTurnOn()
{
	m_turnOnEventCollection = !m_turnOnEventCollection;
	m_eventCollectionCheckBox.SetCheck(m_turnOnEventCollection?TRUE:FALSE);
}
