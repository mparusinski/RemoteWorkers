/* 

RwCommandLocalPipeOut.h: Allows to trigger Remote Devices handle from another program locally

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 06/08/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPEOUT_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPEOUT_H_

#include <QObject>
#include <QLocalSocket>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "../RwNetDataStructures/RwCommandRequest.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        class RwCommandLocalPipeOut : public QObject {
            
            Q_OBJECT
            
        public:
            static RwCommandLocalPipeOut* getInstance();

            virtual ~RwCommandLocalPipeOut();
            
            void sendRequest(const RwNetDataStructures::RwCommandRequest& request);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Connects to local pipe.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void connectToPipe();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Disconnects from local pipe.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void disconnectFromPipe();
            
        public slots:
            
            void connected();
            
            void disconnected();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandLocalPipeOut);
            
            RwCommandLocalPipeOut(QObject* parent);
            
            QLocalSocket* m_localPipe;
            
            bool m_connected;
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPEOUT_H_
