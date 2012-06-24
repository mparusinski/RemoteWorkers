/* 

RwCommandReply.h: Represents a reply from server after a worker executes a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDREPLY_H_
#define _RWNETWORKING_RWCOMMANDREPLY_H_

#include "RwWorkerInterface/RwReply.h"

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

#define REPLY_BEGIN "BEGIN"
#define REPLY_TYPE "TYPE"
#define REPLY_ERROR "ERROR"
#define REPLY_ERROR_MESSAGE "ERROR_MESSAGE"
#define REPLY_REPLY "REPLY"
#define REPLY_FILES_NUMBER "FILESNUMBER"
#define REPLY_FILENAME "FILENAME"
#define REPLY_CONTENT "CONTENT"
#define REPLY_CONTENT_SIZE "CONTENT_SIZE"
#define REPLY_DEFINE " "
#define REPLY_NEW_SECTION "\n"
#define REPLY_END "END"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief RwCommandReply represents the reply after executing a worker
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandReply {
        
    public:
        RwCommandReply();
        RwCommandReply(RwReturnType errorCode);
        RwCommandReply(const RwWorkerInterface::RwReply& reply);
        ~RwCommandReply();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Turns the reply into a well formed string representing it
        ////////////////////////////////////////////////////////////////////////////////
        QString toString() const;
        
    private:
        // DISALLOW_COPY_AND_ASSIGN(RwCommandReply);
        
        bool m_isError;
        RwReturnType m_errorCode;
        RwWorkerInterface::RwReply m_reply;
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDREPLY_H_
