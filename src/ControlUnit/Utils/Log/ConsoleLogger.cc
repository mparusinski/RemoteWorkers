/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "ConsoleLogger.h"

#include <cstdio>
#include <cstdlib>

namespace Utils
{
    namespace Log
    {
        
        ConsoleLogger::ConsoleLogger()
        {
        }
        
        ConsoleLogger::~ConsoleLogger()
        {
        }
        
        void ConsoleLogger::WriteToLog(const QString& message) const
        {
            fprintf(stdout, "%s\n", message.toAscii().data());
        }
        
        void ConsoleLogger::WriteToError(const QString& message) const
        {
            fprintf(stderr, "%s\n", message.toAscii().data());
        }
        
    }
}
