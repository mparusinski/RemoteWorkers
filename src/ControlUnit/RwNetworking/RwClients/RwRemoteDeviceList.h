/* 

RwRemoteDeviceList.h: Handles the list of available clients

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICELIST_H_
#define _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICELIST_H_

#include <QString>
#include <QMap>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

#include "RwRemoteDevice.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Represents the list of devices that are available.
        ///        The list of devices is read from a file but the user can add or remove
        ///        remote devices.
        ////////////////////////////////////////////////////////////////////////////////
        class RwRemoteDeviceList{
            
        public:
            typedef QString RemoteDeviceNameType;
            
            typedef QMap<RemoteDeviceNameType, RwRemoteDevice::RwRemoteDevicePtr> RemoteDevicesListType;
            
            static RwRemoteDeviceList* getInstance();
            
            QStringList getListOfAvailableDevices();
            
            RwRemoteDevice::RwRemoteDevicePtr getDevice(const RemoteDeviceNameType& deviceName);
            
            void addDevice(const QString& deviceName, RwRemoteDevice::RwRemoteDevicePtr& device);
            
            RwReturnType readDeviceListFromFile();
            
            RwReturnType saveDeviceListToFile();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwRemoteDeviceList);
            
            RwRemoteDeviceList();
            
            virtual ~RwRemoteDeviceList();
            
            RemoteDevicesListType m_allDevices;
            
        };
        
    }

}

#endif // _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICELIST_H_
