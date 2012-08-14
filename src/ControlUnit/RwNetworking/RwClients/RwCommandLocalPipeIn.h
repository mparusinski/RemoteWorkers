/* 

RwCommandLocalPipeIn.h: Allows to trigger Remote Devices handle from another program locally

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 06/08/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPEIN_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPEIN_H_

#include <QLocalServer>
#include <QLocalSocket>
#include <QString>
#include <QObject>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "../RwNetDataStructures/RwCommandRequest.h"

#include "RwRemoteDevice.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        class RwCommandLocalPipeIn : public QObject {
          
            Q_OBJECT
            
        public:
            static RwCommandLocalPipeIn* getInstance();
            
            bool init();
            
            void connectToDevice(RwRemoteDevice::RwRemoteDevicePtr device);
            
            virtual ~RwCommandLocalPipeIn();
            
        public slots:
            
            void processConnection();
            
        signals:
            
            void sendRequest(RwCommandRequest::RwCommandRequestPtr);
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandLocalPipeIn);
            
            RwCommandLocalPipeIn(QObject* parent);
            
            RwRemoteDevice::RwRemoteDevicePtr m_currentDevice;
            
            QLocalServer* m_localPipe;
            
            QLocalSocket* m_currentConnection;
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDLOCALPIPEIN_H_
