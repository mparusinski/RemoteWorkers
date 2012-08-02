/* 

EventLogTest.cc: Test the features of RwHistory::RwEventLog

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 20/07/2012

*/

#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <QString>
#include <QDateTime>

#include "RwHistory/RwEventLog.h"
#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwUtils/RwLog/RwCommon.h"

#define NUM_OF_EVENTS 1000

using namespace RwWorkerInterface;
using namespace RwHistory;
using namespace RwUtils::RwLog;

void registerRandomEvent(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command)
{
	const int randomInt = rand() % 5;
	switch (randomInt)
	{
	case 0:
		RwEventLog::getInstance()->serverStarted();
		break;
	case 1:
		RwEventLog::getInstance()->serverStopped();
		break;
	case 2:
		RwEventLog::getInstance()->workerAdded(worker);
		break;
	case 3:
		RwEventLog::getInstance()->workerRemoved(worker);
		break;
	case 4:
		RwEventLog::getInstance()->workerExecutedCommand(worker, command);
		break;
	default: // should not happen
		break;

	}
}

void generateEvents(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command)
{
	for (int i = 0; i < NUM_OF_EVENTS; ++i)
	{
		registerRandomEvent(worker, command);
	}
}

void displayEvents()
{
	RwEventLog::EventListType& events = RwEventLog::getInstance()->getEventList();
	const int size = events.size();
	for (int i = 0; i < size; ++i)
	{
		RwEvent& event = events[i];
		const QString description = event.description();
		const QDateTime& date = event.eventDate();
		rwInfo() << date.toString() << " " << description << endLine();
	}
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	RwMessagingManager::getInstance()->turnAllOn();

	RwWorker::RwWorkerPtr worker;
	const QStringList& availableWorkers = RwManagement::getInstance()->scanAvailableWorkers();
    
    Q_ASSERT(availableWorkers.size() > 0);
    
	if (RwManagement::getInstance()->createWorker(availableWorkers[0], worker) != RW_NO_ERROR)
    {
        rwError() << "Worker not available" << endLine();
        return -1;
    }

	RwCommand::RwCommandPtr command(new RwCommand("GenericCommand", QStringList()));

	// GENERATING A LOT OF EVENTS
	generateEvents(worker, command);

	// GENERATING EVENTs
	RwEventLog::getInstance()->generateAll();

	// DISPLAYING
	displayEvents();

	return 0;
}
