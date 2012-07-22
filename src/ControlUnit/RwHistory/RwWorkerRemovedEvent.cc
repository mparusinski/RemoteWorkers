/* 

RwWorkerRemovedEvent.cc: Worker removed Event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwWorkerRemovedEvent.h"

namespace RwHistory {

RwWorkerRemovedEvent::RwWorkerRemovedEvent(const RwWorker::RwWorkerPtr& worker)
{
	m_generated = false;
	m_subClassType = RW_WORKER_REMOVED_EVENT;
	m_worker = worker;
}

RwEventType::RwEventTypeHandle RwWorkerRemovedEvent::create(const RwWorker::RwWorkerPtr& worker)
{
	RwWorkerRemovedEvent* ptrToObject = new RwWorkerRemovedEvent(worker);
	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwWorkerRemovedEvent::generate()
{
	RwEventType* ptrToObject = new RwEventType;
	ptrToObject->copyEssentials(this);
	QString description = "Worker " + m_worker->getWorkerName() + " has been removed";
	ptrToObject->setEventDescription(description);

	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

}
