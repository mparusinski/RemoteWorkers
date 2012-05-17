/* 

LoggerFileStrategy.hpp: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "LoggerFileStrategy.hpp"

namespace Utils
{

LoggerFileStrategy::LoggerFileStrategy()
{
	m_logFile.open("log.txt", ofstream::out);
	m_errorFile.open("error.txt", ofstream::out);
}

LoggerFileStrategy::~LoggerFileStrategy()
{
	m_logFile.close();
	m_errorFile.close();
}

void LoggerFileStrategy::WriteToLog(const string& message) const
{
	m_logFile << message;
}

void LoggerFileStrategy::WriteToError(const string& message) const
{
	m_errorFile << message;
}

}
