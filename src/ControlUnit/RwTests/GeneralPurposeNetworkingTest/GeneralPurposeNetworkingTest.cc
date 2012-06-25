/* 

GeneralPurposeNetworkingTest: Check that networking stuff when I code but don't want to do something complicateds

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012

*/

#include <QString>

#include "RwNetworking/RwNetDataStructures/RwCommandRequest.h"
#include "RwNetworking/RwNetDataStructures/RwCommandReply.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwReply.h"
#include "RwDataStructures/RwByteArray.h"
#include "RwUtils/RwLog/RwMessagingManager.h"
#include "RwUtils/RwLog/RwCommon.h"

using namespace RwNetworking::RwNetDataStructures;
using namespace RwWorkerInterface;
using namespace RwDataStructures;
using namespace RwUtils::RwLog;

int main(int argc, char * argv [])
{
    RwMessagingManager::getInstance()->turnAllOn();
    
    QString commandName = "SimpleTestWorker";
    QStringList arguments;
    arguments.append("First");
    arguments.append("Second");
    
    RwCommand command(commandName, arguments);
    RwCommandRequest simpleRequest("SimpleTestWorker", command);
    RwByteArray requestData;
    simpleRequest.toRawData(requestData);
    
    RwCommandRequest copyOfRequest;
    copyOfRequest.fromRawData(requestData);
    
    rwMessage() << "Name of Worker: " << copyOfRequest.getWorkerName() << endLine();
    rwMessage() << "Order: " << copyOfRequest.getCommand().getOrder() << endLine();
    
    const QStringList copyArguments = copyOfRequest.getCommand().getArguments();
    const int numberOfArguments = copyArguments.length();
    
    for (int i = 0; i < numberOfArguments; ++i)
    {
        rwMessage() << "Argument " << i << ": " << copyArguments[i] << endLine();
    }
    
    RwWorker worker;
    RwManagement::getInstance()->createWorker("SimpleTestWorker", worker);
    worker.executeCommand(command);
	RwReply reply;
    worker.getReply(reply);
    
    RwWorkerInterface::RwReply::ByteArrays replies = reply.getRawData();
    int numberOfReplies = replies.size();
    for (int i = 0; i < numberOfReplies; ++i)
    {
        const QPair<QString, RwByteArray>& element = replies[i];
        rwMessage() << "File: " << element.first << endLine();
        rwMessage() << element.second.getRawData();
    }
    
    RwCommandReply simpleReply(reply);
    RwByteArray replyData;
    simpleReply.toRawData(replyData);
    
    RwCommandReply copyOfReply;
    copyOfReply.fromRawData(replyData);
    
    copyOfReply.getReply(reply);
    replies = reply.getRawData();
    
    numberOfReplies = replies.size();
    for (int i = 0; i < numberOfReplies; ++i)
    {
        const QPair<QString, RwByteArray>& element = replies[i];
        rwMessage() << "File: " << element.first << endLine();
        rwMessage() << element.second.getRawData();
    }
    
    return 0;
}
