/* 

SimpleRun.cpp: Test to check that basic functionality works

As part of the Remote Workers project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/05/2012.

*/

// NO FUNCTIONS TO BE ADDED TO THIS FILE

#include <cstdio>
#include <cstdlib>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QTextStream>

#include "WorkerInterface/Reply.h"
#include "WorkerInterface/Worker.h"
#include "WorkerInterface/Command.h"
#include "WorkerInterface/Management.h"
#include "Utils/Log/Logger.h"

using namespace WorkerInterface;

int main(int argc, char *argv[])
{
	Utils::Log::Logger::getInstance()->turnAllOn();
    QTextStream streamStdout(stdout);

	QFileInfoList availableWorkers = Management::getInstance()->listAvailableWorkers();
	for (int i = 0; i < availableWorkers.size(); ++i)
	{
		streamStdout << availableWorkers[i].fileName() << endl;
	}

	Worker worker;
	Management::getInstance()->createWorker("SimpleTestWorker", worker);
	Command command("SimpleTestWorker", QStringList());
	worker.executeCommand(command);
	Reply reply;
    worker.getReply(reply);

	if ( reply.empty() )
	{
		Utils::Log::Logger::getInstance()->error_msg("Reply is not built");
		return -1;
	}
	else
	{
		Utils::Log::Logger::getInstance()->log("Reply is built");
	}

	const Reply::ByteStreams& rawData = reply.getRawData();
	const int numberOfByteStreams = rawData.size();
	for (int i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
		const ByteStream& byteStream = rawData[i].second;
		streamStdout << "File: " << fileName << endl;

		const int lengthOfStream = byteStream.size();
		const char * rawData = byteStream.getRawData();
		for (int j = 0; j < lengthOfStream; ++j)
		{
			streamStdout << rawData[j];
		}
		streamStdout << endl << endl;
	}

	return 1;
}
