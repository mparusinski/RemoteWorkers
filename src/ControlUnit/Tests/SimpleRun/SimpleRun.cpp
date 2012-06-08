/* 

SimpleRun.cpp: Test to check that basic functionality works

As part of the Remote Workers project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/05/2012.

*/

// NO FUNCTIONS TO BE ADDED TO THIS FILE

#include <QString>
#include <QStringList>
#include <QVector>
#include <iostream>

#include "WorkerInterface/Reply.hpp"
#include "WorkerInterface/Worker.hpp"
#include "WorkerInterface/Command.hpp"
#include "WorkerInterface/Management.hpp"
#include "Utils/Logger.hpp"

using namespace std;
using namespace WorkerInterface;

int main(int argc, char *argv[])
{
	Utils::Logger::getInstance()->turnAllOn();

	QFileInfoList availableWorkers = Management::getInstance()->listAvailableWorkers();
	for (size_t i = 0; i < availableWorkers.size(); ++i)
	{
		cout << availableWorkers[i].fileName().toStdString() << endl;
	}

	Worker worker;
	Management::getInstance()->createWorker("SimpleTestWorker", worker);
	Command command("SimpleTestWorker", QStringList());
	worker.executeCommand(command);
	Reply reply;
    worker.getReply(reply);

	if ( reply.empty() )
	{
		Utils::Logger::getInstance()->error_msg("Reply is not built");
		return -1;
	}
	else
	{
		Utils::Logger::getInstance()->log("Reply is built");
	}

	const Reply::ByteStreams& rawData = reply.getRawData();
	const size_t numberOfByteStreams = rawData.size();
	for (size_t i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
		const ByteStream& byteStream = rawData[i].second;
		cout << "File: " << fileName.toStdString() << endl;

		const size_t lengthOfStream = byteStream.size();
		const char * rawData = byteStream.getRawData();
		for (size_t j = 0; j < lengthOfStream; ++j)
		{
			cout << rawData[j];
		}
		cout << endl << endl;
	}

	return 1;
}
