/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _LOGGERCONSOLESTRATEGY_HPP_
#define _LOGGERCONSOLESTRATEGY_HPP_

#include <iostream>
#include <string>

#include "LoggerStrategy.hpp"

using namespace std;

namespace Utils
{

class LoggerConsoleStrategy : public LoggerStrategy
{
public:

	LoggerConsoleStrategy();
	virtual ~LoggerConsoleStrategy();

	virtual void WriteToLog(const string& message) const;
	virtual void WriteToError(const string& message) const;

private:

};

}

#endif // _LOGGERCONSOLESTRATEGY_HPP_
