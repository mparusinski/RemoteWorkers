/* 

RwCommandClientBase.h: Base class for all command clients

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTBASE_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTBASE_H_

#include <QObject>
#include <QByteArray>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

#include "../RwNetDataStructures/RwCommandReply.h"
#include "../RwNetDataStructures/RwCommandRequest.h"

#include "../RwSocket/RwAbstractSocket.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwClients {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Abstract base class for command clients (see RwCommandServer).
        ///        Handles communication between localhost and a remote device
        ///        running remote workers.
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandClientBase : public QObject {
            
            Q_OBJECT
            
        public:
            RwCommandClientBase(QObject* parent);
            virtual ~RwCommandClientBase();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Connects to local server at server name (given at construction).
            ////////////////////////////////////////////////////////////////////////////////
            virtual void connectToServer() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Disconnects from local server.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void disconnectFromServer() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sends a request to the local server if connected
            /// \param[in]  request Request to be procesed by remote server
            /// \return An error code corresponding to success or not
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType sendRequest(const RwNetDataStructures::RwCommandRequest& request);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sends a request to the local server if connected
            /// \param[in] request Request to be procesed by remote server, in QByteArray formats
            /// \return An error code corresponding to success or not
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType sendRequest(QByteArray& requestInRawFormat);
            
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
            
        signals:
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Signal representing a reply
            ////////////////////////////////////////////////////////////////////////////////
            void replyReady();
            
        protected:
            bool m_connected;
            RwSocket::RwAbstractSocket* m_socket;
            RwNetDataStructures::RwCommandReply m_reply;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Common function for subclass. It connects all common signals and slots.
            ////////////////////////////////////////////////////////////////////////////////
            void connectSignalAndSlots();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandClientBase);
            bool m_readingBlock;
            quint32 m_blockSize;
            QByteArray m_commandReplyBlock;
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTBASE_H_
