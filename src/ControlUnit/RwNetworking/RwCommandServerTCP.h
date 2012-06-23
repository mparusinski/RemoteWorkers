/* 

RwCommandSeverTCP.h: Listens for command over TCP

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDSERVERTCP_H_
#define _RWNETWORKING_RWCOMMANDSERVERTCP_H_

#include "RwCommandServerBase.h"

#include "RwUtils/RwProgramming/RwReturn.h"
#include "RwUtils/RwProgramming/RwClasses.h"

using namespace RwUtils::RwProgramming;

namespace RwNetworking {
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief Command Server which intercepts commands through a TCP Socket
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandServerTCP : public RwCommandServerBase {
        
        Q_OBJECT
        
    public:
        
        RwCommandServerTCP(QObject* parent, const QString& name);
        virtual ~RwCommandServerTCP();
        
    private:
        virtual void abstract() {}
        DISALLOW_COPY_AND_ASSIGN(RwCommandServerTCP);
        
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDSERVERTCP_H_
