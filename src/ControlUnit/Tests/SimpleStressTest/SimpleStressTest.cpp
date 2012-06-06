/* 

SimpleStressTest.cpp: Simple Stress Test that creates 100 files each of 1 megabyte

As part of the Remote Workers project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

// NO FUNCTIONS TO BE ADDED TO THIS FILE

#include <QString>
#include <vector>
#include <iostream>

#include "WorkerInterface/Reply.hpp"
#include "WorkerInterface/Worker.hpp"
#include "WorkerInterface/Command.hpp"
#include "WorkerInterface/Management.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Profiler.hpp"

using namespace std;
using namespace WorkerInterface;

int main(int argc, char *argv[])
{
	Utils::Profiler::startProfiler();
	Utils::Logger::getInstance()->turnAllOn();
	Utils::Profiler::profile("Turning logging on");

	Utils::Profiler::startProfiler();
	vector<QString> availableWorkers = Management::getInstance()->listAvailableWorkers();
	for (size_t i = 0; i < availableWorkers.size(); ++i)
	{
		cout << availableWorkers[i].toStdString() << endl;
	}
	Utils::Profiler::profile("Reading workers");

	Utils::Profiler::startProfiler();
	Worker worker;
	Management::getInstance()->createWorker("NastyBadWorker", worker);
	Utils::Profiler::profile("Creating worker");

	Utils::Profiler::startProfiler();
	Command command("NastyBadWorker", vector<QString>());
	worker.executeCommand(command);
	Utils::Profiler::profile("Executing a command");

	Utils::Profiler::startProfiler();
	Reply reply = worker.getReply();
	Utils::Profiler::profile("Creating the reply");

	Utils::Profiler::startProfiler();
	vector< pair< QString, ByteStream > > rawData = reply.getRawData();
	const size_t numberOfByteStreams = rawData.size();
	for (size_t i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
		cout << "File: " << fileName.toStdString() << endl;
	}
	Utils::Profiler::profile("Listing files");

	return 1;
}
