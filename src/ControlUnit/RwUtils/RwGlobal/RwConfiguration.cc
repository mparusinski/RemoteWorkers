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
        QFile configurationFile("conf.txt");
        
        if ( configurationFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {            
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
            configurationFile.close();
            return RW_NO_ERROR;
        }
        else
        {
            rwError() << "Unable to read configuration! Configuration file did not open" << endLine();
            return RW_ERROR_FILE_NOT_READ;
        }
    }
    
    RwReturnType RwConfiguration::getConfiguration(const QString& descriptor, QString& configuration)
    {
        if (!m_configurationRead )
        {
            RwReturnType returnMsg = readConfiguration();
            if ( returnMsg != RW_NO_ERROR )
            {
                return returnMsg;
            }
        }
        
        ConfigurationsType::const_iterator iter = m_configurations.find(descriptor);
        if (iter != m_configurations.end())
        {
            configuration = iter.value();
        }
        else
        {
            rwError() << "There is no configuration for descriptor " << descriptor << endLine();
            return RW_ERROR_GENERIC;
        }
        
        return RW_NO_ERROR;
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
