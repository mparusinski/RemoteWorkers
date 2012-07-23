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

class RwWorkerList {

public:
	typedef enum {
		RW_WORKER_NO_TYPE = 0,
	} WorkerType;

	typedef QPair<WorkerType, QDate>  WorkerDescriptionType;

	virtual ~RwWorkerList();

	static RwWorkerList* getInstance();

	void addWorker(const QString& workerName);

	void addWorker(const QString& workerName, const WorkerType workerType);

	void removeWorker(const QString& workerName);

	RwReturnType readWorkers();

	QList<QString> getListOfWorkers();

	const QList<QString> getListOfWorkers() const;

private:
	DISALLOW_COPY_AND_ASSIGN(RwWorkerList);
	RwWorkerList(); // Singleton Pattern

	QMap<QString, WorkerDescriptionType> m_listOfWorkers;
};

}

#endif // _RWHISTORY_RWWORKERLIST_H_
