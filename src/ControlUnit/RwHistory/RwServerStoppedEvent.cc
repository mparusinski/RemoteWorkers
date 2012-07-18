/* 

RwServerStoppedEvent.cc: A server stopped event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwServerStoppedEvent.h"

namespace RwHistory {

RwEventType::RwEventTypeHandle RwServerStoppedEvent::create()
{
	RwServerStoppedEvent* ptrToObject = new RwServerStoppedEvent;
	ptrToObject->m_subClassType = RW_SERVER_STOPPED_EVENT;
	ptrToObject->m_eventDate = QDate::currentDate();
	RwEventType::RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwServerStoppedEvent::generate()
{
	RwEventType* ptrToCompressed = new RwEventType;
	ptrToCompressed->copyEssentials(this);
	ptrToCompressed->m_eventDescription = "RemoteWorkers server has stopped";
	RwEventType::RwEventTypeHandle handle(ptrToCompressed);
	return handle;
}

}
