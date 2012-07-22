/* 

RwWorkerList.h: Handles the list of installed workers

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 21/07/2012.

*/

#include "RwWorkerList.h"

namespace RwWorkerInterface {

RwWorkerList::RwWorkerList()
{

}

RwWorkerList::~RwWorkerList()
{

}

RwWorkerList* RwWorkerList::getInstance()
{
	static RwWorkerList* instance = 0;
	if (instance == 0)
	{
		instance = new RwWorkerList;
	}
	return instance;
}

void RwWorkerList::addWorker(const QString& workerName)
{

}

void RwWorkerList::addWorker(const QString& workerName, const WorkerType type)
{
	WorkerDescriptionType worker
}

}
