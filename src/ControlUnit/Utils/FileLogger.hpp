/* 

LoggerFileStrategy.hpp: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _FILELOGGER_HPP_
#define _FILELOGGER_HPP_

#include "LoggerBaseClass.hpp"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace Utils
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class implements the a logger mechanism that writes to files.
///        Should not be instantiated, use instead the Logger class.
////////////////////////////////////////////////////////////////////////////////
class FileLogger : public LoggerBaseClass
{
public:

	FileLogger();
	virtual ~FileLogger();

	virtual void WriteToLog(const string& message) const;
	virtual void WriteToError(const string& message) const;

private:
	mutable ofstream m_logFile;
	mutable ofstream m_errorFile;
};

}

#endif // _FILELOGGER_HPP_
