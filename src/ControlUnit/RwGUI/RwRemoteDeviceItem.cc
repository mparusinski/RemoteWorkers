/* 

RwRemoteDeviceItem.cc: Item representing a remote device

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 03/08/2012

*/

#include "RwRemoteDeviceItem.h"

namespace RwGUI { 
    
    RwRemoteDeviceItem::RwRemoteDeviceItem(QListWidget* parent, const QString& deviceName, RwRemoteDevice::RwRemoteDevicePtr pointerToDevice)
    : QListWidgetItem(deviceName, parent, UserType)
    {
        m_deviceName = deviceName;
        m_pointerToDevice = pointerToDevice;
    }
    
    RwRemoteDeviceItem::~RwRemoteDeviceItem()
    {
        
    }
    
    RwRemoteDevice::RwRemoteDevicePtr& RwRemoteDeviceItem::getPointerToDevice()
    {
        return m_pointerToDevice;
    }
    
    const RwRemoteDevice::RwRemoteDevicePtr& RwRemoteDeviceItem::getPointerToDevice() const
    {
        return m_pointerToDevice;
    }
    
    QString& RwRemoteDeviceItem::getDeviceName()
    {
        return m_deviceName;
    }
    
    const QString& RwRemoteDeviceItem::getDeviceName() const
    {
        return m_deviceName;
    }
    
}
