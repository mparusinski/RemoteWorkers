/* 

RwCommandLocalPipeServer.cc: Server to pipe commands to clients

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 07/08/2012.

*/

#include "RwCommandLocalPipeServer.h"

#include "RwCommandLocalPipeIn.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        RwCommandLocalPipeServer::RwCommandLocalPipeServer()
        {
            qRegisterMetaType<QByteArray>("QByteArray");
        }
        
        RwCommandLocalPipeServer::~RwCommandLocalPipeServer()
        {
            
        }
        
        void RwCommandLocalPipeServer::run()
        {
            RwCommandLocalPipeIn::getInstance()->init();
            exec();
        }
        
    }
    
}
