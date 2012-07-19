/* 

RwEventLog.h: A history of events that have happened

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#ifndef _RWHISTORY_RWEVENTLOG_H_
#define _RWHISTORY_RWEVENTLOG_H_

#include "RwEvent.h"

#include <QList>
#include <QDate>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwCommand.h"

using namespace RwWorkerInterface;

namespace RwHistory {

class RwEventLog
{
public:
	typedef QList<RwEvent> EventListType;

	virtual ~RwEventLog();

	static RwEventLog* getInstance();

	void registerEvent(const RwEvent& event);

	void serverStarted();

	void serverStopped();

	void workerAdded(const RwWorker::RwWorkerPtr& worker);

	void workerRemoved(const RwWorker::RwWorkerPtr& worker);

	void workerExecutedCommand(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command);

	void generateAll();

private:
	RwEventLog();
	DISALLOW_COPY_AND_ASSIGN(RwEventLog);
	EventListType m_eventList;
};

}

#endif // _RWHISTORY_RWEVENTLOG_H_
