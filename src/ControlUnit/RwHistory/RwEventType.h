/* 

RwEventType.h: Capture the type of an event

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#ifndef _RWHISTORY_RWEVENTTYPE_H_
#define _RWHISTORY_RWEVENTTYPE_H_

#include <QString>
#include <QDate>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwHistory {

class RwEventType {

public:
	typedef enum {
		RW_SERVER_STARTED_EVENT,
		RW_SERVER_STOPPED_EVENT,
		RW_WORKER_ADDED_EVENT,
		RW_WORKER_REMOVED_EVENT,
		RW_WORKER_EXECUTION_EVENT
	} RwEventTypeSubClassType;

	typedef QSharedPointer<RwEventType> RwEventTypeHandle;

	RwEventType() { m_generated = true; }

	virtual ~RwEventType();

	RwEventTypeSubClassType getSubClassType() const;

	inline bool hasBeenGenerated() const { return m_generated; }

	inline const QDate& date() const { return m_eventDate; }

	inline QDate& date() { return m_eventDate; }

	virtual RwEventTypeHandle generate();

	void copyEssentials(const RwEventType* other);

	mutable QString m_eventDescription; // string version of event

protected:
	RwEventTypeSubClassType m_subClassType;
	QDate m_eventDate;
	bool m_generated;

private:
	DISALLOW_COPY_AND_ASSIGN(RwEventType);

};

}

#endif // _RWHISTORY_RWEVENTTYPE_H_
