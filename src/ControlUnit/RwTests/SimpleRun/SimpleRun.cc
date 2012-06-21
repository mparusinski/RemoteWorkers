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
#include <QFileInfo>

#include "RwWorkerInterface/RwReply.h"
#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwUtils/RwLog/RwLogger.h"

using namespace std;

using namespace RwWorkerInterface;

int main(int argc, char *argv[])
{
	RwUtils::RwLog::RwLogger::getInstance()->turnAllOn();

	QFileInfoList availableWorkers = RwManagement::getInstance()->listAvailableWorkers();
    printf("Available workers\n");
	for (int i = 0; i < availableWorkers.size(); ++i)
	{
        printf("\t%s\n", availableWorkers[i].filePath().toAscii().data());
	}

	RwWorker worker;
	RwManagement::getInstance()->createWorker("SimpleTestWorker", worker);
	RwCommand command("SimpleTestWorker", QStringList());
	worker.executeCommand(command);
	RwReply reply;
    worker.getReply(reply);

	if ( reply.empty() )
	{
		RwUtils::RwLog::RwLogger::getInstance()->error_msg("Reply is not built");
		return -1;
	}
	else
	{
		RwUtils::RwLog::RwLogger::getInstance()->log("Reply is built");
	}

    RwReply::ByteStreams& rawData = reply.getRawData();
	const int numberOfByteStreams = rawData.size();
	for (int i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
        RwByteStream& byteStream = rawData[i].second;
        printf("File: %s\n", fileName.toAscii().data());

		const int lengthOfStream = byteStream.size();
		char * rawData = byteStream.getRawData();
		for (int j = 0; j < lengthOfStream; ++j)
		{
            printf("%c", rawData[j]);
		}
        printf("\n\n");
	}

	return 1;
}
