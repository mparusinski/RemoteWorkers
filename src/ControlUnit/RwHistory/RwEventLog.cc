/* 

RwEventLog.h: Container class for a list of events

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwEventLog.h"

#include <QtAlgorithms>

#include "RwServerStartedEvent.h"
#include "RwServerStoppedEvent.h"
#include "RwWorkerAddedEvent.h"
#include "RwWorkerRemovedEvent.h"
#include "RwWorkerExecutionEvent.h"

namespace RwHistory {

RwEventLog::RwEventLog()
{

}

RwEventLog::~RwEventLog()
{

}

RwEventLog* RwEventLog::getInstance()
{
	static RwEventLog* instance = 0;
	if (instance == 0)
	{
		instance = new RwEventLog;
	}
	return instance;
}

void RwEventLog::registerEvent(const RwEvent& event)
{
	if (event > m_eventList.last())
	{
		m_eventList.push_back(event);
	}
	else
	{
		EventListType::iterator position = qLowerBound(m_eventList.begin(), m_eventList.end(), event);
		m_eventList.insert(position, event); // ensures the list is always in order
	}
}

void RwEventLog::serverStarted()
{
	RwEvent event(RwServerStartedEvent::create());
	registerEvent(event);
}

void RwEventLog::serverStopped()
{
	RwEvent event(RwServerStoppedEvent::create());
	registerEvent(event);
}

void RwEventLog::workerAdded(RwWorker::RwWorkerPtr& worker)
{
	RwEvent event(RwWorkerAddedEvent::create(worker));
	registerEvent(event);
}

void RwEventLog::workerRemoved(RwWorker::RwWorkerPtr& worker)
{
	RwEvent event(RwWorkerRemovedEvent::create(worker));
	registerEvent(event);
}

void RwEventLog::workerExecutedCommand(RwWorker::RwWorkerPtr& worker, RwCommand::RwCommandPtr& command)
{
	RwEvent event(RwWorkerExecutionEvent::create(worker, command));
	registerEvent(event);
}

void RwEventLog::generateAll()
{
	EventListType::iterator iter;
	for (iter = m_eventList.begin(); iter != m_eventList.end(); ++iter)
	{
		iter->generateEvent();
	}
}

}
