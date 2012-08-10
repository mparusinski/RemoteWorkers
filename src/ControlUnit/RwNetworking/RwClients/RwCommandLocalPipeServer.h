/* 

RwCommandLocalPipeServer.h: Server to pipe commands to clients

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 07/08/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPESERVER_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPESERVER_H_

#include <QThread>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwRemoteDevice.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        class RwCommandLocalPipeServer : public QThread {
            
        public:
            
            RwCommandLocalPipeServer();
            
            virtual ~RwCommandLocalPipeServer();
            
            void run();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandLocalPipeServer);
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPESERVER_H_
