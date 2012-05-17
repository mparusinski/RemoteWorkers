/* 

Worker.hpp: Interface to a worker program

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _WORKER_HPP_
#define _WORKER_HPP_

#include <string>
#include <vector>

//#include "Reply.hpp"
#include "Command.hpp"

using namespace std;

namespace WorkerInterface
{

class Reply;

class Worker {

public:
	Worker();
	Worker(string path);
	virtual ~Worker() { }

	Reply getReply() const;
	void executeCommand(const Command& command) const;
	string getPath() const;

private:
	string commandToString(const Command& command) const;

	string m_path;
};

}

#endif // _WORKER_HPP_
