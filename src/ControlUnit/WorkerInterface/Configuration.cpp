/* 

Configuration.hpp: Create the configuration for the worker management system

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include "Configuration.hpp"

#include <QDir>

#include "Utils/Logger.hpp"

namespace WorkerInterface
{

Configuration::Configuration()
{
	m_configurationRead = false;
	readConfiguration();
}

Configuration::~Configuration()
{
	m_configurationFile.close();
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

void Configuration::readConfiguration()
{
	m_configurationFile.open("conf.txt");
	if ( m_configurationFile.is_open() )
	{
		if (m_configurationRead)
		{
			Utils::Logger::getInstance()->log("Configuration already read, rereading it");
		}

		while( !m_configurationFile.eof() )
		{
			QString descriptor;
			QString value;
			string descriptor_str;
			string value_str;

			m_configurationFile >> descriptor_str;
			m_configurationFile >> value_str;
			descriptor = descriptor_str.c_str();
			value = value_str.c_str();

			m_configurations[descriptor] = value;
		}
		m_configurationFile.close();

		m_configurationRead = true;
	}
	else
	{
		Utils::Logger::getInstance()->error_msg("Unable to read configuration! Configuration file did not open");
	}
}

void Configuration::getConfiguration(const QString& descriptor, QString& configuration) const
{
	if (m_configurationRead)
	{
		ConfigurationsType::const_iterator iter = m_configurations.find(descriptor);
		if (iter != m_configurations.end())
		{
			configuration = iter->second;
		}
		else
		{
			QString errorMessage = "There is no configuration for descriptor ";
			errorMessage += descriptor;
			Utils::Logger::getInstance()->error_msg(errorMessage);
		}
	}
	else
	{
		Utils::Logger::getInstance()->error_msg("Configuration has not been read");
	}
}

void Configuration::getWorkersPath(QString& workersPath) const
{
    getConfiguration("WorkersPath", workersPath);
}

}
