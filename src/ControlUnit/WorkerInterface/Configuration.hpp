/* 

Configuration.hpp: Create the configuration for the worker management system

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <string>
#include <fstream>
#include <map>

using namespace std;

namespace WorkerInterface
{

class Configuration
{
public:

	typedef map<string, string> ConfigurationsType;

	~Configuration();
	Configuration* getInstance();

	string getWorkersPath() const;
	string getConfiguration(const string& descriptor) const;

	void readConfiguration();

private:
	Configuration();

	ifstream m_configurationFile;
	bool m_configurationRead;
	ConfigurationsType m_configurations;
};

}

#endif // _CONFIGURATION_HPP_
