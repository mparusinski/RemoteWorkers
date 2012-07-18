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

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwEventType.h"

namespace RwHistory {

	class RwEvent {

	public:
		RwEvent(const RwEventType::RwEventTypeHandle& handleToEvent);
		virtual ~RwEvent();

		bool operator <(const RwEvent& other) const;

		bool operator >(const RwEvent& other) const;

		QDate eventDate() const;

		void generateEvent();

	private:
		// Copying this object should be easy
		// DISALLOW_COPY_AND_ASSIGN(RwEvent);

		RwEventType::RwEventTypeHandle m_eventTypeVar;
	};

}

#endif // _RWHISTORY_RWEVENT_H_
