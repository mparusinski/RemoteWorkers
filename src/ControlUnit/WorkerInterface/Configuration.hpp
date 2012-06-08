/* 

Configuration.hpp: Create the configuration for the worker management system

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <QString>
#include <fstream>
#include <map>

using namespace std;

namespace WorkerInterface
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is a singleton class which purpose is to retrieve
///        configuration data from the configuration file
////////////////////////////////////////////////////////////////////////////////
class Configuration
{
public:
	typedef map<QString, QString> ConfigurationsType;

	~Configuration();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Returns an instance of the object (see Singleton pattern).
	///            Most important function as it is the only way to access the object
	/// \return    The only possible instance of the object
	////////////////////////////////////////////////////////////////////////////////
	static Configuration* getInstance();

	/////////////////////////////////////////////////////////////////////////////////
	/// \brief      Returns the path to the directory containing the workers
    /// \param[out] workerPath path to the workers
	/// \return     A string representing a file path
	/////////////////////////////////////////////////////////////////////////////////
	void getWorkersPath(QString& workerPath) const;

	/////////////////////////////////////////////////////////////////////////////////
	/// \brief      Returns the value of corresponding to the descriptor
    /// \param[in]  descriptor    Name of the configuration
    /// \param[out] configuration Value of the configuration
	/// \return     Configuration value for given descriptor
	/////////////////////////////////////////////////////////////////////////////////
	void getConfiguration(const QString& descriptor, QString& configuration) const;

	/////////////////////////////////////////////////////////////////////////////////
	/// \brief     Reads the configuration file. This is already done at construction.
	/////////////////////////////////////////////////////////////////////////////////
	void readConfiguration();

private:
	Configuration();

	ifstream m_configurationFile;
	bool m_configurationRead;
	ConfigurationsType m_configurations;
};

}

#endif // _CONFIGURATION_HPP_
