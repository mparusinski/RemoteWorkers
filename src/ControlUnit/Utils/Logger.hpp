/* 

Logger.hpp: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 16/05/2012 Michal Parusinski <mparusinski@googlemail.com>

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

	void switchLoggingOn();
	void switchLoggingOff();

	void switchErrorReportingOn();
	void switchErrorReportingOff();

	void switchAllOn();
	void switchAllOff();

private:
	Logger(); // singleton pattern

	bool m_logging;
	bool m_reportingErrors;

	LoggerStrategy* m_strategy;
};

}

#endif // _LOGGER_HPP_
