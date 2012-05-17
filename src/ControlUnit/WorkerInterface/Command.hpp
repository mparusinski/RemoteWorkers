/* 

Command.hpp: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <string>
#include <vector>

#include "Worker.hpp"

using namespace std;

namespace WorkerInterface
{

class Command
{

public:
	Command(const Worker& worker, const string& commandName, const vector<string>& arguments);
	virtual ~Command() { }

	void execute() const;
	string toString() const;

private:
	Command();

	Worker m_worker;
	string m_order;
	vector<string> m_arguments;
};

}

#endif // _COMMAND_HPP_
