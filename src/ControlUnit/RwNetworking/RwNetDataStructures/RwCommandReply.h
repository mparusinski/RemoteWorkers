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

#include <QDataStream>

#include "RwWorkerInterface/RwReply.h"

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwGlobal;
using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Class representing a reply from the main server
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandReply : public RwNetDataStructureBase {
            
        public:
            RwCommandReply();
            RwCommandReply(const RwReturnType errorCode);
            RwCommandReply(const RwWorkerInterface::RwReply::RwReplyPtr& reply);
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
            void setReply(const RwWorkerInterface::RwReply::RwReplyPtr& reply);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Copies the object from another command reply
            ////////////////////////////////////////////////////////////////////////////////
            void copyFrom(const RwCommandReply& other);
            
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
            RwWorkerInterface::RwReply::RwReplyPtr& getReply();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Get the reply out. Always check first with isError()
            /// \return Return the replies regardless of the state
            ////////////////////////////////////////////////////////////////////////////////
            const RwWorkerInterface::RwReply::RwReplyPtr& getReply() const;
            
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
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Convers the command reply to a string
            ////////////////////////////////////////////////////////////////////////////////
            virtual QString toString() const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Represents the size of the command reply in bytes
            ////////////////////////////////////////////////////////////////////////////////
            int byteSize() const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandReply);
            
            bool m_isError;
            RwReturnType m_errorCode;
            RwWorkerInterface::RwReply::RwReplyPtr m_reply;
        };
        
        inline QDataStream &operator<<(QDataStream &out, const RwCommandReply &commandReply)
        {
            const bool isError = commandReply.isError();
            out << isError;
            
            if (isError)
            {
                out << commandReply.getErrorCode();
            }
            else
            {
                out << commandReply.getReply()->getRawData();
            }
            
            return out;
        }
        
        inline QDataStream &operator>>(QDataStream &in, RwCommandReply &commandReply)
        {
            bool isError;
            in >> isError;
            
            if (isError)
            {
                RwReturnType errorCode;
                in >> errorCode;
                commandReply.setErrorCode(errorCode);
            }
            else
            {                
                RwWorkerInterface::RwReply::RwReplyPtr reply(new RwWorkerInterface::RwReply);
                in >> reply->getRawData();
                commandReply.setReply(reply);
            }
            
            return in;
        }
        
        inline RwWriter &operator<<(RwWriter &writer, RwCommandReply& commandReply)
        {
            return writer.operator<<(commandReply.toString());
        }
        
    }
    
}

#endif // _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREPLY_H_
