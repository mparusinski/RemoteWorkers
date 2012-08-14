/* 

RwMessagingManager.h: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwMessagingManager.h"

#include <cstdio>
#include <cstdlib>

namespace RwUtils
{
    namespace RwLog
    {
        RwMessagingManager::MessagesLevelType RwMessagingManager::m_reportingLevels = RW_NO_MESSAGE;
        
        void RwMessagingManager::turnAllOn()
        {
        	m_reportingLevels = RW_INFO_MESSAGE | RW_DEBUG_MESSAGE | RW_WARNING_MESSAGE | RW_ERROR_MESSAGE;
        }
        
        void RwMessagingManager::turnAllOff()
        {
        	m_reportingLevels = RW_NO_MESSAGE;
        }
        
        void RwMessagingManager::turnInfosOn()
        {
        	m_reportingLevels = m_reportingLevels | RW_INFO_MESSAGE;
        }
        
        void RwMessagingManager::turnInfosOff()
        {
        	m_reportingLevels = m_reportingLevels & ~RW_INFO_MESSAGE;
        }
        
        void RwMessagingManager::turnErrorsOn()
        {
        	m_reportingLevels = m_reportingLevels | RW_ERROR_MESSAGE;
        }
        
        void RwMessagingManager::turnErrorsOff()
        {
        	m_reportingLevels = m_reportingLevels & ~RW_ERROR_MESSAGE;
        }
        
        void RwMessagingManager::turnWarningsOn()
        {
        	m_reportingLevels = m_reportingLevels | RW_WARNING_MESSAGE;
        }
        
        void RwMessagingManager::turnWarningsOff()
        {
        	m_reportingLevels = m_reportingLevels & ~RW_WARNING_MESSAGE;
        }
        
        void RwMessagingManager::turnDebuggingOn()
        {
        	m_reportingLevels = m_reportingLevels | RW_DEBUG_MESSAGE;
        }
        
        void RwMessagingManager::turnDebuggingOff()
        {
        	m_reportingLevels = m_reportingLevels & ~RW_DEBUG_MESSAGE;
        }
        
        bool RwMessagingManager::isReportingInfos()
        {
        	return (m_reportingLevels & RW_INFO_MESSAGE) > 0;
        }
         
        bool RwMessagingManager::isReportingErrors()
        {
        	return (m_reportingLevels & RW_ERROR_MESSAGE) > 0;
        }
        
        bool RwMessagingManager::isReportingWarnings()
        {
        	return (m_reportingLevels & RW_WARNING_MESSAGE) > 0;
        }
        
        bool RwMessagingManager::isReportingDebugMessages()
        {
        	return (m_reportingLevels & RW_DEBUG_MESSAGE) > 0;
        }
        
        void RwMessagingManager::reportInfo(const char *message)
        {
            if (isReportingInfos())
            {
                fprintf(stdout, "%s", message);
            }
        }
        
        void RwMessagingManager::reportInfo(const char *message, int size)
        {
            if (isReportingInfos())
            {
                fwrite(message, 1, size, stdout);
            }
        }
        
        void RwMessagingManager::reportError(const char *message)
        {
            if (isReportingErrors())
            {
                fprintf(stderr, "%s", message);
            }
        }
        
        void RwMessagingManager::reportError(const char *message, int size)
        {
            if (isReportingErrors())
            {
                fwrite(message, 1, size, stderr);
            }
        }
        
        void RwMessagingManager::reportWarning(const char *message)
        {
            if (isReportingWarnings())
            {
                fprintf(stderr, "%s", message);
            }
        }
        
        void RwMessagingManager::reportWarning(const char *message, int size)
        {
            if (isReportingWarnings())
            {
                fwrite(message, 1, size, stderr);
            }
        }
        
        void RwMessagingManager::reportBug(const char* message)
        {
            if (isReportingDebugMessages())
            {
                fprintf(stderr, "%s", message);
            }
        }
        
        void RwMessagingManager::reportBug(const char* message, int size)
        {
            if (isReportingDebugMessages())
            {
                fwrite(message, 1, size, stderr);
            }
        }
        
    }
}
