/* 

RwRemoteDevice.h: Encapsulate data for remote devices

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICE_H_
#define _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICE_H_

#include <QObject>
#include <QSharedPointer>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwDefines.h"

#include "../RwNetDataStructures/RwCommandRequest.h"
#include "../RwNetDataStructures/RwCommandReply.h"

#include "RwCommandClientBase.h"

using namespace RwUtils::RwGlobal;
using namespace RwNetworking::RwNetDataStructures;

namespace RwNetworking {
    
    namespace RwClients {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Encapsulates a remote device accessible through a suitable client.
        ///        This class hides the actual implementation of the client.
        ///        Use this class to communicate with a remote device.
        ///        A device has three main fields:
        ///          -> A name for the device (for the user)
        ///          -> An address: Domain Name or IP address for Network devices
        ///                         Pipe Name for Local devices
        ///          -> A type field identifying the type of device
        ////////////////////////////////////////////////////////////////////////////////
        class RwRemoteDevice : public QObject {
            
            Q_OBJECT
            
        public:
            typedef QSharedPointer<RwRemoteDevice> RwRemoteDevicePtr;
            
            typedef enum {
                RW_DEVICE_LOCAL_PIPE = 1,
                RW_DEVICE_REMOTE_TCP = 2,
                RW_DEVICE_REMOTE_SSL = 3
            } DeviceConnectionType;
            
            RwRemoteDevice(QObject* parent, const QString& address, const DeviceConnectionType deviceConnection, quint16 m_portNumber = RW_COMMUNICATION_PORT);
            
            virtual ~RwRemoteDevice();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the address (or name of local pipe) of the device
            /// \return Address
            ////////////////////////////////////////////////////////////////////////////////
            QString& getAddress();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the address (or name of local pipe) of the device
            /// \return Address
            ////////////////////////////////////////////////////////////////////////////////
            const QString& getAddress() const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Connects to remote device. Function was named connectToDevice() and
            ///        not connect() to avoid confusion with QT method connect()
            ////////////////////////////////////////////////////////////////////////////////
            void connectToDevice();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Disconnects from remote device. Function was named disconnectFromDevice()
            ///        and not disconnect() to avoid confusion with QT method disconnect()
            ////////////////////////////////////////////////////////////////////////////////
            void disconnectFromDevice();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sends a request to the remote device.
            /// \param[in] request The request to send to the remote device
            ////////////////////////////////////////////////////////////////////////////////
            void sendRequest(const RwCommandRequest& request) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Sends a request to the remote device and gets back a reply
            /// \param[out] request The request to send to the remote device
            ////////////////////////////////////////////////////////////////////////////////
            void getReply(RwCommandReply& reply) const;
            
        public slots:
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Propagate signal further
            ////////////////////////////////////////////////////////////////////////////////
            void receivedReply();
            
        signals:
            
            void notifyOfReply();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwRemoteDevice);
            
            void init();
            
            QString m_address; // or pipe depending if local or not
            DeviceConnectionType m_deviceConnection;
            
            bool m_init;
            quint16 m_portNumber;
            
            RwCommandClientBase* m_client;
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICE_H_
