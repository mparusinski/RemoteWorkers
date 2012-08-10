/* 

RwCommandLocalPipeIn.cc: Allows to trigger Remote Devices handle from another program locally

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 06/08/2012.

*/

#include "RwCommandLocalPipeIn.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        RwCommandLocalPipeIn::RwCommandLocalPipeIn(QObject* parent) : QObject(parent)
        {
            m_localPipe = new QLocalServer(this);
        }
        
        RwCommandLocalPipeIn::~RwCommandLocalPipeIn()
        {
            m_localPipe->close();
            delete m_localPipe;
        }
        
        bool RwCommandLocalPipeIn::init()
        {
            if (m_localPipe->isListening())
            {
                m_localPipe->close();
            }
            
            QLocalServer::removeServer(RW_COMMAND_PIPE);
            
            if ( !m_localPipe->listen(RW_COMMAND_PIPE) )
            {
                return false;
            }
            
            connect(m_localPipe, SIGNAL(newConnection()), this, SLOT(processConnection()) );
            return true;
        }
        
        RwCommandLocalPipeIn* RwCommandLocalPipeIn::getInstance()
        {
            static RwCommandLocalPipeIn* instance = 0;
            if (instance == 0)
            {
                instance = new RwCommandLocalPipeIn(0);
            }
            return instance;
        }
        
        void RwCommandLocalPipeIn::connectToDevice(RwRemoteDevice::RwRemoteDevicePtr device)
        {
            if (m_currentDevice)
                m_currentDevice->detachPipe();
                
            disconnect(m_localPipe, SIGNAL(newConnection()), this, SLOT(processConnection()) );
            // m_localPipe->close();
            m_currentDevice = device;
            m_currentDevice->attachPipe();
            // m_localPipe->listen(RW_COMMAND_PIPE);
            connect(m_localPipe, SIGNAL(newConnection()), this, SLOT(processConnection()) );
        }
        
        void RwCommandLocalPipeIn::processConnection()
        {
            m_currentConnection = m_localPipe->nextPendingConnection();
            connect(m_currentConnection, SIGNAL(disconnected()), m_currentConnection, SLOT(deleteLater()));
            
            while (m_currentConnection->bytesAvailable() < (int)sizeof(quint32)) // waiting for at least 32 bits of data
                m_currentConnection->waitForReadyRead();
            
            QByteArray receivedData = m_currentConnection->readAll();
            
            emit sendRequest(receivedData);
            
            // m_currentDevice->connectToDevice(); // already done
            // m_currentDevice->sendRequest(receivedData); // use signal instead
        }
        
    }
    
}

