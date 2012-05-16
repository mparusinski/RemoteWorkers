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

#include "Logger.hpp"

#include <boost/lexical_cast.hpp>

#include "LoggerConsoleStrategy.hpp"
#include "LoggerFileStrategy.hpp"

namespace Utils
{

Logger::Logger()
{
	m_logging = false;
	m_reportingErrors = false;
	m_strategy = new LoggerConsoleStrategy();
}

Logger::~Logger()
{
	delete m_strategy;
}

Logger* Logger::getInstance()
{
	static Logger* instance = 0;
	if (instance == 0)
	{
		instance = new Logger();
		return instance;
	}
	else
	{
		return instance;
	}
}

void Logger::useConsoleLogger()
{
	delete m_strategy;
	m_strategy = new LoggerConsoleStrategy();
}

void Logger::useFileLogger()
{
	delete m_strategy;
	m_strategy = new LoggerFileStrategy();
}

void Logger::switchLoggingOff()
{
	m_logging = false;
}

void Logger::switchLoggingOn()
{
	m_logging = true;
}

void Logger::switchErrorReportingOff()
{
	m_reportingErrors = false;
}

void Logger::switchErrorReportingOn()
{
	m_reportingErrors = true;
}

void Logger::switchAllOff()
{
	m_logging = false;
	m_reportingErrors = false;
}

void Logger::switchAllOn()
{
	m_logging = true;
	m_reportingErrors = true;
}

void Logger::log(const char* message) const
{
	if (m_logging)
	{
		string strMessage(message);
		strMessage += "\n";
		m_strategy->WriteToLog(strMessage);
	}
}

void Logger::log(const string& message) const
{
	if (m_logging)
	{
		string actualMessage = message;
		actualMessage += "\n";
		m_strategy->WriteToLog(actualMessage);
	}
}

void Logger::reportError(
		const char* file,
		const char* function,
		const int lineNumber,
		const char* message) const
{
	if (m_reportingErrors)
	{
		string actualMessage;
		actualMessage += "ERROR (file:";
		actualMessage += file;
		actualMessage += ", function: ";
		actualMessage += function;
		actualMessage += ", lineNumber: ";
		actualMessage += boost::lexical_cast<string>(lineNumber);
		actualMessage += "): ";
		actualMessage += message;
		actualMessage += "\n";
		m_strategy->WriteToError(actualMessage);
	}
}

void Logger::reportError(
		const char* file,
		const char* function,
		const int lineNumber,
		const string& message) const
{
	if (m_reportingErrors)
	{
		string actualMessage;
		actualMessage += "ERROR (file:";
		actualMessage += file;
		actualMessage += ", function: ";
		actualMessage += function;
		actualMessage += ", lineNumber: ";
		actualMessage += boost::lexical_cast<string>(lineNumber);
		actualMessage += "): ";
		actualMessage += message;
		actualMessage += "\n";
		m_strategy->WriteToError(actualMessage);
	}
}

}
