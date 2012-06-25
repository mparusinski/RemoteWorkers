/* 

RwCommandClientLocal.cc: Client for RwCommandServerLocal

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/06/2012.

*/

#include "RwCommandClientLocal.h"

#include <QDataStream>

#include "RwUtils/RwGlobal/RwDefines.h"
#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwClients {
        
        RwCommandClientLocal::RwCommandClientLocal(QObject* parent, const QString& serverName)
        : QObject(parent) 
        {
            m_connected = false;
            m_serverName = serverName;
            m_localSocket = new QLocalSocket(this);
            
            QObject::connect(m_localSocket, SIGNAL(connected()), 
                             this, SLOT(clientConnected()));
            QObject::connect(m_localSocket, SIGNAL(disconnected()), 
                             this, SLOT(clientDisconnected()));
            
            QObject::connect(m_localSocket, SIGNAL(readyRead()), 
                             this, SLOT(readReady()));
            QObject::connect(m_localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)),
                             this, SLOT(clientError(QLocalSocket::LocalSocketError)));
        }
        
        RwCommandClientLocal::~RwCommandClientLocal() 
        {
            m_localSocket->abort();
            delete m_localSocket;
        }
        
        void RwCommandClientLocal::clientConnected()
        {
            m_connected = true;
        }
        
        void RwCommandClientLocal::clientDisconnected()
        {
            m_connected = false;
            // rwDebug() << "local client has disconnected from server " << m_serverName << endLine();
        }
        
        void RwCommandClientLocal::readReady()
        {
            // rwDebug() << "local client is ready to read" << endLine();
        }
        
        void RwCommandClientLocal::connectToServer()
        {
            m_localSocket->abort();
            //        rwDebug() << "Connecting to server " << m_serverName << endLine();
            m_localSocket->connectToServer(m_serverName);
        }
        
        void RwCommandClientLocal::disconnectFromServer()
        {
            m_localSocket->disconnectFromServer();
        }
        
        void RwCommandClientLocal::clientError(QLocalSocket::LocalSocketError socketError)
        {
            rwError() << "Client error: " << m_localSocket->errorString() << endLine();
        }
        
        RwReturnType RwCommandClientLocal::sendRequest(const RwNetDataStructures::RwCommandRequest &request)
        {
            if ( !m_connected )
            {
                rwError() << "The local client is not connected! Please connect to local server." << endLine();
                return RW_ERROR_NO_CONNECTION;
            }
            
            // SEND REQUEST
            QByteArray requestRawData;
            const RwReturnType returnMsg = request.toRawData(requestRawData);
            m_localSocket->write(requestRawData);
            
            // READ REPLY
            QByteArray replyRawData = m_localSocket->readAll();
    
            RwNetDataStructures::RwCommandReply reply;
            reply.fromRawData(replyRawData);
            
            return returnMsg;
        }
        
    }
    
}
