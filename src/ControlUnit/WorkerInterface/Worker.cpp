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
#include "Utils/CrossPlatform.hpp"
#include "Utils/Logger.hpp"

using namespace std;

namespace WorkerInterface
{

Worker::Worker()
{
	m_path = string();
}

Worker::Worker(string path)
{
	m_path = path;
}

Reply Worker::getReply() const
{
	Reply reply(*this);
	reply.cleanWorkerOutput();
	return reply;
}

string Worker::getPath() const
{
	return m_path;
}

void Worker::executeCommand(const Command& command) const
{
	const string& order = command.getOrder();
	const vector<string>& arguments = command.getArguments();

	if ( Utils::CrossPlatform::executeCommand(m_path, order, arguments) == 0 )
	{
		string errorMessage = commandToString(command);
		errorMessage += " did not execute properly";
		Utils::Logger::getInstance()->error(errorMessage);
	}
	else
	{
		string successMessage = commandToString(command);
		successMessage += " did execute properly";
		Utils::Logger::getInstance()->log(successMessage);
	}
}

string Worker::commandToString(const Command& command) const
{
	string commandName;

	commandName += "Command ";
	commandName += m_path;
	commandName += Utils::CrossPlatform::getPathSeparator();
	commandName += command.getOrder();

	return commandName;
}

}
