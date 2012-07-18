/* 

RwWorkerAddedEvent.cc: Worker added event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwWorkerAddedEvent.h"

namespace RwHistory {

RwEventType::RwEventTypeHandle RwWorkerAddedEvent::create(const RwWorker::RwWorkerPtr& worker)
{
	RwWorkerAddedEvent* ptrToObject = new RwWorkerAddedEvent;
	ptrToObject->m_worker = worker;
	ptrToObject->m_subClassType = RW_WORKER_ADDED_EVENT;
	ptrToObject->m_eventDate = QDate::currentDate();

	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwWorkerAddedEvent::generate()
{
	RwEventType* ptrToObject = new RwEventType;
	ptrToObject->copyEssentials(this);
	ptrToObject->m_eventDescription = "Worker " + m_worker->getWorkerName() + " has been added\n";

	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

}
