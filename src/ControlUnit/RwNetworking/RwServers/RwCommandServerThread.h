/* 

RwCommandServerThread.h: Creates a thread in which run a Command Server

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 04/08/2012.

*/

#ifndef _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERTHREAD_H_
#define _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERTHREAD_H_

#include <QThread>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwCommandServerLocal.h"
#include "RwCommandServerTCP.h"
#include "RwCommandServerSSL.h"

namespace RwNetworking {
    
    namespace RwServers {
        
        class RwCommandServerThread : public QThread {
            
        public:
            
            static RwCommandServerThread* getInstance();
            
            virtual ~RwCommandServerThread();
            
            void run();
            
            void startServers();
            
            void stopServers();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandServerThread);
            
            RwCommandServerThread();
            
            RwCommandServerLocal* m_localServer;
            RwCommandServerTCP* m_tcpServer;
            // RwCommandServerSSL* m_sslServer;
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERTHREAD_H_
