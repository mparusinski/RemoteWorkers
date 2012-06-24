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
        /// \brief Convers the request into raw data suitable for transmission
        /// \param[out] rawData Data that will represent the request
        /// \return Error message if applicable
        ////////////////////////////////////////////////////////////////////////////////
        RwReturnType toRawData(RwDataStructures::RwByteArray& rawData) const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Convers the raw data into a request if correctly formed
        /// \param[in] rawData Data that will represent the request
        /// \return Error message if applicable
        ////////////////////////////////////////////////////////////////////////////////
        RwReturnType fromRawData(const RwDataStructures::RwByteArray& rawData);
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Return the name of worker represented by the request
        /// \return The worker name
        ////////////////////////////////////////////////////////////////////////////////
        QString getWorkerName() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Return the command represented by the command
        /// \return The command
        ////////////////////////////////////////////////////////////////////////////////
        RwCommand getCommand() const;
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwCommandRequest);
        
        QString m_workerName; // Not an actual worker
        RwCommand m_command;
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDREQUEST_H_
