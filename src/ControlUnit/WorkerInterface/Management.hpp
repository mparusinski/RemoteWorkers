/* 

Management.hpp: Manages workers

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#ifndef _MANAGEMENT_HPP_
#define _MANAGEMENT_HPP_

#include <string>

#include "Worker.hpp"
#include "Reply.hpp"

using namespace std;

namespace WorkerInterface
{

class Management
{
public:
	virtual ~Management();
	static Management* getInstance();

	Worker createWorker(const string& workerName) const;

private:
	Management();

	string m_pathToWorkers;
};

}

#endif // _MANAGEMENT_HPP_
