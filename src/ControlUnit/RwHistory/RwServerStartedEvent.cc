/* 

RwServerStartedEvent.cc: A server started event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwServerStartedEvent.h"

namespace RwHistory {

RwEventType::RwEventTypeHandle RwServerStartedEvent::create()
{
	RwServerStartedEvent* ptrToObject = new RwServerStartedEvent;
	ptrToObject->m_subClassType = RW_SERVER_STARTED_EVENT;
	ptrToObject->m_eventDate = QDate::currentDate();
	RwEventType::RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwServerStartedEvent::generate()
{
	RwEventType* ptrToCompressed = new RwEventType;
	ptrToCompressed->copyEssentials(this);
	ptrToCompressed->m_eventDescription = "RemoteWorkers server has started";
	RwEventType::RwEventTypeHandle handle(ptrToCompressed);
	return handle;
}

}
