/* 

RwMessagingConsoleDispatcher.cc: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwMessagingConsoleDispatcher.h"

#include <cstdio>
#include <cstdlib>

namespace RwUtils
{
    namespace RwLog
    {
        
        RwMessagingConsoleDispatcher::RwMessagingConsoleDispatcher()
        {
        }
        
        RwMessagingConsoleDispatcher::~RwMessagingConsoleDispatcher()
        {
        }
        
        void RwMessagingConsoleDispatcher::writeMessage(const char *message) const
        {
            fprintf(stdout, "%s", message);
        }
        
        void RwMessagingConsoleDispatcher::writeError(const char* errorMessage) const
        {
            fprintf(stderr, "%s", errorMessage);
        }
        
        void RwMessagingConsoleDispatcher::writeWarning(const char *warningMessage) const
        {
            fprintf(stderr, "%s", warningMessage);
        }
        
        void RwMessagingConsoleDispatcher::writeDebug(const char *debugMessage) const
        {
            fprintf(stderr, "%s", debugMessage);
        }
        
    }
}
