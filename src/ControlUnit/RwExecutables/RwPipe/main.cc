/* 

main.cc: Entry point for the CommandPipe exectuable.

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 07/08/2012

*/

#include "RwNetworking/RwClients/RwCommandLocalPipeOut.h"
#include "RwNetworking/RwNetDataStructures/RwCommandRequest.h"

#include "RwWorkerInterface/RwCommand.h"

using namespace RwNetworking::RwClients;
using namespace RwNetworking::RwNetDataStructures;

int main(int argc, char* argv[])
{
    Q_ASSERT(argc > 2);
    
    QString workerName = argv[1];
    QString commandName = argv[2];
    
    QStringList arguments;
    for (int i = 3; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }
    
    RwCommand::RwCommandPtr command(new RwCommand(commandName, arguments));
    
    RwCommandRequest request(workerName, command);
    
    RwCommandLocalPipeOut::getInstance()->connectToPipe();
    
    RwCommandLocalPipeOut::getInstance()->sendRequest(request);
    
    RwCommandLocalPipeOut::getInstance()->disconnectFromPipe();
    
    return 0;
}
