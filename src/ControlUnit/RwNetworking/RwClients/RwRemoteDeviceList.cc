/* 

RwRemoteDeviceList.cc: Handles the list of available clients

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#include "RwRemoteDeviceList.h"

#include <QFile>
#include <QTextStream>

#include "RwUtils/RwGlobal/RwConfiguration.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwGlobal;
using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwClients {
        
        RwRemoteDeviceList::RwRemoteDeviceList()
        {
            
        }
        
        RwRemoteDeviceList::~RwRemoteDeviceList()
        {
            
        }
        
        RwRemoteDeviceList* RwRemoteDeviceList::getInstance()
        {
            static RwRemoteDeviceList* instance = 0;
            if (instance == 0)
            {
                instance = new RwRemoteDeviceList;
            }
            return instance;
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
        
        RwReturnType RwRemoteDeviceList::readDeviceListFromFile()
        {
            QString deviceListPath;
            RwConfiguration::getInstance()->getDeviceListPath(deviceListPath);
            
            QFile deviceListFile(deviceListPath);
            
            if ( !deviceListFile.open(QIODevice::ReadOnly | QIODevice::Text) )
            {
                rwError() << "Unable to open device list file" << endLine();
                return RW_ERROR_FILE_NOT_READ;
            }
            
            QTextStream in(&deviceListFile);
            
            while ( !in.atEnd())
            {
                QString deviceName;
                quint16 typeNum;
                QString address;
                
                in >> deviceName;
                
                if (deviceName[0] == '#')
                {
                    in.readLine();
                    continue;
                } else if ( deviceName.isEmpty() ) {
                    break;
                }
                
                in >> typeNum;
                in >> address;
                
                RwRemoteDevice::RwRemoteDevicePtr remoteDevice(new RwRemoteDevice(0, address, typeNum));
                m_allDevices[deviceName] = remoteDevice;
            }
            
            deviceListFile.close();
            return RW_NO_ERROR;
        }
        
        RwReturnType RwRemoteDeviceList::saveDeviceListToFile()
        {
            QString deviceListPath;
            RwConfiguration::getInstance()->getDeviceListPath(deviceListPath);
            
            QFile deviceListFile(deviceListPath);
            
            if ( !deviceListFile.open(QIODevice::WriteOnly | QIODevice::Text) )
            {
                rwError() << "Unable to open device list file" << endLine();
                return RW_ERROR_FILE_NOT_READ;
            }
            
            QTextStream out(&deviceListFile);
            
            out << "# Name Type (1 -> local, 2 -> TCP, 3 -> SSL) Address" << endLine();
            
            RemoteDevicesListType::const_iterator iter;
            for (iter = m_allDevices.begin(); iter != m_allDevices.end(); ++iter)
            {
                RwRemoteDevice::RwRemoteDevicePtr remoteDevice = iter.value();
                out << iter.key() << ' ' << remoteDevice->getType() << ' ' << remoteDevice->getAddress() << endLine();
            }
            
            deviceListFile.close();
            return RW_NO_ERROR;
        }
        
    }
    
}
