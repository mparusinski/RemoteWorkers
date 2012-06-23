/* 

RwMessagingFileDispatcher.cc: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwMessagingFileDispatcher.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        RwMessagingFileDispatcher::RwMessagingFileDispatcher()
        {
            m_out     = fopen("out.log", "a");
            m_err     = fopen("err.log", "a");
            m_debug   = fopen("debug.log", "a");
            m_warning = fopen("warning.log", "a");
        }
        
        RwMessagingFileDispatcher::~RwMessagingFileDispatcher()
        {
            fclose(m_out);
            fclose(m_err);
            fclose(m_debug);
            fclose(m_warning);
        }
        
        void RwMessagingFileDispatcher::writeMessage(const char* message) const
        {
            fprintf(m_out, "%s", message);
        }
        
        void RwMessagingFileDispatcher::writeError(const char* errorMessage) const
        {
            fprintf(m_err, "%s", errorMessage);
        }
        
        void RwMessagingFileDispatcher::writeDebug(const char *debugMessage) const
        {
            fprintf(m_debug, "%s", debugMessage);
        }
        
        void RwMessagingFileDispatcher::writeWarning(const char *warningMessage) const
        {
            fprintf(m_warning, "%s", warningMessage);
        }
        
    }
}
