/* 

Logger.hpp: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>

#include "LoggerStrategy.hpp"

using namespace std;

namespace Utils
{

class Logger
{
public:
	virtual ~Logger();

	static Logger* getInstance();

	void useConsoleLogger();
	void useFileLogger();

	void log(const char* message) const;
	void log(const string& message) const;

#define error(message) reportError(__FILE__, (__func__), __LINE__, message)

#ifndef NDEBUG
#define debug(message) _debugMessage(__FILE__, message);
#else
#define debug(message)
#endif // NDEBUG

	void reportError(
			const char* file,
			const char* function,
			const int lineNumber,
			const char* message) const;
	void reportError(
			const char* file,
			const char* function,
			const int lineNumber,
			const string& message) const;

	void turnLoggingOn();
	void turnLoggingOff();

	void turnErrorReportingOn();
	void turnErrorReportingOff();

	void turnAllOn();
	void turnAllOff();

	void _debugMessage(const char* file, const char* message) const;
	void _debugMessage(const char* file, const string& message) const;

private:
	Logger(); // singleton pattern

	bool m_logging;
	bool m_reportingErrors;

	LoggerStrategy* m_strategy;
};

}

#endif // _LOGGER_HPP_
