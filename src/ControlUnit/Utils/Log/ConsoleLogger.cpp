/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "ConsoleLogger.hpp"

#include <cstdio>
#include <cstdlib>

namespace Utils
{
namespace Log
{

ConsoleLogger::ConsoleLogger()
{
    m_stdout = new QTextStream(stdout);
    m_stderr = new QTextStream(stderr); 
}

ConsoleLogger::~ConsoleLogger()
{
    delete m_stdout;
    delete m_stderr;
}

void ConsoleLogger::WriteToLog(const QString& message) const
{
	*m_stdout << message << endl;
}

void ConsoleLogger::WriteToError(const QString& message) const
{
	*m_stderr << message << endl;
}

}
}
