/* 

RwCommandServerLocal.cc: Emulates a local command server

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandServerLocal.h"

#include <QLocalSocket>

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    RwCommandServerLocal::RwCommandServerLocal(QObject* parent, const QString& serverName) : 
        RwCommandServerBase(parent, serverName)
    {
        m_localServer = new QLocalServer(this);
    }
    
    RwCommandServerLocal::~RwCommandServerLocal()
    {
        delete m_localServer;
    }
    
    void RwCommandServerLocal::start()
    {
        rwDebug() << "Server starting" << endLine();
        if ( isRunning() )
        {
            rwError() << "A local server with name " << getServerName() << " has already started" << endLine();
            return;
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
        if (m_localServer != 0)
        {
            m_localServer->close();
        }
    }
    
    bool RwCommandServerLocal::isRunning() const
    {
        if (m_localServer != 0)
        {
            return m_localServer->isListening();
        }
        return false;
    }
    
    void RwCommandServerLocal::simpleTest()
    {
        rwDebug() << "Caught connection" << endLine();
        QLocalSocket* clientSocket = m_localServer->nextPendingConnection();
        
        QObject::connect(clientSocket, SIGNAL(disconnected()), 
                         clientSocket, SLOT(deleteLater()));
    }
 
    void RwCommandServerLocal::init()
    {
        rwDebug() << "Initialiasing" << endLine();
        QObject::connect(m_localServer, SIGNAL(newConnection()), 
                         this, SLOT(simpleTest()));
    }
}

