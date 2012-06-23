/* 

RwCommandClientLocal.cc: Client for RwCommandServerLocal

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/06/2012.

*/

#include "RwCommandClientLocal.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    RwCommandClientLocal::RwCommandClientLocal(QObject* parent, const QString& serverName)
        : QObject(parent) 
    {
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
        rwDebug() << "local client has connected to server " << m_serverName << endLine();
    }
    
    void RwCommandClientLocal::clientDisconnected()
    {
        rwDebug() << "local client has disconnected from server " << m_serverName << endLine();
    }
    
    void RwCommandClientLocal::readReady()
    {
        rwDebug() << "local client is ready to read" << endLine();
    }
    
    void RwCommandClientLocal::connectToServer()
    {
        m_localSocket->abort();
        rwDebug() << "Connecting to server " << m_serverName << endLine();
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
    
}
