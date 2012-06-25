/* 

RwCommandReply.h: Represents a reply from server after a worker executes a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREPLY_H_
#define _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREPLY_H_

#include "RwNetDataStructureBase.h"

#include "RwWorkerInterface/RwReply.h"

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief RwCommandReply represents the reply after executing a worker
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandReply : public RwNetDataStructureBase {
            
        public:
            RwCommandReply();
            RwCommandReply(RwReturnType errorCode);
            RwCommandReply(const RwWorkerInterface::RwReply& reply);
            virtual ~RwCommandReply();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Reads a reply from raw data
            /// \param[in]  rawData The raw data representing the CommandReply
            /// \return An error code representing the error occurred
            ////////////////////////////////////////////////////////////////////////////////
            virtual RwReturnType fromRawData(const QByteArray &rawData);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Converts the request to raw data
            /// \param[out]  rawData The raw data representing the CommandRequest
            /// \return An error code representing the error occurred
            ////////////////////////////////////////////////////////////////////////////////
            virtual RwReturnType toRawData(QByteArray& rawData) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Get the reply out of this class if applicable
            /// \param[out]  reply The reply represented by this class if the class doesn't represent an error
            /// \return Return false if the class represents an error
            ////////////////////////////////////////////////////////////////////////////////
            bool getReply(RwWorkerInterface::RwReply& reply) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief FOR TESTING PURPOSES MAINLY
            ////////////////////////////////////////////////////////////////////////////////
            bool operator==(const RwCommandReply& other) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief FOR TESTING PURPOSES MAINLY
            ////////////////////////////////////////////////////////////////////////////////
            inline bool operator!=(const RwCommandReply& other) const
            {
                return !(*this == other);
            }
            
        private:
            // DISALLOW_COPY_AND_ASSIGN(RwCommandReply);
            
            bool m_isError;
            RwReturnType m_errorCode;
            RwWorkerInterface::RwReply m_reply;
        };
        
    }
    
}

#endif // _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREPLY_H_
