/* 

RwRemoteDevice.h: Encapsulate data for remote devices

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#include "RwRemoteDevice.h"

#include "RwCommandClientLocal.h"
#include "RwCommandClientSSL.h"
#include "RwCommandClientTCP.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        RwRemoteDevice::RwRemoteDevice(QObject* parent, const QString& address, const RwRemoteDevice::DeviceConnectionType deviceConnection, quint16 portNumber) : QObject(parent)
        {
            m_address = address;
            m_deviceConnection = deviceConnection;
            m_init = false;
            m_portNumber = portNumber;
            m_client = 0;
        }
        
        RwRemoteDevice::~RwRemoteDevice()
        {
            if (m_client != 0)
            {
                delete m_client;
            }
        }
        
        QString& RwRemoteDevice::getAddress()
        {
            return m_address;
        }
        
        const QString& RwRemoteDevice::getAddress() const
        {
            return m_address;
        }
        
        void RwRemoteDevice::init()
        {
            if (m_client != 0)
            {
                delete m_client;
                m_client = 0;
            }
            
            switch (m_deviceConnection) {
                case RW_DEVICE_LOCAL_PIPE:
                    m_client = new RwCommandClientLocal(this, m_address);
                    break;
                case RW_DEVICE_REMOTE_TCP:
                    m_client = new RwCommandClientTCP(this, m_address, m_portNumber);
                    break;
                case RW_DEVICE_REMOTE_SSL:
                    m_client = new RwCommandClientSSL(this, m_address, m_portNumber);
                    break;
                default:
                    m_client = 0;
                    return; // uninitialised
            }
            
            m_init = true;
        }
        
        void RwRemoteDevice::connectToDevice()
        {
            if (!m_init)
                init();
            
            m_client->connectToServer();
        }
        
        void RwRemoteDevice::disconnectFromDevice()
        {
            m_client->disconnectFromServer();
        }
        
        void RwRemoteDevice::sendRequest(const RwCommandRequest &request) const
        {
            m_client->sendRequest(request);
            connect(m_client, SIGNAL(replyReady()), this, SLOT(receivedReply()));
        }
        
        void RwRemoteDevice::getReply(RwCommandReply &reply) const
        {
            m_client->getReply(reply);
        }
        
        void RwRemoteDevice::receivedReply()
        {
            disconnect(m_client, SIGNAL(replyReady()), this, SLOT(receivedReply()));
            emit notifyOfReply();
        }
        
    }
    
}
