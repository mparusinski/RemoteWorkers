/* 

RwRemoteDeviceItem.h: Item representing a remote device

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 03/08/2012.

*/

#ifndef _RWGUI_RWREMOTEDEVICEITEM_H_
#define _RWGUI_RWREMOTEDEVICEITEM_H_

#include <QListWidgetItem>

#include <QString>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwNetworking/RwClients/RwRemoteDevice.h"

using namespace RwNetworking::RwClients;

namespace RwGUI {
    
    class RwRemoteDeviceItem : public QListWidgetItem {
        
    public:
        
        RwRemoteDeviceItem(QListWidget* parent, const QString& deviceName, RwRemoteDevice::RwRemoteDevicePtr pointerToDevice);
        
        virtual ~RwRemoteDeviceItem();
        
        RwRemoteDevice::RwRemoteDevicePtr& getPointerToDevice();
        
        const RwRemoteDevice::RwRemoteDevicePtr& getPointerToDevice() const;
        
        QString& getDeviceName();
        
        const QString& getDeviceName() const;
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwRemoteDeviceItem);
        
        QString m_deviceName;
        RwRemoteDevice::RwRemoteDevicePtr m_pointerToDevice;
        
    };
    
}

#endif // _RWGUI_RWREMOTEDEVICEITEM_H_
