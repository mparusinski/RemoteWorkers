/* 

Management.hpp: Manages workers

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#ifndef _MANAGEMENT_HPP_
#define _MANAGEMENT_HPP_

#include <QString>
#include <QFileInfo>

#include "Utils/Return/Return.h"

#include "Worker.h"
#include "Reply.h"

using namespace Utils::Return;

namespace WorkerInterface
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is a singleton class which purpose is to manage workers.
///        It provides a interface to the workers by creating them on demand,
///        listing them and other.
////////////////////////////////////////////////////////////////////////////////
class Management
{
public:
	virtual ~Management();
	static Management* getInstance();

	/////////////////////////////////////////////////////////////////////////////////
	/// \brief      Create the worker with given name. The function resolves the path
	///             to the worker
	/// \param[in]  workerName	Name of the worker
	/// \param[out] worker      The worker we wish to create
	/// \return     returns true if successfully created worker
	/////////////////////////////////////////////////////////////////////////////////
	ReturnType createWorker(const QString& workerName, Worker& worker);

	/////////////////////////////////////////////////////////////////////////////////
	/// \brief     List all available workers in default path
	/// \return    List of worker names (not a list of workers)
	/////////////////////////////////////////////////////////////////////////////////
	const QFileInfoList& listAvailableWorkers();

private:
	Management();

	inline void getListOfWorkers();

	QFileInfo m_pathToWorkers;
	QFileInfoList m_availableWorkers;
};

}

#endif // _MANAGEMENT_HPP_
