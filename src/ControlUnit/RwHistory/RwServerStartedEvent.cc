/* 

RwServerStartedEvent.cc: A server started event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwServerStartedEvent.h"

namespace RwHistory {

RwServerStartedEvent::RwServerStartedEvent()
{
	m_generated = false;
	m_subClassType = RW_SERVER_STARTED_EVENT;
	m_eventDate = QDate::currentDate();
}

RwEventType::RwEventTypeHandle RwServerStartedEvent::create()
{
	RwServerStartedEvent* ptrToObject = new RwServerStartedEvent;
	RwEventType::RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwServerStartedEvent::generate()
{
	RwEventType* ptrToCompressed = new RwEventType;
	ptrToCompressed->copyEssentials(this);
	QString description = "RemoteWorkers server has started";
	ptrToCompressed->setEventDescription(description);
	RwEventType::RwEventTypeHandle handle(ptrToCompressed);
	return handle;
}

}
