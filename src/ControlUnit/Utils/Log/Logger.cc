/* 

Logger.hpp: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "Logger.h"

#include "ConsoleLogger.h"
#include "FileLogger.h"

#include <QString>

namespace Utils
{
namespace Log
{

Logger::Logger()
{
	m_logging = false;
	m_reportingErrors = false;
	m_strategy = new ConsoleLogger();
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
	}
	return instance;
}

void Logger::useConsoleLogger()
{
	delete m_strategy;
	m_strategy = new ConsoleLogger();
}

void Logger::useFileLogger()
{
	delete m_strategy;
	m_strategy = new FileLogger();
}

void Logger::turnLoggingOff()
{
	m_logging = false;
}

void Logger::turnLoggingOn()
{
	m_logging = true;
}

void Logger::turnErrorReportingOff()
{
	m_reportingErrors = false;
}

void Logger::turnErrorReportingOn()
{
	m_reportingErrors = true;
}

void Logger::turnAllOff()
{
	m_logging = false;
	m_reportingErrors = false;
}

void Logger::turnAllOn()
{
	m_logging = true;
	m_reportingErrors = true;
}

bool Logger::logging()
{
	return m_logging;
}

bool Logger::reportErrors()
{
	return m_reportingErrors;
}

void Logger::log(const char* message) const
{
	if (m_logging)
	{
		QString strMessage(message);
		strMessage += "\n";
		m_strategy->WriteToLog(strMessage);
	}
}

void Logger::log(const QString& message) const
{
	if (m_logging)
	{
		QString actualMessage = message;
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
		QString actualMessage;
		actualMessage += "ERROR (file:";
		actualMessage += file;
		actualMessage += ", function: ";
		actualMessage += function;
		actualMessage += ", lineNumber: ";
		actualMessage += QString::number(lineNumber);
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
		const QString& message) const
{
	if (m_reportingErrors)
	{
		QString actualMessage;
		actualMessage += "ERROR (file:";
		actualMessage += file;
		actualMessage += ", function: ";
		actualMessage += function;
		actualMessage += ", lineNumber: ";
		actualMessage += QString::number(lineNumber);
		actualMessage += "): ";
		actualMessage += message;
		actualMessage += "\n";
		m_strategy->WriteToError(actualMessage);
	}
}

void Logger::_debugMessage(const char* file, const char* message) const
{
	fprintf(stderr, "DEBUG (%s): %s\n", file, message);
}

void Logger::_debugMessage(const char* file, const QString& message) const
{
    QTextStream errout(stderr);
    QString debugMessage = "DEBUG (";
    debugMessage += file;
    debugMessage += "): ";
    debugMessage += message;
    debugMessage += "\n";
    errout << debugMessage;
}

}
}
