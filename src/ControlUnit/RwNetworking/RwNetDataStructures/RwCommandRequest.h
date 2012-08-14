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

#include <QSharedPointer>

#include "RwWorkerInterface/RwCommand.h"

#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwWorkerInterface;
using namespace RwUtils::RwGlobal;
using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief RwCommandRequest represents a command to a remote worker.
        ///        The main purpose of this object is to convert the request into
        ///        a suitable byte array, which can be sent over the network.
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandRequest : public RwNetDataStructureBase {
            
        public:
            
            typedef QSharedPointer<RwCommandRequest> RwCommandRequestPtr;
            
            RwCommandRequest();
            RwCommandRequest(const QString& workerName, const RwCommand::RwCommandPtr& command);
            virtual ~RwCommandRequest();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Return the name of worker represented by the request
            /// \return The worker name
            ////////////////////////////////////////////////////////////////////////////////
            QString getWorkerName() const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sets the worker name in the request
            ////////////////////////////////////////////////////////////////////////////////
            void setWorkerName(const QString& workerName);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Return the command represented by the request
            /// \return The command
            ////////////////////////////////////////////////////////////////////////////////
            const RwCommand::RwCommandPtr& getCommand() const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sets the command
            ////////////////////////////////////////////////////////////////////////////////
            void setCommand(const RwCommand::RwCommandPtr& command);
            
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

            
            virtual QString toString() const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandRequest);
            
            QString m_workerName; // Not an actual worker
            RwCommand::RwCommandPtr m_command;
        };
        
        
        inline QDataStream &operator<<(QDataStream &out, const RwCommandRequest &commandRequest)
        {
            out << commandRequest.getWorkerName();
            const RwCommand::RwCommandPtr& command = commandRequest.getCommand();
            out << command->getOrder();
            out << command->getArguments();
            return out;
        }
        
        inline QDataStream &operator>>(QDataStream &in, RwCommandRequest &commandRequest)
        {
            QString workerName, order;
            QStringList arguments;
            in >> workerName;
            in >> order;
            in >> arguments;
            commandRequest.setWorkerName(workerName);
            RwCommand::RwCommandPtr command(new RwCommand(order, arguments));
            commandRequest.setCommand(command);
            return in;
        }
        
        inline RwWriter &operator<<(RwWriter &writer, RwCommandRequest& commandRequest)
        {
            return writer.operator<<(commandRequest.toString());
        }
    }
}

#endif // _RWNETWORKING_RWNETDATASTRUCTURES_RWCOMMANDREQUEST_H_
