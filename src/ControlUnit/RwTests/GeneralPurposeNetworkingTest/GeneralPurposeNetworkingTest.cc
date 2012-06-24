/* 

GeneralPurposeNetworkingTest: Check that networking stuff when I code but don't want to do something complicateds

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012

*/

#include <QString>

#include "RwNetworking/RwCommandRequest.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwDataStructures/RwByteArray.h"
#include "RwUtils/RwLog/RwMessagingManager.h"
#include "RwUtils/RwLog/RwCommon.h"

using namespace RwNetworking;
using namespace RwWorkerInterface;
using namespace RwDataStructures;
using namespace RwUtils::RwLog;

int main(int argc, char * argv [])
{
    RwMessagingManager::getInstance()->turnAllOn();
    
    QString commandName = "JustDoIt";
    QStringList arguments;
    arguments.append("First");
    arguments.append("Second");
    
    RwCommandRequest simpleRequest("SimpleWorker", RwCommand(commandName,arguments));
    RwByteArray rawData;
    simpleRequest.toRawData(rawData);
    
    rwMessage() << "Raw data: " << endLine() << rawData.getRawData() << endLine();
    
    RwCommandRequest copyOfRequest;
    copyOfRequest.fromRawData(rawData);
    
    rwMessage() << "Name of Worker: " << copyOfRequest.getWorkerName() << endLine();
    rwMessage() << "Order: " << copyOfRequest.getCommand().getOrder() << endLine();
    
    const QStringList copyArguments = copyOfRequest.getCommand().getArguments();
    const int numberOfArguments = copyArguments.length();
    
    for (int i = 0; i < numberOfArguments; ++i)
    {
        rwMessage() << "Argument " << i << ": " << copyArguments[i] << endLine();
    }
    
    return 0;
}
