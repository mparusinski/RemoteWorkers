/* 

RwCommandClientLocal.h: Client for RwCommandServerLocal.

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
        /// \brief This class represents a local socket to a local Command Server.
        ///        Use only in conjunction with RwCommandServerLocal
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandClientLocal : public QObject {
            
            Q_OBJECT
            
        public:
            RwCommandClientLocal(QObject* parent, const QString& serverName);
            ~RwCommandClientLocal();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Connects to local server at server name (given at construction).
            ////////////////////////////////////////////////////////////////////////////////
            void connectToServer();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Disconnects from local server.
            ////////////////////////////////////////////////////////////////////////////////
            void disconnectFromServer();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sends a request to the local server if connected
            /// \param[in]  request Request to be procesed by remote server
            /// \return An error code corresponding to success or not
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType sendRequest(const RwNetDataStructures::RwCommandRequest& request);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Gets the reply back when available. Should be called after sendRequest
            ///        and only when the read signal was emitted.
            /// \param[out] reply  Reply obtained from request
            /// \return An error code corresponding to success or not
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType getReply(RwNetDataStructures::RwCommandReply& reply);
            
            public slots:
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Slot for when the client successfully connects
            ////////////////////////////////////////////////////////////////////////////////
            void clientConnected();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Slot for when the client disconnects from server
            ////////////////////////////////////////////////////////////////////////////////
            void clientDisconnected();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Slot for when something is available from the server
            ////////////////////////////////////////////////////////////////////////////////
            void readReady();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Slot for when something goes wrong with the connection
            ////////////////////////////////////////////////////////////////////////////////
            void clientError(QLocalSocket::LocalSocketError socketError);
            
        signals:
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Signal representing a reply 
            ////////////////////////////////////////////////////////////////////////////////
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
