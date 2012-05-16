/* 

Command.cpp: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 15/04/2012 Michal Parusinski <mparusinski@googlemail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 

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
	m_commandName = commandName;
	m_arguments = arguments;
}

void Command::execute() const
{
	if ( Utils::CrossPlatform::executeCommand(m_worker.getName(), m_commandName, m_arguments) == 0 )
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
	commandName += m_worker.getName();
	commandName += " ";
	commandName += m_commandName;

	return commandName;
}

}
