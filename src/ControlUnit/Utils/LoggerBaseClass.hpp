/* 

LoggerStrategy.hpp: Set of function that handles the logging (ABSTRACT)

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _LOGGERBASECLASS_HPP_
#define _LOGGERBASECLASS_HPP_

#include <string>

using namespace std;

namespace Utils
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is a abstract base class to logging systems. It is used by
///        the logger class to allow the logger to choose the logging mechanism.
////////////////////////////////////////////////////////////////////////////////
class LoggerBaseClass
{
public:

	LoggerBaseClass();
	virtual ~LoggerBaseClass();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Abstract method for writing a message to a log
	/// \param[in] message	message to be logged
	////////////////////////////////////////////////////////////////////////////////
	virtual void WriteToLog(const string& message) const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Abstract method for writing a report an error
	/// \param[in] message	error message to reported
	////////////////////////////////////////////////////////////////////////////////
	virtual void WriteToError(const string& message) const;

private:
	virtual void noInstantiation() = 0;
	inline void usingBaseClassError() const;

};

}

#endif // _LOGGERBASECLASS_HPP_