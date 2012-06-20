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

#include "WorkerInterface/Reply.h"
#include "WorkerInterface/Worker.h"
#include "WorkerInterface/Command.h"
#include "WorkerInterface/Management.h"
#include "Utils/Log/Logger.h"
#include "Utils/Profile/Profiler.h"

using namespace std;
using namespace WorkerInterface;

int main(int argc, char *argv[])
{
	Utils::Profile::Profiler::startProfiler();
	Utils::Log::Logger::getInstance()->turnAllOn();
	Utils::Profile::Profiler::profile("Turning logging on");

	Utils::Profile::Profiler::startProfiler();
	QFileInfoList availableWorkers = Management::getInstance()->listAvailableWorkers();
	for (size_t i = 0; i < availableWorkers.size(); ++i)
	{
		printf("%s\n", availableWorkers[i].fileName().toAscii().data());
	}
	Utils::Profile::Profiler::profile("Reading workers");

	Utils::Profile::Profiler::startProfiler();
	Worker worker;
	Management::getInstance()->createWorker("NastyBadWorker", worker);
	Utils::Profile::Profiler::profile("Creating worker");

	Utils::Profile::Profiler::startProfiler();
	Command command("NastyBadWorker", QStringList());
	worker.executeCommand(command);
	Utils::Profile::Profiler::profile("Executing a command");

	Utils::Profile::Profiler::startProfiler();
	Reply reply;
	worker.getReply(reply);
	Utils::Profile::Profiler::profile("Creating the reply");

	Utils::Profile::Profiler::startProfiler();
	QList< QPair< QString, ByteStream > > rawData = reply.getRawData();
	const size_t numberOfByteStreams = rawData.size();
	for (size_t i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
		printf("File: %s\n", fileName.toAscii().data());
	}
	Utils::Profile::Profiler::profile("Listing files");

	return 1;
}
