/* 

RwCommandClientLocal.h: Client for RwCommandServerLocal.

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/06/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTLOCAL_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTLOCAL_H_

#include "RwCommandClientBase.h"

#include <QString>

#include "../RwNetDataStructures/RwCommandRequest.h"
#include "../RwNetDataStructures/RwCommandReply.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking  {
    
    namespace RwClients {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class represents a local socket to a local Command Server.
        ///        Use only in conjunction with RwCommandServerLocal
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandClientLocal : public RwCommandClientBase {
            
            Q_OBJECT
            
        public:
            RwCommandClientLocal(QObject* parent, const QString& serverName);
            virtual ~RwCommandClientLocal();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Connects to local server at server name (given at construction).
            ////////////////////////////////////////////////////////////////////////////////
            virtual void connectToServer();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Disconnects from local server.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void disconnectFromServer();
            
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandClientLocal);
            
            QString m_serverName;
        };
        
    }
    
}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTLOCAL_H_
