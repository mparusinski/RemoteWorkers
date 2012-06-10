/* 

LoggerStrategy.hpp: Set of function that handles the logging (ABSTRACT)

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include <cstdio>
#include "LoggerBaseClass.hpp"

namespace Utils
{

LoggerBaseClass::LoggerBaseClass()
{

}

LoggerBaseClass::~LoggerBaseClass()
{

}

void LoggerBaseClass::WriteToLog(const QString & message) const
{
	usingBaseClassError();
}

void LoggerBaseClass::WriteToError(const QString & message) const
{
	usingBaseClassError();
}

inline void LoggerBaseClass::usingBaseClassError() const
{
	fprintf(stderr, "DEVELOPMENT-ERROR: Using base class in strategy pattern (Logger system)!\n");
	fprintf(stderr, "Please use the specialised classes for the LoggerStrategy\n");
	exit(-1);
}

}
