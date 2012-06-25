/* 

RwCommandSeverTCP.cc: Listens for command over TCP

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

 */

#include "RwCommandServerTCP.h"

namespace RwNetworking {
    
    namespace RwServers {
        
        RwCommandServerTCP::RwCommandServerTCP(QObject* parent, const QString& serverName) 
        : RwCommandServerBase(parent, serverName)
        {
            
        }
        
        RwCommandServerTCP::~RwCommandServerTCP()
        {
            
        }
        
    }
    
}
