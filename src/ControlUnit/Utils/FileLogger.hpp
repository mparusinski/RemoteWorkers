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

#include <QString>
#include <QFile>
#include <QTextStream>

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

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Method for writing a message to a log which is stored in a file
	/// \param[in] message	message to be logged
	////////////////////////////////////////////////////////////////////////////////
	virtual void WriteToLog(const QString& message) const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Method for reporting an error to an error file
	/// \param[in] message	error message to reported
	////////////////////////////////////////////////////////////////////////////////
	virtual void WriteToError(const QString& message) const;

private:
	virtual void noInstantiation() {}

	QFile* m_logFile;
	QFile* m_errorFile;
    QTextStream* m_logOut;
    QTextStream* m_errorOut;
};

}

#endif // _FILELOGGER_HPP_
