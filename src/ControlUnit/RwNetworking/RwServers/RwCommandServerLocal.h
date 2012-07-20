/* 

RwCommandServerLocal.h: Command Server over Local pipes. The command server handles requests and sends back replies

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERLOCAL_H_
#define _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERLOCAL_H_

#include "RwCommandServerBase.h"

#include <QString>
#include <QLocalServer>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwWorkerInterface/RwReply.h"

using namespace RwWorkerInterface;
using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwServers {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class implements a Command Server using Local pipes.
        ///        Command Servers handles requests and sends back responses.
        ///        The server should run in a seperate thread.
        ///        Can not be used over the network. Useful for testing.
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandServerLocal : public RwCommandServerBase<QLocalSocket>
        {
            Q_OBJECT
            
        public:
            RwCommandServerLocal(QObject* parent, const QString& serverName);
            virtual ~RwCommandServerLocal();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Starts the server which listens for requests.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void start();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Stops the server which listens no more for requests
            ////////////////////////////////////////////////////////////////////////////////
            virtual void stop();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Checks if the server is currently running.
            ////////////////////////////////////////////////////////////////////////////////
            virtual bool isRunning() const;
            
        public slots:
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Slot dedicated to process the connection when received from server.
            ////////////////////////////////////////////////////////////////////////////////
            void processConnection();
            
            void caughtError(QLocalSocket::LocalSocketError error);

        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandServerLocal);
            
            void init();
            
            QString m_serverName;
            QLocalServer* m_localServer;
        };
        
    }
    
}

#endif // _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERLOCAL_H_
