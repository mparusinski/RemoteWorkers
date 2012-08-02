/* 

RwRemoteDevicesMode.cc: Remote Devices mode (part of the GUI) for interacting with remote devices. Inherits RwAbstractMode

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

 */

#include "RwRemoteDevicesMode.h"

#include "RwNetworking/RwClients/RwRemoteDeviceList.h"

using namespace RwNetworking::RwClients;

namespace RwGUI {
    
    RwRemoteDevicesMode::RwRemoteDevicesMode(QWidget* parent, QToolBar* toolBar, int index) : RwAbstractMode(parent, toolBar, index)
    {
        m_modeName = "Remote Devices Mode";
        
        setAction();
        setLayout();
        
        initRemoteDevices();
        
        attach();
    }
    
    RwRemoteDevicesMode::~RwRemoteDevicesMode()
    {
        
    }
    
    void RwRemoteDevicesMode::setAction()
    {
        m_action = new QAction(tr("Remote Devices"), this); // TODO ADD ICON
        m_action->setToolTip(tr("Interact with remote devices"));
    }
    
    void RwRemoteDevicesMode::setLayout()
    {
        m_mainLayout = new QHBoxLayout(this);
        
        m_devices = new QListWidget(this);
        m_mainLayout->addWidget(m_devices, 3);
        
        m_remoteWorkers = new QListWidget(this);
        m_remoteWorkers->setViewMode(QListView::IconMode);
        m_mainLayout->addWidget(m_remoteWorkers, 7);
    }
    
    void RwRemoteDevicesMode::initRemoteDevices()
    {
        RwRemoteDeviceList::getInstance()->readDeviceListFromFile();
        
        QStringList deviceNames = RwRemoteDeviceList::getInstance()->getListOfAvailableDevices();
        
        int numOfDevices = deviceNames.length();
        for (int i = 0; i < numOfDevices; ++i)
        {
            m_devices->addItem(deviceNames[i]);
        }
    }
    
}
