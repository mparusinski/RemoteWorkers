/* 

RwWorkerList.h: Handles the list of installed workers

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 21/07/2012.

*/

#ifndef _RWHISTORY_RWWORKERLIST_H_
#define _RWHISTORY_RWWORKERLIST_H_

#include <QSet>
#include <QString>
#include <QDate>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwWorkerInterface {

class RwWorkerList {

public:
	typedef enum {
		RW_WORKER_NO_TYPE = 0,
	} WorkerType;

	typedef struct {
		QString m_workerName;
		WorkerType m_type; // default for now
		QDate m_date;
	} WorkerDescriptionType;

	virtual ~RwWorkerList();

	static RwWorkerList* getInstance();

	void addWorker(const QString& workerName);

	void addWorker(const QString& workerName, const WorkerType workerType);

	void removeWorker(const QString& workerName);

private:
	DISALLOW_COPY_AND_ASSIGN(RwWorkerList);
	RwWorkerList(); // Singleton Pattern

	QSet<WorkerDescriptionType> m_listOfWorkers;

};

}

#endif // _RWHISTORY_RWWORKERLIST_H_
