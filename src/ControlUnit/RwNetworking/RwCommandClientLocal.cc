/* 

RwCommandClientLocal.cc: Client for RwCommandServerLocal

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/06/2012.

*/

#include "RwCommandClientLocal.h"

#include "RwUtils/RwLog/RwLogger.h"

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
        RwLogger::getInstance()->debug("RwCommandClientLocal has connected to server");
    }
    
    void RwCommandClientLocal::clientDisconnected()
    {
        RwLogger::getInstance()->debug("RwCommandClientLocal has disconnected from server");
    }
    
    void RwCommandClientLocal::readReady()
    {
        RwLogger::getInstance()->debug("RwCommandClientLocal is ready to read");
    }
    
    void RwCommandClientLocal::connectToServer()
    {
        RwLogger::getInstance()->debug("Connecting to server");
        m_localSocket->abort();
        m_localSocket->connectToServer(m_serverName);
    }
    
    void RwCommandClientLocal::disconnectFromServer()
    {
        m_localSocket->disconnectFromServer();
    }
    
    void RwCommandClientLocal::clientError(QLocalSocket::LocalSocketError socketError)
    {
        QString errorMsg = "Client error: ";
        errorMsg += m_localSocket->errorString();
        
        RwLogger::getInstance()->error_msg(errorMsg);
    }
    
}
