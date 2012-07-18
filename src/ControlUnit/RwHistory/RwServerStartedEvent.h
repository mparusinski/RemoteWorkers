/* 

RwServerStartedEvent.h: A server started event. Inherits from RwEventType

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#ifndef _RWHISTORY_RWSERVERSTARTEDEVENT_H_
#define _RWHISTORY_RWSERVERSTARTEDEVENT_H_

#include "RwEventType.h"

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwHistory {

class RwServerStartedEvent : public RwEventType {

public:
	RwServerStartedEvent() { m_generated = false; }

	virtual ~RwServerStartedEvent() { }

	virtual RwEventTypeHandle generate();

	static RwEventTypeHandle create();

private:
	DISALLOW_COPY_AND_ASSIGN(RwServerStartedEvent);
};

}

#endif // _RWHISTORY_RWSERVERSTARTEDEVENT_H_
