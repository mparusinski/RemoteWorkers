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
    RwUtils::RwGlobal::RwReturnType returnMsg;
	RwMessagingManager::getInstance()->turnAllOn();

	QStringList availableWorkers = RwManagement::getInstance()->scanAvailableWorkers();
    rwInfo() << "Available workers" << endLine();
	for (int i = 0; i < availableWorkers.size(); ++i)
	{
		rwInfo() << availableWorkers[i] << endLine();
	}

	RwWorker::RwWorkerPtr worker;
	returnMsg = RwManagement::getInstance()->createWorker("SimpleTestWorker", worker);
    
    if (returnMsg != RW_NO_ERROR)
    {
        rwError() << "Failed to create worker" << endLine();
        return -1;
    }
    
	RwCommand::RwCommandPtr command(new RwCommand("SimpleTestWorker", QStringList()));
	worker->executeCommand(command);
    
	RwReply::RwReplyPtr reply;
    worker->getReply(reply);

	if ( reply->empty() )
	{
        rwError() << "Reply is not built" << endLine();
		return -1;
	}
	else
	{
		rwInfo() << "Reply is built" << endLine();
	}

    RwReply::ByteArrays& rawData = reply->getRawData();
	const int numberOfByteStreams = rawData.size();
	for (int i = 0; i < numberOfByteStreams; ++i)
	{
		const QString& fileName = rawData[i].first;
        QByteArray& byteStream = rawData[i].second;
        rwInfo() << "File " << fileName << endLine();
        rwInfo() << byteStream << endLine() << endLine();
	}

	return 1;
}
