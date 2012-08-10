/* 

RwCommandServerLocal.cc: Emulates a local command server

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandServerLocal.h"

#include "RwUtils/RwGlobal/RwDefines.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwWorkerInterface/RwManagement.h"

#include "../RwSocket/RwLocalSocket.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwServers {
        
        RwCommandServerLocal::RwCommandServerLocal(QObject* parent, const QString& serverName) : 
        RwCommandServerBase(parent)
        {
            m_serverName = serverName;
            m_localServer = new QLocalServer(this);
        }
        
        RwCommandServerLocal::~RwCommandServerLocal()
        {
            delete m_localServer;
        }
        
        void RwCommandServerLocal::start()
        {
            if ( isRunning() )
            {
                rwWarning() << "Server already running -> closing" << endLine();
                m_localServer->close();
            }
            
            QLocalServer::removeServer(m_serverName);
            
            if ( !m_localServer->listen(m_serverName) )
            {
                rwError() << "Unable to start server: " << m_localServer->errorString() << endLine();
                return;
            }
            
            init();
        }
        
        void RwCommandServerLocal::stop()
        {
            m_localServer->close();
        }
        
        bool RwCommandServerLocal::isRunning() const
        {
            return m_localServer->isListening();
        }
        
        void RwCommandServerLocal::processConnection()
        {
            // ESTABLISHING CONNECTION
            m_currentConnection = new RwSocket::RwLocalSocket(m_localServer->nextPendingConnection());
            abstractProcessConnection();

        }
        
        void RwCommandServerLocal::init()
        {
            connect(m_localServer, SIGNAL(newConnection()), this, SLOT(processConnection()));
        }

    }
}

