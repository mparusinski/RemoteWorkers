/* 

RwWorkerRemovedEvent.h: Worker removed Event. Inherits from RwEventType

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#ifndef _RWHISTORY_RWWORKERREMOVEDEVENT_H_
#define _RWHISTORY_RWWORKERREMOVEDEVENT_H_

#include "RwEventType.h"

#include "RwWorkerInterface/RwWorker.h"
#include "RwUtils/RwGlobal/RwClasses.h"

using namespace RwWorkerInterface;

namespace RwHistory {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents an removed worker event
///        Do not use, internal purpose only
///        Prefer using RwEventLog
////////////////////////////////////////////////////////////////////////////////
class RwWorkerRemovedEvent : public RwEventType {

public:
	virtual ~RwWorkerRemovedEvent() { }

	static RwEventTypeHandle create(const RwWorker::RwWorkerPtr& worker);

	virtual RwEventTypeHandle generate();

private:
	DISALLOW_COPY_AND_ASSIGN(RwWorkerRemovedEvent);
	RwWorkerRemovedEvent(const RwWorker::RwWorkerPtr& worker);

	RwWorker::RwWorkerPtr m_worker;

};

}

#endif // _RWHISTORY_RWWORKERREMOVEDEVENT_H_
