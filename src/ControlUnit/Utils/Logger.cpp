/* 

Logger.hpp: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

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

void Logger::_debugMessage(const char* message) const
{
	cerr << "DEBUG: " << message << endl;
}

void Logger::_debugMessage(const string& message) const
{
	cerr << "DEBUG: " << message << endl;
}

}
