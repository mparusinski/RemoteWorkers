/* 

RwWorkerAddedEvent.cc: Worker added event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwWorkerAddedEvent.h"

namespace RwHistory {

RwWorkerAddedEvent::RwWorkerAddedEvent(const RwWorker::RwWorkerPtr& worker)
{
	m_generated = false;
	m_subClassType = RW_WORKER_ADDED_EVENT;
	m_eventDate = QDate::currentDate();
	m_worker = worker;
}

RwEventType::RwEventTypeHandle RwWorkerAddedEvent::create(const RwWorker::RwWorkerPtr& worker)
{
	RwWorkerAddedEvent* ptrToObject = new RwWorkerAddedEvent(worker);
	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwWorkerAddedEvent::generate()
{
	RwEventType* ptrToObject = new RwEventType;
	ptrToObject->copyEssentials(this);
	QString eventDescription = "Worker " + m_worker->getWorkerName() + " has been added";
	ptrToObject->setEventDescription(eventDescription);

	RwEventTypeHandle handle(ptrToObject);
	return handle;
}

}
