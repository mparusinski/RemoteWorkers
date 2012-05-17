/* 

Command.cpp: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include <iostream>

#include "Command.hpp"

using namespace std;

namespace WorkerInterface
{

Command::Command(const string& commandName, const vector<string>& arguments)
{
	m_order = commandName;
	m_arguments = arguments;
}

string Command::getOrder() const
{
	return m_order;
}

vector<string> Command::getArguments() const
{
	return m_arguments;
}

}
