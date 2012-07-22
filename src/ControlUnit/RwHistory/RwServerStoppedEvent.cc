/* 

RwServerStoppedEvent.cc: A server stopped event. Inherits from RwEventType

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwServerStoppedEvent.h"

namespace RwHistory {

RwServerStoppedEvent::RwServerStoppedEvent()
{
	m_generated = false;
	m_subClassType = RW_SERVER_STOPPED_EVENT;
}

RwEventType::RwEventTypeHandle RwServerStoppedEvent::create()
{
	RwServerStoppedEvent* ptrToObject = new RwServerStoppedEvent;
	RwEventType::RwEventTypeHandle handle(ptrToObject);
	return handle;
}

RwEventType::RwEventTypeHandle RwServerStoppedEvent::generate()
{
	RwEventType* ptrToCompressed = new RwEventType;
	ptrToCompressed->copyEssentials(this);
	QString description = "RemoteWorkers server has stopped";
	ptrToCompressed->setEventDescription(description);
	RwEventType::RwEventTypeHandle handle(ptrToCompressed);
	return handle;
}

}
