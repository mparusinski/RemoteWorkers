/* 

RwWorkerExecutionEvent.cc: Worker executed a command event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwWorkerExecutionEvent.h"

namespace RwHistory {

RwWorkerExecutionEvent::RwWorkerExecutionEvent(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command)
{
	m_generated = false;
	m_subClassType = RW_WORKER_EXECUTION_EVENT;
	m_eventDate = QDate::currentDate();
	m_worker = worker;
	m_command = command;
}

RwEventType::RwEventTypeHandle RwWorkerExecutionEvent::create(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command)
{
	RwWorkerExecutionEvent* ptrToObject = new RwWorkerExecutionEvent(worker, command);
	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwWorkerExecutionEvent::generate()
{
	RwEventType* ptrToObject = new RwEventType;
	ptrToObject->copyEssentials(this);
	QString description = "Worker " + m_worker->getWorkerName() + " executed the following command: "
			+ m_command->getOrder() + " with arguments " + m_command->getArguments().join(" ");
	ptrToObject->setEventDescription(description);
	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

}
