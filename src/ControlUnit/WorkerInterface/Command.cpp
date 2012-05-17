/* 

Command.cpp: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include <iostream>

#include "Command.hpp"
#include "Utils/CrossPlatform.hpp"
#include "Utils/Logger.hpp"

using namespace std;

namespace WorkerInterface
{

Command::Command(const Worker& worker, const string& commandName, const vector<string>& arguments)
{
	m_worker = worker;
	m_order = commandName;
	m_arguments = arguments;
}

void Command::execute() const
{
	if ( Utils::CrossPlatform::executeCommand(m_worker.getPath(), m_order, m_arguments) == 0 )
	{
		string errorMessage = toString();
		errorMessage += " did not execute properly";
		Utils::Logger::getInstance()->error(errorMessage);
	}
	else
	{
		string successMessage = toString();
		successMessage += " did execute properly";
		Utils::Logger::getInstance()->log(successMessage);
	}
}

string Command::toString() const
{
	string commandName;
	commandName += "Command ";
	commandName += m_worker.getPath();
	commandName += " ";
	commandName += m_order;

	return commandName;
}

}
