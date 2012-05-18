/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "ConsoleLogger.hpp"

#include <iostream>

using namespace std;

namespace Utils
{

ConsoleLogger::ConsoleLogger()
{

}

ConsoleLogger::~ConsoleLogger()
{

}

void ConsoleLogger::WriteToLog(const string& message) const
{
	cout << message << endl;
}

void ConsoleLogger::WriteToError(const string& message) const
{
	cerr << message << endl;
}

}
