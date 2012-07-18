/* 

RwEvent.h: Class capturing a server event. Will be used for logging activity

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/08/2012.

*/

#ifndef _RWHISTORY_RWEVENT_H_
#define _RWHISTORY_RWEVENT_H_

#include <QSharedPointer>
#include <QDate>

namespace RwHistory {

	class RwEvent {

	public:
		RwEvent();
		virtual ~RwEvent();

	private:

	};

}

#endif // _RWHISTORY_RWEVENT_H_
