/* 

RwCommandServerSSL.h: Ssl version of the network socket

As part of the RemoteWorkers program which creates a ramework for remote
management of laptops,desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDSERVERSSL_H_
#define _RWNETWORKING_RWCOMMANDSERVERSSL_H_

#include "RwCommandServerBase.h"

#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief Command Server which intercepts commands through a TCP Socket
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandServerSSL : public RwCommandServerBase {
        
        Q_OBJECT
        
    public:
        
        RwCommandServerSSL(QObject* parent, const QString& name);
        virtual ~RwCommandServerSSL();
        
    private:
        virtual void abstract() {}
        DISALLOW_COPY_AND_ASSIGN(RwCommandServerSSL);
        
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDSERVERSSL_H_