/* 

RwCommandServerLocal.cc: Emulates a local command server

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandServerLocal.h"

#include <QLocalSocket>

#include "RwUtils/RwLog/RwLogger.h"

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
        RwLogger::getInstance()->debug("Server starting");
        if ( isRunning() )
        {
            QString errorMsg = "A local server with name ";
            errorMsg += getServerName();
            errorMsg += " has already started";
            
            RwLogger::getInstance()->error_msg(errorMsg);
            return;
        }
        
        QLocalServer::removeServer(m_serverName);
        
        if ( !m_localServer->listen(m_serverName) )
        {
            QString errorMsg = "Unable to start server: ";
            errorMsg += m_localServer->errorString();
            
            RwLogger::getInstance()->error_msg(errorMsg);
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
        RwLogger::getInstance()->debug("Caught connection");
        QLocalSocket* clientSocket = m_localServer->nextPendingConnection();
        
        QObject::connect(clientSocket, SIGNAL(disconnected()), 
                         clientSocket, SLOT(deleteLater()));
    }
 
    void RwCommandServerLocal::init()
    {
        RwLogger::getInstance()->debug("Initialising");
        QObject::connect(m_localServer, SIGNAL(newConnection()), 
                         this, SLOT(simpleTest()));
    }
}

