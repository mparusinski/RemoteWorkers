/* 

RwCommandClientLocal.h: Client for RwCommandServerLocal

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/06/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTLOCAL_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTLOCAL_H_

#include <QObject>

#include <QString>
#include <QLocalSocket>

#include "../RwNetDataStructures/RwCommandRequest.h"
#include "../RwNetDataStructures/RwCommandReply.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking  {
    
    namespace RwClients {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class represents a local client. This allows to interact with 
        ///        the server even outside the network. Use it with RwCommandServerLocal
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandClientLocal : public QObject {
            
            Q_OBJECT
            
        public:
            RwCommandClientLocal(QObject* parent, const QString& serverName);
            ~RwCommandClientLocal();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Connects to server
            ////////////////////////////////////////////////////////////////////////////////
            void connectToServer();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Disconnects from server
            ////////////////////////////////////////////////////////////////////////////////
            void disconnectFromServer();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sends a request to server if connected
            /// \param[in]  request Request to be procesed by remote server
            /// \return error code corresponding to success or not
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType sendRequest(const RwNetDataStructures::RwCommandRequest& request);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Gets the reply back when available. (BLOCKING)
            /// \param[out] reply   Reply obtained from request
            /// \return error code corresponding to success or not
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType getReply(RwNetDataStructures::RwCommandReply& reply);
            
            public slots:
            void clientConnected();
            void clientDisconnected();
            void readReady();
            void clientError(QLocalSocket::LocalSocketError socketError);
            
        signals:
            void replyReady();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandClientLocal);
            
            bool m_connected;
            QString m_serverName;
            QLocalSocket* m_localSocket;
            RwNetDataStructures::RwCommandReply m_reply;
        };
        
    }
    
}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTLOCAL_H_
