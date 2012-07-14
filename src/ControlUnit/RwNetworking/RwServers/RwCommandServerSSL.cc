/* 

RwCommandServerSsl.cc: Ssl version of the network socket

As part of the RemoteWorkers program which creates a ramework for remote
management of laptops,desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#include "RwCommandServerSSL.h"

namespace RwNetworking {
    
    namespace RwServers {
        
        RwCommandServerSSL::RwCommandServerSSL(QObject* parent, const QString& serverName) 
        : RwCommandServerBase(parent, serverName)
        {
            
        }
        
        RwCommandServerSSL::~RwCommandServerSSL()
        {
            
        }
        
    }
    
}
