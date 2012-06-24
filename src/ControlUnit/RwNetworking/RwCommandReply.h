/* 

RwCommandReply.h: Represents a reply from server after a worker executes a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDREPLY_H_
#define _RWNETWORKING_RWCOMMANDREPLY_H_

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief RwCommandReply represents the reply after executing a worker
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandReply {
        
    public:
        RwCommandReply();
        ~RwCommandReply();
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwCommandReply);
        
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDREPLY_H_
