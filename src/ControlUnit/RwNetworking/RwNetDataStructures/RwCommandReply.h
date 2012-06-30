/* 

RwCommandReply.h: Represents a reply from server after a worker executed a command

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
        /// \brief Class representing a reply from the main server
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandReply : public RwNetDataStructureBase {
            
        public:
            RwCommandReply();
            RwCommandReply(const RwReturnType errorCode);
            RwCommandReply(const RwWorkerInterface::RwReply& reply);
            virtual ~RwCommandReply();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Turns the reply structure into an error code.
            /// \param[in]  errorCode Error code
            ////////////////////////////////////////////////////////////////////////////////
            void setErrorCode(const RwReturnType errorCode);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Turns the reply structure into a reply.
            /// \param[in] errorCode Error code
            ////////////////////////////////////////////////////////////////////////////////
            void setReply(const RwWorkerInterface::RwReply& reply);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Copies the object from another command reply
            ////////////////////////////////////////////////////////////////////////////////
            void copyFrom(const RwCommandReply& other);
            
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
            /// \brief Returns the error code. Always check first with isError()
            /// \return Returns the error code regardless of the state.
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType getErrorCode() const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Tells is the reply represents an error
            ////////////////////////////////////////////////////////////////////////////////
            bool isError() const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Get the reply out. Always check first with isError()
            /// \return Return the replies regardless of the state
            ////////////////////////////////////////////////////////////////////////////////
            RwWorkerInterface::RwReply& getReply();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Get the reply out. Always check first with isError()
            /// \return Return the replies regardless of the state
            ////////////////////////////////////////////////////////////////////////////////
            const RwWorkerInterface::RwReply& getReply() const;
            
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
            DISALLOW_COPY_AND_ASSIGN(RwCommandReply);
            
            bool m_isError;
            RwReturnType m_errorCode;
            RwWorkerInterface::RwReply m_reply;
        };
        
    }
    
}

#endif // _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREPLY_H_
