/* 

RwRemoteDevicesMode.cc: Remote Devices mode (part of the GUI) for interacting with remote devices. Inherits RwAbstractMode

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

 */

#include "RwRemoteDevicesMode.h"

#include <QDir>
#include <QMessageBox>

#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwGlobal/RwDefines.h"

#include "RwWorkerInterface/RwCommand.h"
#include "RwWorkerInterface/RwReply.h"

#include "RwNetworking/RwClients/RwRemoteDeviceList.h"
#include "RwNetworking/RwNetDataStructures/RwCommandRequest.h"
#include "RwNetworking/RwNetDataStructures/RwCommandReply.h"

using namespace RwUtils::RwLog;
using namespace RwNetworking::RwClients;
using namespace RwNetworking::RwNetDataStructures;

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
        
        m_remoteWorkers = new QWebView(this);
        
        // m_remoteWorkers->setViewMode(QListView::IconMode);
        m_mainLayout->addWidget(m_remoteWorkers, 7);
    }
    
    void RwRemoteDevicesMode::initRemoteDevices()
    {
        typedef RwRemoteDeviceList::RemoteDevicesListType::const_iterator IteratorType;
        
        RwRemoteDeviceList::getInstance()->readDeviceListFromFile();
        
        const RwRemoteDeviceList::RemoteDevicesListType& devices = RwRemoteDeviceList::getInstance()->getAllDevices();

        IteratorType iter;
        for (iter = devices.begin(); iter != devices.end(); ++iter)
        {
            const QString& deviceName = iter.key();
            const RwRemoteDevice::RwRemoteDevicePtr& remoteDevice = iter.value();
            
            RwRemoteDeviceItem* remoteDeviceItem = new RwRemoteDeviceItem(m_devices, deviceName, remoteDevice);
            m_devices->addItem(remoteDeviceItem);
            connect(m_devices, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(deviceActivated(QListWidgetItem*)));
        }
        
        m_currentDevice = 0;
    }
    
    void RwRemoteDevicesMode::deviceActivated(QListWidgetItem *item)
    {
        if (m_currentDevice != 0)
        {
            const RwRemoteDevice::RwRemoteDevicePtr& remoteDevice = m_currentDevice->getPointerToDevice();
            disconnect(remoteDevice.data(), SIGNAL(notifyOfReply()), this, SLOT(replyReady()));
        }
        
        m_currentDevice = dynamic_cast<RwRemoteDeviceItem*>(item);
        
        const QString& deviceName = m_currentDevice->getDeviceName();
        const RwRemoteDevice::RwRemoteDevicePtr& remoteDevice = m_currentDevice->getPointerToDevice();
        
        rwInfo() << "Activated device " << deviceName << endLine();
        
        connect(remoteDevice.data(), SIGNAL(notifyOfReply()), this, SLOT(replyReady()));
        
        // creating request that will give use the list of all workers
        const QString listWorkerName = RW_LISTWORKER_WORKER_NAME;
        const QStringList arguments;
        const RwWorkerInterface::RwCommand::RwCommandPtr command(new RwWorkerInterface::RwCommand(listWorkerName, arguments));
        RwCommandRequest request(listWorkerName, command);
        
        remoteDevice->connectToDevice();
        if ( !remoteDevice->sendRequest(request) )
        {
            const QString title(tr("Error sending request"));
            const QString errorMessage(tr("An error occurred when sending request to remote device"));
            QMessageBox::critical(this, title, errorMessage);
        }
    }
    
    void RwRemoteDevicesMode::replyReady()
    {
        const RwRemoteDevice::RwRemoteDevicePtr& remoteDevice = m_currentDevice->getPointerToDevice();
        remoteDevice->writeReply();
        
        QDir pathToOutputData(RW_RESPONSE_DATA_FOLDER);
        if ( pathToOutputData.exists("error_code.txt") )
        {
            // TODO: Adapt so it uses the error code
            const QString title(tr("Remote device error"));
            const QString errorMessage(tr("An error occurred when remote device was processing the request"));
            QMessageBox::critical(this, title, errorMessage);
        }
        else if ( pathToOutputData.exists("index.html") )
        {
            QString pathToIndex = pathToOutputData.absoluteFilePath("index.html");
            
            rwDebug() << "Displaying " << pathToIndex << endLine();
            
            m_remoteWorkers->load("file://" + pathToIndex);
        }
    }
    
}
