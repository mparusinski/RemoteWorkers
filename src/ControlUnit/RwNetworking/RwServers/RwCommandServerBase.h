/* 

RwCommandServerBase.h: Abstract base class for the functionality of the command server
                       The command server handles requests and sends back replies

As part of the RemoteWorkers program which creates a ramework for remote
management of laptops,desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#ifndef _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_
#define _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_

#include <QString>
#include <QAbstractSocket>
#include <QLocalSocket>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "../RwNetDataStructures/RwCommandRequest.h"
#include "../RwNetDataStructures/RwCommandReply.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwServers {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This abstract class is a base class for all Command Server.
        ///        Command Servers handles requests and sends back responses.
        ///        The server should run in a seperate thread.
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandServerBase : public QObject {
            
            Q_OBJECT
            
        public:
            RwCommandServerBase(QObject* parent);
            virtual ~RwCommandServerBase();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Starts the server which listens for requests.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void start() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Stops the server which listens no more for requests
            ////////////////////////////////////////////////////////////////////////////////
            virtual void stop() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Checks if the server is currently running.
            ////////////////////////////////////////////////////////////////////////////////
            virtual bool isRunning() const = 0;
            
        protected:
            bool m_pendingConnection;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Process the data, the data coming in represents the request,
            ///         the data coming represents the response. Each in raw format.
            /// \param[in]  in  Represents the request in raw format
            /// \param[out] out Represents the response in raw format
            /// \return Returns an error code telling if any error did occur
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType processData(const QByteArray& in, QByteArray& out) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Executes the request and return the response
            /// \param[in]  request  Represents the request
            /// \param[out] reply    Represents the response
            /// \return Returns an error code telling if any error did occur
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType executeRequest(const RwNetDataStructures::RwCommandRequest& request, RwNetDataStructures::RwCommandReply& reply) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Processes the connection regardless of the type of socket
            /// \param[in] abstractSocket Represents the socket to be handled
            ////////////////////////////////////////////////////////////////////////////////
            template <typename SocketType>
            void abstractProcessConnection(SocketType* abstractSocket) const;
            
        private:
            virtual void abstract() = 0;
            DISALLOW_COPY_AND_ASSIGN(RwCommandServerBase);
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_
