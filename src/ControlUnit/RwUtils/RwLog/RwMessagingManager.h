/* 

RwMessagingManager.h: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _RWUTILS_RWLOG_RWMESSAGINGMANAGER_H_
#define _RWUTILS_RWLOG_RWMESSAGINGMANAGER_H_

#include <QString>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class provides an interface for reporting, errors, warnings and
        ///        debug messages. It does so using external message dispatcher.
        ///        It is a singleton class. Prefer using the specialised classes for
        ///        each type of error.
        ////////////////////////////////////////////////////////////////////////////////
        class RwMessagingManager
        {
        public:

            typedef int MessagesLevelType;
#define RW_NO_MESSAGE 0
#define RW_DEBUG_MESSAGE 1
#define RW_INFO_MESSAGE 2
#define RW_WARNING_MESSAGE 4
#define RW_ERROR_MESSAGE 8
            
            static MessagesLevelType m_reportingLevels;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Function which logs an info message (if logging if turned on)
            /// \param[in] message	Message to be logged
            ////////////////////////////////////////////////////////////////////////////////
            static void reportInfo(const char* message);
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly.
            /////////////////////////////////////////////////////////////////////////////////
            static void reportError(const char* message);
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly. Use the macro
            ///            error instead which will use the correct inputs
            /////////////////////////////////////////////////////////////////////////////////
            static void reportWarning(const char* message);
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly. Use the macro
            ///            error instead which will use the correct inputs
            /////////////////////////////////////////////////////////////////////////////////
            static void reportBug(const char* message);
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on message to log all messages to appropriate dispatcher.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnInfosOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off message for normal messages, no message will be logged
            /////////////////////////////////////////////////////////////////////////////////
            static void turnInfosOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on error reporting and uses appropriate dispatcher to
            ///            register errors
            /////////////////////////////////////////////////////////////////////////////////
            static void turnErrorsOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off error reporting. No error will be reported.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnErrorsOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on warnings.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnWarningsOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off warnings.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnWarningsOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on warnings.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnDebuggingOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on warnings.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnDebuggingOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches both logging and error reporting error on. All messages
            ///            and error messages will be sent to appropriate logger.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnAllOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches both logging and error reporting error off. No messages
            ///            will be logged and no error will be reported.
            /////////////////////////////////////////////////////////////////////////////////
            static void turnAllOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting messages
            /// \return    True if message reporting false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            static bool isReportingInfos();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting errors
            /// \return    True if error reporting false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            static bool isReportingErrors();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting warnings
            /// \return    True if warning reporting false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            static bool isReportingWarnings();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting debug messages
            /// \return    True if debug messages are reported false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            static bool isReportingDebugMessages();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwMessagingManager);
            RwMessagingManager(); // pure static class
        };
        
    }
}

#endif // _RWUTILS_RWLOG_RWMESSAGINGMANAGER_H_
