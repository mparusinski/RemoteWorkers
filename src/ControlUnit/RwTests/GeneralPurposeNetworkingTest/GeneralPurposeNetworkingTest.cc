/* 

GeneralPurposeNetworkingTest: Check that networking stuff when I code but don't want to do something complicateds

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012

*/

#include <QString>
#include <QByteArray>

#include "RwNetworking/RwNetDataStructures/RwCommandRequest.h"
#include "RwNetworking/RwNetDataStructures/RwCommandReply.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwReply.h"
#include "RwUtils/RwLog/RwMessagingManager.h"
#include "RwUtils/RwLog/RwCommon.h"

using namespace RwNetworking::RwNetDataStructures;
using namespace RwWorkerInterface;
using namespace RwUtils::RwLog;

void assess(const QString& testName, const bool test)
{
    if (test)
        rwMessage() << "Test succeeded " << testName << endLine();
    else 
        rwMessage() << "Test failed " << testName << endLine();
}

bool test(const QString& commandName, const QString& order, const QStringList& arguments)
{
    RwCommand command(order, arguments);
    RwCommandRequest simpleRequest(commandName, command);
    QByteArray requestData;
    simpleRequest.toRawData(requestData);
    
    RwCommandRequest copyOfRequest;
    copyOfRequest.fromRawData(requestData);
    
    if ( copyOfRequest != simpleRequest )
    {
        rwError() << "Failure at request with " << commandName << " " << order << endLine();
        return false;
    }
    
    RwWorker worker;
    RwManagement::getInstance()->createWorker(commandName, worker);
    worker.executeCommand(command);
	RwReply reply;
    RwReturnType errorCode = worker.getReply(reply);
    
    RwCommandReply simpleReply;
    if (errorCode != RW_NO_ERROR) {
        simpleReply.setErrorCode(errorCode);
    } else {
        simpleReply.setReply(reply);
    }
    QByteArray replyData;
    simpleReply.toRawData(replyData);
    
    RwCommandReply copyOfReply;
    copyOfReply.fromRawData(replyData);
    
    if ( copyOfReply != simpleReply )
    {        
        rwError() << "Failure at reply with " << commandName << " " << order << endLine();
        return false;
    }
    
    return true;
}

int main(int argc, char * argv [])
{
    RwMessagingManager::getInstance()->turnAllOn();
    
    QStringList arguments1;
    arguments1.append("First");
    arguments1.append("Second");
    const bool test1 = test("SimpleTestWorker", "SimpleTestWorker", arguments1);
    assess("TEST 1", test1);
    
    QStringList arguments2;
    arguments2.append("");
    arguments2.append("");
    const bool test2 = test("SimpleTestWorker", "SimpleTestWorker", arguments2);
    assess("TEST 2", test2);
    
    QStringList arguments3;
    arguments3.append("a");
    arguments3.append("a");
    arguments3.append("a");
    arguments3.append("a");
    const bool test3 = test("RandomWorker", "JustDoIt", arguments3);
    assess("TEST 3", test3);
    
    return 0;
}
