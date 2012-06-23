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
            m_sendingMessages  = true;
            m_reportingWarning = true;
            m_reportingErrors  = true;
            m_debugging        = true;
        }
        
        void RwMessagingManager::turnAllOff()
        {
            m_sendingMessages  = false;
            m_reportingWarning = false;
            m_reportingErrors  = false;
            m_debugging        = false;
        }
        
        void RwMessagingManager::turnMessagingOn()
        {
            m_sendingMessages = true;
        }
        
        void RwMessagingManager::turnMessagingOff()
        {
            m_sendingMessages = false;
        }
        
        void RwMessagingManager::turnErrorReportingOn()
        {
            m_reportingErrors = true;
        }
        
        void RwMessagingManager::turnErrorReportingOff()
        {
            m_reportingErrors = false;
        }
        
        void RwMessagingManager::turnWarningsOn()
        {
            m_reportingWarning = true;
        }
        
        void RwMessagingManager::turnWarningsOff()
        {
            m_reportingWarning = false;
        }
        
        void RwMessagingManager::turnDebuggingOn()
        {
            m_debugging = true;
        }
        
        void RwMessagingManager::turnDebuggingOff()
        {
            m_debugging = false;
        }
        
        bool RwMessagingManager::isReportingMessages() const
        {
            return m_sendingMessages;
        }
         
        bool RwMessagingManager::isReportingErrors() const
        {
            return m_reportingErrors;
        }
        
        bool RwMessagingManager::isReportingWarnings() const
        {
            return m_reportingWarning;
        }
        
        bool RwMessagingManager::isReportingDebugMessages() const
        {
            return m_debugging;
        }
        
        void RwMessagingManager::reportMessage(const char *message) const
        {
            if (m_sendingMessages)
            {
                m_strategy->writeMessage(message);
            }
        }
        
        void RwMessagingManager::reportError(const char *message) const
        {
            if (m_reportingErrors)
            {
                m_strategy->writeError(message);
            }
        }
        
        void RwMessagingManager::reportWarning(const char *message) const
        {
            if (m_reportingWarning)
            {
                m_strategy->writeWarning(message);
            }
        }
        
        void RwMessagingManager::reportBug(const char* message) const
        {
            if (m_debugging)
            {
                m_strategy->writeDebug(message);
            }
        }
        
    }
}
