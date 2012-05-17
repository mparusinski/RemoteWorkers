/* 

LoggerFileStrategy.hpp: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _LOGGERFILESTRATEGY_HPP_
#define _LOGGERFILESTRATEGY_HPP_

#include "LoggerStrategy.hpp"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace Utils
{

class LoggerFileStrategy : public LoggerStrategy
{
public:

	LoggerFileStrategy();
	virtual ~LoggerFileStrategy();

	virtual void WriteToLog(const string& message) const;
	virtual void WriteToError(const string& message) const;

private:
	mutable ofstream m_logFile;
	mutable ofstream m_errorFile;
};

}

#endif // _LOGGERFILESTRATEGY_HPP_
