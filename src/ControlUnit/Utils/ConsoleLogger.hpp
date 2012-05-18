/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _CONSOLELOGGER_HPP_
#define _CONSOLELOGGER_HPP_

#include <iostream>
#include <string>

#include "LoggerBaseClass.hpp"

using namespace std;

namespace Utils
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class implements the a logger mechanism that writes to console.
///        Should not be instantiated, use instead the Logger class.
////////////////////////////////////////////////////////////////////////////////
class ConsoleLogger : public LoggerBaseClass
{
public:

	ConsoleLogger();
	virtual ~ConsoleLogger();

	virtual void WriteToLog(const string& message) const;
	virtual void WriteToError(const string& message) const;

private:

};

}

#endif // _CONSOLELOGGER_HPP_
