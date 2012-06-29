/* 

RwCommandRequest.h: Represents a request to a server to have a worker execute a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREQUEST_H_
#define _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREQUEST_H_

#include "RwNetDataStructureBase.h"

#include "RwWorkerInterface/RwCommand.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

using namespace RwWorkerInterface;
using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief RwCommandRequest represents command a remote worker needs to execute
        ///        The main purpose of this object is to convert the request into
        ///        a suitable byte array.
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandRequest : public RwNetDataStructureBase {
            
        public:
            RwCommandRequest();
            RwCommandRequest(const QString& workerName, const RwCommand& command);
            virtual ~RwCommandRequest();
            
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
            const RwCommand& getCommand() const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sets the command
            ////////////////////////////////////////////////////////////////////////////////
            void setCommand(const RwCommand& command);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Converts the request from raw data
            /// \param[int] rawData rawData representing the request
            /// \return Error code
            ////////////////////////////////////////////////////////////////////////////////
            virtual RwReturnType fromRawData(const QByteArray& rawData);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Converts the request into rawData
            /// \param[out] rawData rawData representing the request
            /// \return Error code
            ////////////////////////////////////////////////////////////////////////////////
            virtual RwReturnType toRawData(QByteArray& rawData) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief FOR TESTING PURPOSES MAINLY
            ////////////////////////////////////////////////////////////////////////////////
            bool operator==(const RwCommandRequest& other) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief FOR TESTING PURPOSES MAINLY
            ////////////////////////////////////////////////////////////////////////////////
            inline bool operator!=(const RwCommandRequest& other) const
            {
                return !(*this == other);
            }

            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandRequest);
            
            QString m_workerName; // Not an actual worker
            RwCommand m_command;
        };
        
    }
}

#endif // _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREQUEST_H_
