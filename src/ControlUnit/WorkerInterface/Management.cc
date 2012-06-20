/* 

Management.hpp: Manages workers

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012

*/

#include "Management.h"

#include <cstdio>

#include "Configuration.h"
#include "Utils/Log/Logger.h"
#include "Utils/System/FileManagement.h"

namespace WorkerInterface
{

Management::Management()
{
    QString pathToWorkers;
	Configuration::getInstance()->getWorkersPath(pathToWorkers);
    m_pathToWorkers.setFile(pathToWorkers);
	//Utils::Logger::getInstance()->debug(m_pathToWorkers)
	if (m_pathToWorkers == QString())
	{
		Utils::Log::Logger::getInstance()->error_msg("Path to workers not read! Closing!");
		exit(-1);
	}
}

Management::~Management()
{

}

Management* Management::getInstance()
{
	static Management* instance = 0;
	if (instance == 0)
	{
		instance = new Management();
	}
	return instance;
}

ReturnType Management::createWorker(const QString& workerName, Worker& worker)
{
	getListOfWorkers();
	const int numberOfWorkers = m_availableWorkers.size();
	for (int i = 0; i < numberOfWorkers; ++i)
	{
		const QFileInfo& currentWorkerName = m_availableWorkers[i];
		if (currentWorkerName.fileName() == workerName)
		{
			worker = Worker(currentWorkerName);
			return RW_NO_ERROR;
		}
	}

	Utils::Log::Logger::getInstance()->error_msg("Worker not available");

	return RW_ERROR_NO_WORKER;
}

const QFileInfoList& Management::listAvailableWorkers()
{
	getListOfWorkers();
	return m_availableWorkers;
}

void Management::getListOfWorkers()
{
	if (m_availableWorkers.empty())
	{
		Utils::System::FileManagement::getListOfDirsInDir(m_pathToWorkers, m_availableWorkers);
	}
}

}