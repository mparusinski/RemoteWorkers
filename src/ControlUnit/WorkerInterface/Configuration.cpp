/* 

Configuration.hpp: Create the configuration for the worker management system

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include "Configuration.hpp"

#include "Utils/Logger.hpp"

namespace WorkerInterface
{

Configuration::Configuration()
{
	m_configurationRead = false;
	m_configurationFile.open("conf.txt");
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
		return instance;
	}
	else
	{
		return instance;
	}
}

void Configuration::readConfiguration()
{
	if ( m_configurationFile.is_open() )
	{
		if (m_configurationRead)
		{
			Utils::Logger::getInstance()->log("Configuration already read, rereading it");
		}

		while( !m_configurationFile.eof() )
		{
			string descriptor;
			string value;
			m_configurationFile >> descriptor;
			m_configurationFile >> value;
			m_configurations[descriptor] = value;
		}
		m_configurationFile.seekg(0, ios::beg);

		m_configurationRead = true;
	}
	else
	{
		Utils::Logger::getInstance()->error("Unable to read configuration! Configuration file did not open");
	}
}

string Configuration::getConfiguration(const string& descriptor) const
{
	if (m_configurationRead)
	{
		ConfigurationsType::const_iterator iter = m_configurations.find(descriptor);
		if (iter != m_configurations.end())
		{
			return iter->second;
		}
		else
		{
			string errorMessage = "There is no configuration for descriptor ";
			errorMessage += descriptor;
			Utils::Logger::getInstance()->error(errorMessage);

			return string();
		}
	}
	else
	{
		Utils::Logger::getInstance()->error("Configuration has not been read");
		return string();
	}
}

string Configuration::getWorkersPath() const
{
	return getConfiguration("WorkersPath");
}

}
