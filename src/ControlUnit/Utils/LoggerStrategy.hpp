/* 

LoggerStrategy.hpp: Set of function that handles the logging (ABSTRACT)

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _LOGGERSTRATEGY_HPP_
#define _LOGGERSTRATEGY_HPP_

#include <string>

using namespace std;

namespace Utils
{

class LoggerStrategy
{
public:

	LoggerStrategy();
	virtual ~LoggerStrategy();

	virtual void WriteToLog(const string& message) const;
	virtual void WriteToError(const string& message) const;

private:
	inline void usingBaseClassError() const;

};

}

#endif // _LOGGERSTRATEGY_HPP_
