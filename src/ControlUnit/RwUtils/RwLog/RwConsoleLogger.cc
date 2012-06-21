/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwConsoleLogger.h"

#include <cstdio>
#include <cstdlib>

namespace RwUtils
{
    namespace RwLog
    {
        
        RwConsoleLogger::RwConsoleLogger()
        {
        }
        
        RwConsoleLogger::~RwConsoleLogger()
        {
        }
        
        void RwConsoleLogger::WriteToLog(const char* message) const
        {
            fprintf(stdout, "%s\n", message);
        }
        
        void RwConsoleLogger::WriteToError(const char* message) const
        {
            fprintf(stderr, "%s\n", message);
        }
        
    }
}
