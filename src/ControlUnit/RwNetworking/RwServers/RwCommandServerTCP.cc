/* 

RwCommandSeverTCP.cc: Listens for command over TCP

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

 */

#include "RwCommandServerTCP.h"

#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwGlobal/RwReturn.h"

using namespace RwUtils::RwLog;
using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwServers {
        
        RwCommandServerTCP::RwCommandServerTCP(QObject* parent, const int portNumber) 
        : RwCommandServerBase<QTcpSocket>(parent)
        {
            m_portNumber = portNumber;
            m_tcpServer = new QTcpServer(this);
        }
        
        RwCommandServerTCP::~RwCommandServerTCP()
        {
            delete m_tcpServer;
        }
        
        void RwCommandServerTCP::start()
        {
            if ( isRunning() )
            {
                rwWarning() << "Server already running -> closing" << endLine();
            }
            
            m_tcpServer->close();
            
            if ( !m_tcpServer->listen(QHostAddress::Any, m_portNumber) )
            {
                rwError() << "Unable to start server: " << m_tcpServer->errorString() << endLine();
                return;
            }
            
            init();
        }
        
        void RwCommandServerTCP::stop()
        {
            m_tcpServer->close();
        }
        
        bool RwCommandServerTCP::isRunning() const
        {
            return m_tcpServer->isListening();
        }
        
        void RwCommandServerTCP::processConnection()
        {
            m_currentConnection = m_tcpServer->nextPendingConnection();
            abstractProcessConnection();
        }
        
        void RwCommandServerTCP::init()
        {
            QObject::connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(processConnection()));
        }
        
    }
    
}
