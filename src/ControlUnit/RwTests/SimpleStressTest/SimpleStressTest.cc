/* 

SimpleStressTest.cpp: Simple Stress Test that creates 100 files each of 1 megabyte

As part of the Remote Workers project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

// NO FUNCTIONS TO BE ADDED TO THIS FILE

#include <QString>
#include <QStringList>
#include <QList>
#include <QPair>
#include <cstdio>

#include "RwWorkerInterface/RwReply.h"
#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwProfile/RwProfiler.h"

using namespace RwUtils::RwLog;
using namespace RwWorkerInterface;

int main(int argc, char *argv[])
{
	RwUtils::RwProfile::RwProfiler::startProfiler();
	RwMessagingManager::turnAllOn();
	RwUtils::RwProfile::RwProfiler::profile("Turning logging on");

	RwUtils::RwProfile::RwProfiler::startProfiler();
	QStringList availableWorkers = RwManagement::getInstance()->scanAvailableWorkers();
	for (size_t i = 0; i < availableWorkers.size(); ++i)
	{
		rwInfo() << availableWorkers[i] << endLine();
	}
	RwUtils::RwProfile::RwProfiler::profile("Reading workers");

	RwUtils::RwProfile::RwProfiler::startProfiler();
	RwWorker::RwWorkerPtr worker;
	if (RwManagement::getInstance()->createWorker("NastyBadWorker", worker) != RW_NO_ERROR)
    {
        rwError() << "Worker not created" << endLine();
        return -1;
    }
	RwUtils::RwProfile::RwProfiler::profile("Creating worker");

	RwUtils::RwProfile::RwProfiler::startProfiler();
	RwCommand::RwCommandPtr command(new RwCommand("NastyBadWorker", QStringList()));
	worker->executeCommand(command);
	RwUtils::RwProfile::RwProfiler::profile("Executing a command");

	RwUtils::RwProfile::RwProfiler::startProfiler();
	RwReply::RwReplyPtr reply;
	worker->getReply(reply);
	RwUtils::RwProfile::RwProfiler::profile("Creating the reply");

	RwUtils::RwProfile::RwProfiler::startProfiler();
	const RwReply::ByteArrays& rawData = reply->getRawData();
	const size_t numberOfByteStreams = rawData.size();
	for (size_t i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
		rwInfo() << "File: " << fileName << endLine();
	}
	RwUtils::RwProfile::RwProfiler::profile("Listing files");

	return 1;
}
