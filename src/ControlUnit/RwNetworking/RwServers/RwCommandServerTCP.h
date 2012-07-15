/* 

RwCommandSeverTCP.h: Command Server over TCP. The command server handles requests and sends back replies

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERTCP_H_
#define _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERTCP_H_

#include "RwCommandServerBase.h"

#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

#include <QTcpServer>
#include <QTcpSocket>

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwServers {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class implements a Command Server using TCP.
        ///        Command Servers handles requests and sends back responses.
        ///        The server should run in a seperate thread.
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandServerTCP : public RwCommandServerBase {
            
            Q_OBJECT
            
        public:
            
            RwCommandServerTCP(QObject* parent, const int portNumber);
            virtual ~RwCommandServerTCP();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Starts the server which listens for requests.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void start();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Stops the server which listens no more for requests
            ////////////////////////////////////////////////////////////////////////////////
            virtual void stop();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Checks if the server is currently running.
            ////////////////////////////////////////////////////////////////////////////////
            virtual bool isRunning() const;
            
        public slots:
            void processConnection(void);
            
        private:
            virtual void abstract() {}
            DISALLOW_COPY_AND_ASSIGN(RwCommandServerTCP);
            
            void init();
            
            int m_portNumber;
            QTcpServer* m_tcpServer;
            QTcpSocket* m_currentConnection;
        };
        
    }
}

#endif // _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERTCP_H_
