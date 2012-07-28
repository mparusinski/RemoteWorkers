/* 

RwConfiguration.cc: Create the configuration for the worker management system

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include "RwConfiguration.h"

#include <QFile>
#include <QTextStream>

#include "../RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwUtils
{

namespace RwGlobal
{
    
    RwConfiguration::RwConfiguration()
    {
        m_configurationRead = false;
        //readConfiguration(); // should not be called as it can fail
    }
    
    RwConfiguration::~RwConfiguration()
    {
    }
    
    RwConfiguration* RwConfiguration::getInstance()
    {
        static RwConfiguration* instance = 0;
        if (instance == 0)
        {
            instance = new RwConfiguration();
        }
        return instance;
    }
    
    RwReturnType RwConfiguration::readConfiguration()
    {
        RwReturnType returnMsg = RW_NO_ERROR;
        QFile configurationFile("conf.txt");
        
        if ( configurationFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            if (m_configurationRead)
            {
                rwWarning() << "Configuration already read, rereading" << endLine();
            }
            
            QTextStream configurationFileIn(&configurationFile);
            
            while( !configurationFileIn.atEnd() )
            {
                QString descriptor;
                QString value;
                
                configurationFileIn >> descriptor;
                configurationFileIn >> value;
                
                m_configurations[descriptor] = value;
            }
            
            m_configurationRead = true;
        }
        else
        {
            rwError() << "Unable to read configuration! Configuration file did not open" 
                      << endLine();
            returnMsg = returnMsg | RW_ERROR_FILE_NOT_READ;
        }
        
        configurationFile.close();
        
        return returnMsg;
    }
    
    RwReturnType RwConfiguration::getConfiguration(const QString& descriptor, QString& configuration)
    {
        RwReturnType returnMsg = RW_NO_ERROR;
        if (!m_configurationRead)
        {
            returnMsg = readConfiguration();
        }
        
        if (returnMsg != RW_NO_ERROR)
        {
            rwError() << "Some error happened when reading configuration file" << endLine();
            return returnMsg;
        }
        
        if (m_configurationRead)
        {
            ConfigurationsType::const_iterator iter = m_configurations.find(descriptor);
            if (iter != m_configurations.end())
            {
                configuration = iter.value();
            }
            else
            {
                rwError() << "There is no configuration for descriptor " << descriptor << endLine();
            }
        }
        
        return returnMsg;
    }
    
    RwReturnType RwConfiguration::getWorkersPath(QString& workersPath)
    {
        return getConfiguration("WorkersPath", workersPath);
    }
    
    RwReturnType RwConfiguration::getWorkersListPath(QString& workersListPath)
    {
    	return getConfiguration("WorkersList", workersListPath);
    }

    RwReturnType RwConfiguration::getDeviceListPath(QString& deviceListPath)
    {
    	return getConfiguration("DeviceList", deviceListPath);
    }

}

}
