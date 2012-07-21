/* 

RwServerStoppedEvent.h: A server stopped event. Inherits from RwEventType

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#ifndef _RWHISTORY_RWSERVERSTOPPEDEVENT_H_
#define _RWHISTORY_RWSERVERSTOPPEDEVENT_H_

#include "RwEventType.h"

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwHistory {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents a server stopped event.
///        Do not use, internal purpose only
///        Prefer using RwEventLog
////////////////////////////////////////////////////////////////////////////////
class RwServerStoppedEvent : public RwEventType {

public:
	virtual ~RwServerStoppedEvent() { }

	virtual RwEventTypeHandle generate();

	static RwEventTypeHandle create();

private:
	DISALLOW_COPY_AND_ASSIGN(RwServerStoppedEvent);
	RwServerStoppedEvent();
};

}

#endif // _RWHISTORY_RWSERVERSTOPPEDEVENT_H_
