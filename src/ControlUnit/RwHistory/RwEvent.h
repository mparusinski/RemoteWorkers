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

#include "RwEventType.h"

namespace RwHistory {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents a server event. Event may be in non computed state.
///        In non computed state, the event only holds the smallest amount of data
///        possible. When access is needed to useful data, the event will compute
///        all the relevant data. To compute directly call generateEvent().
///        Use RwEventLog to register events.
////////////////////////////////////////////////////////////////////////////////
class RwEvent {

public:
	RwEvent(const RwEventType::RwEventTypeHandle& handleToEvent);
	virtual ~RwEvent();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Compare the date of two events. An event A is smaller than an event B
	///        if A occurred in B's past. Checking if A < B.
	/// \param[in] other The other event
	/// \return Returns true if A is in the past of B.
	////////////////////////////////////////////////////////////////////////////////
	bool operator <(const RwEvent& other) const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Compare the date of two events. An event A is bigger than an event B
	///        if A occurred in B's future. Checking if A > B.
	/// \param[in] other The other event
	/// \return Returns true if A is in the future of B.
	////////////////////////////////////////////////////////////////////////////////
	bool operator >(const RwEvent& other) const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Return the date of the event.
	/// \return Date of the event.
	////////////////////////////////////////////////////////////////////////////////
	const QDateTime& eventDate() const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Return the date of the event.
	/// \return Date of the event.
	////////////////////////////////////////////////////////////////////////////////
	QDateTime& eventDate();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Return a string describing the event. Note that this function
	///        will change the internal state of the event as it may have
	///        to generate the string.
	/// \return Description of the event
	////////////////////////////////////////////////////////////////////////////////
	const QString& description();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Generates all the data describing the event.
	/// \return Description of the event
	////////////////////////////////////////////////////////////////////////////////
	void generateEvent();

private:
	RwEventType::RwEventTypeHandle m_eventTypeVar;
};

}

#endif // _RWHISTORY_RWEVENT_H_
