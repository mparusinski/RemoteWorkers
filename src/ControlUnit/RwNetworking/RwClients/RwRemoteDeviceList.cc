/* 

RwRemoteDeviceList.cc: Handles the list of available clients

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#include "RwRemoteDeviceList.h"

namespace RwNetworking {
    
    namespace RwClients {
        
        RwRemoteDeviceList::RwRemoteDeviceList(QObject* parent) : QObject(parent)
        {
            
        }
        
        RwRemoteDeviceList::~RwRemoteDeviceList()
        {
            
        }
        
        QStringList RwRemoteDeviceList::getListOfAvailableDevices()
        {
            return m_allDevices.keys();
        }
        
        RwRemoteDevice::RwRemoteDevicePtr RwRemoteDeviceList::getDevice(const RemoteDeviceNameType &deviceName)
        {
            RemoteDevicesListType::iterator iter = m_allDevices.find(deviceName);
            if (iter != m_allDevices.end())
            {
                return iter.value();
            }
            return RwRemoteDevice::RwRemoteDevicePtr();
        }
        
        void RwRemoteDeviceList::addDevice(const QString &deviceName, RwRemoteDevice::RwRemoteDevicePtr &device)
        {
            m_allDevices[deviceName] = device;
        }
        
    }
    
}
