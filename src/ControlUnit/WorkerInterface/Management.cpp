/* 

Management.hpp: Manages workers

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012

*/

#include "Management.hpp"

#include "Configuration.hpp"
#include "Utils/Logger.hpp"
#include "Utils/CrossPlatform.hpp"

namespace WorkerInterface
{

Management::Management()
{
	m_pathToWorkers = Configuration::getInstance()->getWorkersPath();
	//Utils::Logger::getInstance()->debug(m_pathToWorkers)
	if (m_pathToWorkers == string())
	{
		Utils::Logger::getInstance()->error("Path to workers not read! Closing");
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

Worker Management::createWorker(const string& workerName) const
{
	string fullPath = m_pathToWorkers;
	fullPath += Utils::CrossPlatform::getPathSeparator();
	fullPath += workerName;

	return Worker(fullPath);
}

}
