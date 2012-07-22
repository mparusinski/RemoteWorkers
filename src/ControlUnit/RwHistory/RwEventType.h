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
#include <QDateTime>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwHistory {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is a helper class for RwEvent. It captures the type
///        of the event which occurred. All events are meant to be in non
///        generated state, which means they contain the smallest amount of
///        information possible. When other information will become needed
///        the class will then generate the required information.
///        Non generated events corresponds to subclass of this one.
///        Prefer using the RwEventLog class
////////////////////////////////////////////////////////////////////////////////
class RwEventType {

public:
	typedef enum {
		RW_SERVER_STARTED_EVENT,
		RW_SERVER_STOPPED_EVENT,
		RW_WORKER_ADDED_EVENT,
		RW_WORKER_REMOVED_EVENT,
		RW_WORKER_EXECUTION_EVENT
	} RwEventTypeSubClassType; // type of the event

	// Pointer to this class
	typedef QSharedPointer<RwEventType> RwEventTypeHandle;

	RwEventType();

	virtual ~RwEventType();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Get the type of event this event represents.
	/// \return A variable describing the type of event
	////////////////////////////////////////////////////////////////////////////////
	RwEventTypeSubClassType getEventType() const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Checks if the event was generated
	/// \return Returns true if the event data was generated
	////////////////////////////////////////////////////////////////////////////////
	inline bool hasBeenGenerated() const { return m_generated; }

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Function to get the date at which the event occurred.
	/// \return The date of the event
	////////////////////////////////////////////////////////////////////////////////
	inline const QDateTime& date() const { return m_eventDate; }

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Function to get the date at which the event occurred.
	/// \return The date of the event
	////////////////////////////////////////////////////////////////////////////////
	inline QDateTime  & date() { return m_eventDate; }

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Generates the event data
	/// \return A pointer to object containing the generated data
	////////////////////////////////////////////////////////////////////////////////
	virtual RwEventTypeHandle generate();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Copies the essential data from another event (don't use this directly)
	/// \param[in] other Event from which the data needs to be copied from
	////////////////////////////////////////////////////////////////////////////////
	void copyEssentials(const RwEventType* other);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Gets a string describing the event. Will result in generating the event
	///        data if not available..
	/// \returns The description of the event
	////////////////////////////////////////////////////////////////////////////////
	const QString& getEventDescription() const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Sets the string describing the event. Do not use, internal purpose only
	/// \param[in] eventDescription String describing the event
	////////////////////////////////////////////////////////////////////////////////
	void setEventDescription(QString& eventDescription);

protected:
	bool m_generated;
	QDateTime m_eventDate;
	RwEventTypeSubClassType m_subClassType;

private:
	DISALLOW_COPY_AND_ASSIGN(RwEventType);
	QString m_eventDescription;

};

}

#endif // _RWHISTORY_RWEVENTTYPE_H_
