/* 

RwMessagingManager.h: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwMessagingManager.h"

#include "RwMessagingDispatcherBase.h"
#include "RwMessagingConsoleDispatcher.h"
#include "RwMessagingFileDispatcher.h"

using namespace std;

namespace RwUtils
{
    namespace RwLog
    {
        
        RwMessagingManager::RwMessagingManager()
        {
            turnAllOff();
            m_strategy = new RwMessagingConsoleDispatcher;
        }
        
        RwMessagingManager::~RwMessagingManager()
        {
            delete m_strategy;
        }
        
        RwMessagingManager* RwMessagingManager::getInstance()
        {
            static RwMessagingManager* instance = 0;
            if (instance == 0)
            {
                instance = new RwMessagingManager;
            }
            return instance;
        }
        
        void RwMessagingManager::useConsoleDispatcher()
        {
            delete m_strategy;
            m_strategy = new RwMessagingConsoleDispatcher;
        }
        
        void RwMessagingManager::useFileDispatcher()
        {
            delete m_strategy;
            m_strategy = new RwMessagingFileDispatcher();
        }
        
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
        
        bool RwMessagingManager::isReportingInfos() const
        {
        	return (m_reportingLevels & RW_INFO_MESSAGE) > 0;
        }
         
        bool RwMessagingManager::isReportingErrors() const
        {
        	return (m_reportingLevels & RW_ERROR_MESSAGE) > 0;
        }
        
        bool RwMessagingManager::isReportingWarnings() const
        {
        	return (m_reportingLevels & RW_WARNING_MESSAGE) > 0;
        }
        
        bool RwMessagingManager::isReportingDebugMessages() const
        {
        	return (m_reportingLevels & RW_DEBUG_MESSAGE) > 0;
        }
        
        void RwMessagingManager::reportInfo(const char *message) const
        {
            if (isReportingInfos())
            {
                m_strategy->writeMessage(message);
            }
        }
        
        void RwMessagingManager::reportError(const char *message) const
        {
            if (isReportingErrors())
            {
                m_strategy->writeError(message);
            }
        }
        
        void RwMessagingManager::reportWarning(const char *message) const
        {
            if (isReportingWarnings())
            {
                m_strategy->writeWarning(message);
            }
        }
        
        void RwMessagingManager::reportBug(const char* message) const
        {
            if (isReportingDebugMessages())
            {
                m_strategy->writeDebug(message);
            }
        }
        
    }
}
