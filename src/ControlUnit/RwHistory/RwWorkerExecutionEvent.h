/* 

RwWorkerExecutionEvent.h: Worker executed a command event. Inherits from RwEventType

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#ifndef _RWHISTORY_RWWORKEREXECUTIONEVENT_H_
#define _RWHISTORY_RWWORKEREXECUTIONEVENT_H_

#include "RwEventType.h"

#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwUtils/RwGlobal/RwClasses.h"

using namespace RwWorkerInterface;

namespace RwHistory {

class RwWorkerExecutionEvent : public RwEventType {

public:
	virtual ~RwWorkerExecutionEvent() { }

	static RwEventTypeHandle create(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command);

	virtual RwEventTypeHandle generate();

private:
	RwWorkerExecutionEvent() { m_generated = false; }
	DISALLOW_COPY_AND_ASSIGN(RwWorkerExecutionEvent);

	RwWorker::RwWorkerPtr m_worker;
	RwCommand::RwCommandPtr m_command;

};

}

#endif // _RWHISTORY_RWWORKEREXECUTIONEVENT_H_
