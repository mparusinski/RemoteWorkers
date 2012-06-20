/* 

Configuration.hpp: Create the configuration for the worker management system

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include "Configuration.h"

#include <QDir>
#include <QFile>
#include <QTextStream>

#include "Utils/Log/Logger.h"

namespace WorkerInterface
{

Configuration::Configuration()
{
	m_configurationRead = false;
	//readConfiguration(); // should not be called as it can fail
}

Configuration::~Configuration()
{
}

Configuration* Configuration::getInstance()
{
	static Configuration* instance = 0;
	if (instance == 0)
	{
		instance = new Configuration();
	}
	return instance;
}

ReturnType Configuration::readConfiguration()
{
    ReturnType returnMsg = RW_NO_ERROR;
    QFile configurationFile("conf.txt");
    configurationFile.open(QFile::ReadOnly | QFile::Text);
    
	if ( configurationFile.isOpen() )
	{
        QTextStream configurationIn(&configurationFile);
        
		if (m_configurationRead)
		{
			Utils::Log::Logger::getInstance()->log("Configuration already read, rereading it");
		}

		while( !configurationIn.atEnd() )
		{
			QString descriptor;
			QString value;

			configurationIn >> descriptor;
			configurationIn >> value;

			m_configurations[descriptor] = value;
		}

		m_configurationRead = true;
	}
	else
	{
		Utils::Log::Logger::getInstance()->error_msg("Unable to read configuration! Configuration file did not open");
        returnMsg = returnMsg | RW_ERROR_FILE_NOT_READ;
	}
    
    configurationFile.close();
    
    return returnMsg;
}

ReturnType Configuration::getConfiguration(const QString& descriptor, QString& configuration)
{
    ReturnType returnMsg = RW_NO_ERROR;
    if (!m_configurationRead)
    {
        returnMsg = readConfiguration();
    }
    
	if (returnMsg != RW_NO_ERROR)
    {
        Utils::Log::Logger::getInstance()->error_msg("Error occurred when reading configuration file!");
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
			QString errorMessage = "There is no configuration for descriptor ";
			errorMessage += descriptor;
			Utils::Log::Logger::getInstance()->error_msg(errorMessage);
		}
	}
    
    return returnMsg;
}

void Configuration::getWorkersPath(QString& workersPath)
{
    getConfiguration("WorkersPath", workersPath);
}

}
