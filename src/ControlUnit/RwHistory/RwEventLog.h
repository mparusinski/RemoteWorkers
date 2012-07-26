/* 

RwEventLog.h: A history of events that have happened

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#ifndef _RWHISTORY_RWEVENTLOG_H_
#define _RWHISTORY_RWEVENTLOG_H_

#include "RwEvent.h"

#include <QList>
#include <QDate>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwCommand.h"

#define DEFAULT_EVENTS_ROTATE 100

using namespace RwWorkerInterface;

namespace RwHistory {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class holds the information about all events that occurred.
///        This class is a singleton class and should be access by getInstance.
////////////////////////////////////////////////////////////////////////////////
class RwEventLog : public QObject
{

	Q_OBJECT

public:
	typedef QList<RwEvent> EventListType;

	virtual ~RwEventLog();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief This class is a singleton class and should be access using this function.
	/// \return The only possible instance of the class.
	////////////////////////////////////////////////////////////////////////////////
	static RwEventLog* getInstance();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Function to get the list of events in chronological order
	/// \return The list of events in chronological order
	////////////////////////////////////////////////////////////////////////////////
	EventListType& getEventList();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief This class is a singleton class and should be access using this function.
	/// \return The only possible instance of the class.
	////////////////////////////////////////////////////////////////////////////////
	const EventListType& getEventList() const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Adds an event to the event list, and maintains it ordered.
	///        The event may have any date. Prefer using the specialized functions.
	/// \param[in] event The event to be added.
	////////////////////////////////////////////////////////////////////////////////
	void addEvent(const RwEvent& event);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Notifies that the server has started
	////////////////////////////////////////////////////////////////////////////////
	void serverStarted();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Notifies that the server has stopped
	////////////////////////////////////////////////////////////////////////////////
	void serverStopped();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Notifies that a certain worker was added
	/// \param[in] worker Worker that was added.
	////////////////////////////////////////////////////////////////////////////////
	void workerAdded(const RwWorker::RwWorkerPtr& worker);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Notifies that a certain worker was removed.
	/// \param[in] worker Worker that was removed.
	////////////////////////////////////////////////////////////////////////////////
	void workerRemoved(const RwWorker::RwWorkerPtr& worker);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Notifies that a certain worker has executed a certain command.
	/// \param[in] worker Worker that was used.
	/// \param[in] command Command that was executed
	////////////////////////////////////////////////////////////////////////////////
	void workerExecutedCommand(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Generates every event into a usable format. The computation will
	///        involved computing a description of the event. Note that all events
	///        are initially in a minimal format
	////////////////////////////////////////////////////////////////////////////////
	void generateAll();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Removed all events in the list except a given amount
	/// \param[in] eventsToKeep Number of events to keep
	////////////////////////////////////////////////////////////////////////////////
	void logRotate(int eventsToKeep = DEFAULT_EVENTS_ROTATE);

signals:
	void eventAdded();

private:
	RwEventLog();
	DISALLOW_COPY_AND_ASSIGN(RwEventLog);
	EventListType m_eventList;
};

}

#endif // _RWHISTORY_RWEVENTLOG_H_
