/* 

RwCommandRequest.h: Represents a request to a server to have a worker execute a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDREQUEST_H_
#define _RWNETWORKING_RWCOMMANDREQUEST_H_

#include <QString>

#include "RwWorkerInterface/RwCommand.h"
#include "RwDataStructures/RwByteArray.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

#define REQUEST_BEGIN "BEGIN"
#define REQUEST_END   "END"
#define REQUEST_RW_VERSION "RW_VERSION"
#define REQUEST_WORKER  "WORKER"
#define REQUEST_ORDER   "ORDER"
#define REQUEST_ARG_NUMBER "ARG_NUMBER"
#define REQUEST_ARG "ARG"
#define REQUEST_DEFINE " "
#define REQUEST_NEW_SECTION "\n";

using namespace RwWorkerInterface;
using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief RwCommandRequest represents command a remote worker needs to execute
    ///        The main purpose of this object is to convert the request into
    ///        a suitable byte array.
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandRequest {
        
    public:
        RwCommandRequest();
        RwCommandRequest(const QString& workerName, const RwCommand& command);
        ~RwCommandRequest();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Return the name of worker represented by the request
        /// \return The worker name
        ////////////////////////////////////////////////////////////////////////////////
        QString getWorkerName() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets the worker name
        ////////////////////////////////////////////////////////////////////////////////
        void setWorkerName(const QString& workerName);
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Return the command represented by the command
        /// \return The command
        ////////////////////////////////////////////////////////////////////////////////
        RwCommand getCommand() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets the command
        ////////////////////////////////////////////////////////////////////////////////
        void setCommand(const RwCommand& command);
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Converts the message into a QString
        /// \return String representing the request
        ////////////////////////////////////////////////////////////////////////////////
        QString toString() const;
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwCommandRequest);
        
        QString m_workerName; // Not an actual worker
        RwCommand m_command;
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDREQUEST_H_
