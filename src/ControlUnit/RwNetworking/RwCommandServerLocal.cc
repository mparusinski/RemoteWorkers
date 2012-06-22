/* 

RwCommandServerLocal.cc: Emulates a local command server

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandServerLocal.h"

#include "RwUtils/RwLog/RwLogger.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    RwCommandServerLocal::RwCommandServerLocal(const QString& serverName) : 
        RwCommandServerBase(serverName)
    {
        
    }
    
    RwCommandServerLocal::~RwCommandServerLocal()
    {
        
    }
    
    RwReturnType RwCommandServerLocal::listen()
    {
        if ( m_localServer.listen(m_serverName) )
        {
            init();
            return RW_NO_ERROR;
        } else {
            return RW_ERROR_SERVER_ALREADY_STARTED;
        }
    }
    
    bool RwCommandServerLocal::isListening() const
    {
        return m_localServer.isListening();
    }
    
    RwReturnType RwCommandServerLocal::close()
    {
        m_localServer.close();
        return RW_NO_ERROR;
    }
    
    void RwCommandServerLocal::simpleTest() const
    {
        RwLogger::getInstance()->log("Test passed");
    }
 
    void RwCommandServerLocal::init()
    {
        QObject::connect(m_localServer, SIGNAL(newConnection()), this, SLOT(simpleTest()))
    }
    
}

