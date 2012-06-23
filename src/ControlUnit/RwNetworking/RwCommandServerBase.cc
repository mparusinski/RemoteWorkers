/* 

RwCommandServerBase.cc: Interface to the network socket

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#include "RwCommandServerBase.h"

namespace RwNetworking {

    RwCommandServerBase::RwCommandServerBase(QObject* parent, const QString& serverName) 
        : QObject(parent)
    {
        m_serverName = serverName;
    }
    
    RwCommandServerBase::~RwCommandServerBase()
    {
        
    }
    
    QString RwCommandServerBase::getServerName() const
    {
        return m_serverName;
    }
    
}
