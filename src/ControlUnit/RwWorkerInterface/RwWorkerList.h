/* 

RwWorkerList.h: Handles the list of installed workers

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 21/07/2012.

*/

#ifndef _RWHISTORY_RWWORKERLIST_H_
#define _RWHISTORY_RWWORKERLIST_H_

#include <QList>
#include <QMap>
#include <QString>
#include <QDate>
#include <QPair>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

using namespace RwUtils::RwGlobal;

namespace RwWorkerInterface {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents the global list of workers available.
///        This is a singleton class
////////////////////////////////////////////////////////////////////////////////
class RwWorkerList {

public:
	typedef enum {
		RW_WORKER_NO_TYPE = 0,
	} WorkerType;

	typedef QPair<WorkerType, QDate>  WorkerDescriptionType;

	virtual ~RwWorkerList();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Function to use to get an instance of this class. (See singleton pattern)
	////////////////////////////////////////////////////////////////////////////////
	static RwWorkerList* getInstance();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Adds a worker to the list of workers
	/// \param[in] workerName Name of the worker
	////////////////////////////////////////////////////////////////////////////////
	void addWorker(const QString& workerName);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Adds a worker to the list of workers
	/// \param[in] workerName Name of the worker
	/// \param[in] workerType Type of the worker (only one type is yet available)
	////////////////////////////////////////////////////////////////////////////////
	void addWorker(const QString& workerName, const WorkerType workerType);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Removes the worker from the list
	/// \param[in] workerName Worker to be removed
	////////////////////////////////////////////////////////////////////////////////
	void removeWorker(const QString& workerName);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Reads the list of workers from the specified file in conf.txt
	/// \return An error code to inform about the success of failure of the program
	////////////////////////////////////////////////////////////////////////////////
	RwReturnType readWorkers();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the list of workers available.
	/// \return A copy of the list of workers. Avoid overcalling this function
	////////////////////////////////////////////////////////////////////////////////
	QList<QString> getListOfWorkers();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the list of workers available.
	/// \return A copy of the list of workers. Avoid overcalling this function
	////////////////////////////////////////////////////////////////////////////////
	const QList<QString> getListOfWorkers() const;

private:
	DISALLOW_COPY_AND_ASSIGN(RwWorkerList);
	RwWorkerList(); // Singleton Pattern

	QMap<QString, WorkerDescriptionType> m_listOfWorkers;
};

}

#endif // _RWHISTORY_RWWORKERLIST_H_
