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
#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwLog/RwMessagingManager.h"

using namespace RwUtils::RwLog;
using namespace RwWorkerInterface;

int main(int argc, char *argv[])
{
	RwMessagingManager::getInstance()->turnAllOn();

	QStringList availableWorkers = RwManagement::getInstance()->scanAvailableWorkers();
    rwMessage() << "Available workers" << endLine();
	for (int i = 0; i < availableWorkers.size(); ++i)
	{
        rwMessage() << availableWorkers[i] << endLine();
	}

	RwWorker::RwWorkerPtr worker;
	RwManagement::getInstance()->createWorker("SimpleTestWorker", worker);
	RwCommand command("SimpleTestWorker", QStringList());
	worker->executeCommand(command);
	RwReply reply;
    worker->getReply(reply);

	if ( reply.empty() )
	{
        rwError() << "Reply is not built" << endLine();
		return -1;
	}
	else
	{
        rwMessage() << "Reply is built" << endLine();
	}

    RwReply::ByteArrays& rawData = reply.getRawData();
	const int numberOfByteStreams = rawData.size();
	for (int i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
        QByteArray& byteStream = rawData[i].second;
        printf("File: %s\n", fileName.toAscii().data());
        rwMessage() << byteStream << endLine() << endLine();
	}

	return 1;
}
