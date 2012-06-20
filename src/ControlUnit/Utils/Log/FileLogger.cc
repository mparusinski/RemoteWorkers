/* 

LoggerFileStrategy.hpp: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "FileLogger.h"

namespace Utils
{
namespace Log
{

FileLogger::FileLogger()
{
	m_logFile   = new QFile("log.txt");
	m_errorFile = new QFile("error.txt");
    
    m_logFile->open(QIODevice::WriteOnly | QIODevice::Text);
    m_errorFile->open(QIODevice::WriteOnly | QIODevice::Text);
    
    m_logOut    = new QTextStream(m_logFile);
    m_errorOut  = new QTextStream(m_errorFile);
}

FileLogger::~FileLogger()
{
    m_logFile->close();
	m_errorFile->close();
    
    delete m_logOut;
    delete m_errorOut;
    
    delete m_logFile;
    delete m_errorFile;
}

void FileLogger::WriteToLog(const QString& message) const
{
	*m_logOut << message;
}

void FileLogger::WriteToError(const QString& message) const
{
	*m_errorOut << message;
}

}
}
