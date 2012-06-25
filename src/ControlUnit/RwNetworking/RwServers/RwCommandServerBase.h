/* 

RwCommandServerBase.h: Interface to the network socket

As part of the RemoteWorkers program which creates a ramework for remote
management of laptops,desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#ifndef _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_
#define _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_

#include <QString>
#include <QThread>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwDataStructures/RwByteArray.h"

#include "../RwNetDataStructures/RwCommandRequest.h"
#include "../RwNetDataStructures/RwCommandReply.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwServers {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This abstract class is an interface for basic server functionality
        ///        required for the Command Server (listening for commands)
        ///        Should not be instantiated
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandServerBase : public QObject {
            
            Q_OBJECT
            
        public:
            RwCommandServerBase(QObject* parent, const QString& name);
            virtual ~RwCommandServerBase();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Starts listening for commands
            ////////////////////////////////////////////////////////////////////////////////
            virtual void start() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Close the server
            ////////////////////////////////////////////////////////////////////////////////
            virtual void stop() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Checks if the server is running
            ////////////////////////////////////////////////////////////////////////////////
            virtual bool isRunning() const = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Returns the name of the server
            /// \return Return the name of the server
            ////////////////////////////////////////////////////////////////////////////////
            QString getServerName() const;
            
        protected:
            QString m_serverName;
            
            RwReturnType processData(const RwDataStructures::RwByteArray& in, RwDataStructures::RwByteArray& out) const;
            RwReturnType executeRequest(const RwNetDataStructures::RwCommandRequest& request, RwNetDataStructures::RwCommandReply& reply) const;
            
        private:
            virtual void abstract() = 0;
            DISALLOW_COPY_AND_ASSIGN(RwCommandServerBase);
        };
        
    }
    
}

#endif // _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_
