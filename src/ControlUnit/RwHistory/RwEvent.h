/* 

RwEvent.h: Class capturing a server event. Will be used for logging activity

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/08/2012.

*/

#ifndef _RWHISTORY_RWEVENT_H_
#define _RWHISTORY_RWEVENT_H_

#include <QSharedPointer>
#include <QDate>

#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwCommand.h"

namespace RwHistory {

	class RwEvent {

	public:
		typedef enum {
			RW_EVENT_WORKER_EXECUTED,
			RW_EVENT_WORKER_ADDED,
			RW_EVENT_WORKER_REMOVED,
			RW_EVENT_SERVER_STARTED,
			RW_EVENT_SERVER_STOPPED
		} EventType;

		typedef struct {
			QSharedPointer<RwWorkerInterface::RwWorker>  m_worker;
			QSharedPointer<RwWorkerInterface::RwCommand> m_command;
			QDate m_executionDate;
		} EventContainerExecutionType;

		RwEvent();
		virtual ~RwEvent();

	private:

		EventType m_eventVarType;
	};

}

#endif // _RWHISTORY_RWEVENT_H_
