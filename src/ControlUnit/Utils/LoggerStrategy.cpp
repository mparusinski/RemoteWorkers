/* 

LoggerStrategy.hpp: Set of function that handles the logging (ABSTRACT)

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "LoggerStrategy.hpp"

#include <iostream>

namespace Utils
{

LoggerStrategy::LoggerStrategy()
{

}

LoggerStrategy::~LoggerStrategy()
{

}

void LoggerStrategy::WriteToLog(const string & message) const
{
	usingBaseClassError();
}

void LoggerStrategy::WriteToError(const string & message) const
{
	usingBaseClassError();
}

inline void LoggerStrategy::usingBaseClassError() const
{
	cerr << "DEVELOPMENT-ERROR: Using base class in strategy pattern (Logger system)!" << endl;
	cerr << "Please use the specialised classes for the LoggerStrategy";
	exit(-1);
}

}
