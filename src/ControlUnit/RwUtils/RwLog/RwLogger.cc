/* 

Logger.hpp: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwLogger.h"

#include <cstdio>
#include <cstdlib>

#include <QString>

#include "RwConsoleLogger.h"
#include "RwFileLogger.h"


namespace RwUtils
{
    namespace RwLog
    {
        
        RwLogger::RwLogger()
        {
            m_logging = false;
            m_reportingErrors = false;
            m_strategy = new RwConsoleLogger();
        }
        
        RwLogger::~RwLogger()
        {
            delete m_strategy;
        }
        
        RwLogger* RwLogger::getInstance()
        {
            static RwLogger* instance = 0;
            if (instance == 0)
            {
                instance = new RwLogger();
            }
            return instance;
        }
        
        void RwLogger::useConsoleLogger()
        {
            delete m_strategy;
            m_strategy = new RwConsoleLogger();
        }
        
        void RwLogger::useFileLogger()
        {
            delete m_strategy;
            m_strategy = new RwFileLogger();
        }
        
        void RwLogger::turnLoggingOff()
        {
            m_logging = false;
        }
        
        void RwLogger::turnLoggingOn()
        {
            m_logging = true;
        }
        
        void RwLogger::turnErrorReportingOff()
        {
            m_reportingErrors = false;
        }
        
        void RwLogger::turnErrorReportingOn()
        {
            m_reportingErrors = true;
        }
        
        void RwLogger::turnAllOff()
        {
            m_logging = false;
            m_reportingErrors = false;
        }
        
        void RwLogger::turnAllOn()
        {
            m_logging = true;
            m_reportingErrors = true;
        }
        
        bool RwLogger::logging()
        {
            return m_logging;
        }
        
        bool RwLogger::reportErrors()
        {
            return m_reportingErrors;
        }
        
        void RwLogger::log(const char* message) const
        {
            if (m_logging)
            {
                QString strMessage(message);
                strMessage += "\n";
                m_strategy->WriteToLog(strMessage);
            }
        }
        
        void RwLogger::log(const QString& message) const
        {
            if (m_logging)
            {
                QString actualMessage = message;
                actualMessage += "\n";
                m_strategy->WriteToLog(actualMessage);
            }
        }
        
        void RwLogger::reportError(
                                 const char* file,
                                 const char* function,
                                 const int lineNumber,
                                 const char* message) const
        {
            if (m_reportingErrors)
            {
                QString actualMessage;
                actualMessage += "ERROR (file:";
                actualMessage += file;
                actualMessage += ", function: ";
                actualMessage += function;
                actualMessage += ", lineNumber: ";
                actualMessage += QString::number(lineNumber);
                actualMessage += "): ";
                actualMessage += message;
                actualMessage += "\n";
                m_strategy->WriteToError(actualMessage);
            }
        }
        
        void RwLogger::reportError(
                                 const char* file,
                                 const char* function,
                                 const int lineNumber,
                                 const QString& message) const
        {
            if (m_reportingErrors)
            {
                QString actualMessage;
                actualMessage += "ERROR (file:";
                actualMessage += file;
                actualMessage += ", function: ";
                actualMessage += function;
                actualMessage += ", lineNumber: ";
                actualMessage += QString::number(lineNumber);
                actualMessage += "): ";
                actualMessage += message;
                actualMessage += "\n";
                m_strategy->WriteToError(actualMessage);
            }
        }
        
        void RwLogger::_debugMessage(const char* file, const char* message) const
        {
            fprintf(stderr, "DEBUG (%s): %s\n", file, message);
        }
        
        void RwLogger::_debugMessage(const char* file, const QString& message) const
        {
            QString debugMessage = "DEBUG (";
            debugMessage += file;
            debugMessage += "): ";
            debugMessage += message;
            debugMessage += "\n";
            
            fprintf(stderr, "%s", debugMessage.toAscii().data());
        }
        
    }
}
