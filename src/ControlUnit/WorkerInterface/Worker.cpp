/* 

Worker.cpp: Interface to a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "Worker.hpp"

#include <string>
#include <iostream>

#include "Reply.hpp"

using namespace std;

namespace WorkerInterface
{

Worker::Worker()
{
}

Worker::Worker(string path)
{
	m_path = path;
}

string Worker::getPath() const
{
	return m_path;
}

Reply Worker::getReply() const
{
	Reply reply(*this);
	reply.cleanWorkerOutput();
	return reply;
}

}
