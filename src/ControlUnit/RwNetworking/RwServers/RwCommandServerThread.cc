/* 

RwCommandServerThread.cc: Creates a thread in which run a Command Server

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 04/08/2012

*/

#include "RwCommandServerThread.h"

#include "RwUtils/RwGlobal/RwDefines.h"

#include "RwHistory/RwEventLog.h"

namespace RwNetworking {
    
    namespace RwServers {
        
        RwCommandServerThread::RwCommandServerThread()
        {
            m_localServer = 0;
            m_tcpServer = 0;
            // m_sslServer = 0;
        }
        
        RwCommandServerThread::~RwCommandServerThread()
        {
            if (m_localServer != 0)
                delete m_localServer;
            
            if (m_tcpServer != 0)
                delete m_tcpServer;
            
            // if (m_sslServer != 0)
            //    delete m_sslServer;
        }
        
        RwCommandServerThread* RwCommandServerThread::getInstance()
        {
            static RwCommandServerThread* instance = 0;
            if (instance == 0)
            {
                instance = new RwCommandServerThread;
            }
            return instance;
        }
        
        void RwCommandServerThread::run()
        {
            m_localServer = new RwCommandServerLocal(0, RW_LOCAL_SERVER_NAME);
            m_tcpServer = new RwCommandServerTCP(0, RW_COMMUNICATION_PORT);
            // m_sslServer = new RwCommandServerSSL(0, RW_COMMUNICATION_PORT);
            
            startServers();
            
            exec();
        }
        
        void RwCommandServerThread::stopServers()
        {
            // check atomicity
            
            m_localServer->stop();
            m_tcpServer->stop();
            // m_sslServer->stop();
            
            RwHistory::RwEventLog::getInstance()->serverStopped();
        }
        
        void RwCommandServerThread::startServers()
        {
            m_localServer->start();
            m_tcpServer->start();
            // m_sslServer->start();
            
            RwHistory::RwEventLog::getInstance()->serverStarted();
        }
        
    }
    
}
