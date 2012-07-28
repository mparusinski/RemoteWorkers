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

#include "../RwSocket/RwLocalSocket.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwClients {
        
        RwCommandClientLocal::RwCommandClientLocal(QObject* parent, const QString& serverName)
        : RwCommandClientBase(parent)
        {
            m_serverName = serverName;
            m_socket = new RwSocket::RwLocalSocket(this);
            
            connectSignalAndSlots();
        }
        
        RwCommandClientLocal::~RwCommandClientLocal() 
        {
        	m_socket->abort();
            delete m_socket;
        }
        
        void RwCommandClientLocal::connectToServer()
        {
        	m_socket->abort();
        	dynamic_cast<RwSocket::RwLocalSocket*>(m_socket)->connectToServer(m_serverName);
        }
        
        void RwCommandClientLocal::disconnectFromServer()
        {
        	dynamic_cast<RwSocket::RwLocalSocket*>(m_socket)->disconnectFromServer();
        }
        
    }
    
}
