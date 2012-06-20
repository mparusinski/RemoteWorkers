/* 

Management.hpp: Manages workers

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012

*/

#include "RwManagement.h"

#include <cstdio>

#include "RwConfiguration.h"
#include "RwUtils/RwLog/RwLogger.h"
#include "RwUtils/RwSystem/RwFileManagement.h"

namespace RwWorkerInterface
{

RwManagement::RwManagement()
{
    QString pathToWorkers;
	RwConfiguration::getInstance()->getWorkersPath(pathToWorkers);
    m_pathToWorkers.setFile(pathToWorkers);
	//Utils::Logger::getInstance()->debug(m_pathToWorkers)
	if (m_pathToWorkers == QString())
	{
		RwUtils::RwLog::RwLogger::getInstance()->error_msg("Path to workers not read! Closing!");
		exit(-1);
	}
}

RwManagement::~RwManagement()
{

}

RwManagement* RwManagement::getInstance()
{
	static RwManagement* instance = 0;
	if (instance == 0)
	{
		instance = new RwManagement();
	}
	return instance;
}

RwReturnType RwManagement::createWorker(const QString& workerName, RwWorker& worker)
{
	getListOfWorkers();
	const int numberOfWorkers = m_availableWorkers.size();
	for (int i = 0; i < numberOfWorkers; ++i)
	{
		const QFileInfo& currentWorkerName = m_availableWorkers[i];
		if (currentWorkerName.fileName() == workerName)
		{
			worker = RwWorker(currentWorkerName);
			return RW_NO_ERROR;
		}
	}

	RwUtils::RwLog::RwLogger::getInstance()->error_msg("Worker not available");

	return RW_ERROR_NO_WORKER;
}

const QFileInfoList& RwManagement::listAvailableWorkers()
{
	getListOfWorkers();
	return m_availableWorkers;
}

void RwManagement::getListOfWorkers()
{
	if (m_availableWorkers.empty())
	{
		RwUtils::RwSystem::RwFileManagement::getListOfDirsInDir(m_pathToWorkers, m_availableWorkers);
	}
}

}
