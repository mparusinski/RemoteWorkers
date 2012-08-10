/* 

RwCommandLocalPipeOut.cc: Allows to trigger Remote Devices handle from another program locally

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 06/08/2012.

*/

#include "RwCommandLocalPipeOut.h"

#include "RwUtils/RwGlobal/RwDefines.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwClients {
        
        RwCommandLocalPipeOut::RwCommandLocalPipeOut(QObject* parent) : QObject(parent)
        {
            m_localPipe = new QLocalSocket(this);
            m_connected = false;
            
            connect(m_localPipe, SIGNAL(connected()), this, SLOT(connected()));
            connect(m_localPipe, SIGNAL(disconnected()), this, SLOT(disconnected()));
        }
        
        RwCommandLocalPipeOut::~RwCommandLocalPipeOut()
        {
            
        }
        
        RwCommandLocalPipeOut* RwCommandLocalPipeOut::getInstance()
        {
            static RwCommandLocalPipeOut* instance = 0;
            if (instance == 0)
            {
                instance =  new RwCommandLocalPipeOut(0);
            }
            return instance;
        }
        
        void RwCommandLocalPipeOut::connected()
        {
            m_connected = true;
        }
        
        void RwCommandLocalPipeOut::disconnected()
        {
            m_connected = false;
        }
        
        void RwCommandLocalPipeOut::sendRequest(const RwNetDataStructures::RwCommandRequest& request)
        {
            if ( !m_connected )
            {
                rwError() << "The client is not connected! Please connect to server first." << endLine();
                return;
            }
            
            // SEND REQUEST
            QByteArray requestRawData;
            request.toRawData(requestRawData);
            m_localPipe->write(requestRawData);
            m_localPipe->flush();
        }
        
        void RwCommandLocalPipeOut::connectToPipe()
        {
            m_localPipe->abort();
            m_localPipe->connectToServer(RW_COMMAND_PIPE);
        }
        
        void RwCommandLocalPipeOut::disconnectFromPipe()
        {
            m_localPipe->disconnectFromServer();
        }
        
    }
    
}
