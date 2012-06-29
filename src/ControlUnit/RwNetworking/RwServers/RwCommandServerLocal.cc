/* 

RwCommandServerLocal.cc: Emulates a local command server

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandServerLocal.h"

#include <QLocalSocket>

#include "RwUtils/RwGlobal/RwDefines.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwWorkerInterface/RwManagement.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwServers {
        
        RwCommandServerLocal::RwCommandServerLocal(QObject* parent, const QString& serverName) : 
        RwCommandServerBase(parent, serverName)
        {
            m_localServer = new QLocalServer(this);
            m_pendingConnection = false;
        }
        
        RwCommandServerLocal::~RwCommandServerLocal()
        {
            delete m_localServer;
        }
        
        void RwCommandServerLocal::start()
        {
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
        
        void RwCommandServerLocal::processConnection()
        {
            m_pendingConnection = true;
            
            // ESTABLISHING CONNECTION
            m_currentConnection = m_localServer->nextPendingConnection();
            QObject::connect(m_currentConnection, SIGNAL(disconnected()), 
                             m_currentConnection, SLOT(deleteLater()));
            
            while (m_currentConnection->bytesAvailable() < (int)sizeof(quint32))
                   m_currentConnection->waitForReadyRead();
            
            // RECEIVING DATA
            QByteArray receivedData = m_currentConnection->readAll(); // This may be dangerous
            QByteArray responseData;
            RwReturnType errorCode = processData(receivedData, responseData);
            
            if (errorCode != RW_NO_ERROR)
            {
                rwError() << "Some error happened sending upwards" << endLine();
            }
            
            // SENDING RAW DATA
            m_currentConnection->write(responseData);
            m_pendingConnection = false;
        }
        
        void RwCommandServerLocal::init()
        {
            QObject::connect(m_localServer, SIGNAL(newConnection()), 
                             this, SLOT(processConnection()));
        }
        
    }
}
