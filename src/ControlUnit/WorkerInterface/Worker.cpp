/* 

Worker.cpp: Interface to a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include <string>
#include <iostream>

#include "Worker.hpp"

using namespace std;

namespace WorkerInterface
{

Worker::Worker()
{
}

Worker::Worker(string name)
{
	m_name = name;
}

string Worker::getName() const
{
	return m_name;
}

}
