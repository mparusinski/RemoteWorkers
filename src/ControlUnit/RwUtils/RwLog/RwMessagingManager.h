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

#include "RwUtils/RwProgramming/RwClasses.h"

#include "RwMessagingDispatcherBase.h"

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
            virtual ~RwMessagingManager();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Returns an instance of the object (see Singleton pattern).
            ///            Most important function as it is the only way to access the object
            /// \return    The only possible instance of the object
            ////////////////////////////////////////////////////////////////////////////////
            static RwMessagingManager* getInstance();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells the logger to use a console logger to perform all logging
            ///            and error reporting.
            ////////////////////////////////////////////////////////////////////////////////
            void useConsoleDispatcher();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells the logger to use a file logger to perform all logging
            ///            and error reporting.
            ////////////////////////////////////////////////////////////////////////////////
            void useFileDispatcher();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Function which logs a message (if logging if turned on)
            /// \param[in] message	Message to be logged
            ////////////////////////////////////////////////////////////////////////////////
            void reportMessage(const char* message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly.
            /////////////////////////////////////////////////////////////////////////////////
            void reportError(const char* message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly. Use the macro
            ///            error instead which will use the correct inputs
            /////////////////////////////////////////////////////////////////////////////////
            void reportWarning(const char* message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly. Use the macro
            ///            error instead which will use the correct inputs
            /////////////////////////////////////////////////////////////////////////////////
            void reportBug(const char* message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on message to log all messages to appropriate dispatcher.
            /////////////////////////////////////////////////////////////////////////////////
            void turnMessagingOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off message for normal messages, no message will be logged
            /////////////////////////////////////////////////////////////////////////////////
            void turnMessagingOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on error reporting and uses appropriate dispatcher to
            ///            register errors
            /////////////////////////////////////////////////////////////////////////////////
            void turnErrorReportingOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off error reporting. No error will be reported.
            /////////////////////////////////////////////////////////////////////////////////
            void turnErrorReportingOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on warnings.
            /////////////////////////////////////////////////////////////////////////////////
            void turnWarningsOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off warnings.
            /////////////////////////////////////////////////////////////////////////////////
            void turnWarningsOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on warnings.
            /////////////////////////////////////////////////////////////////////////////////
            void turnDebuggingOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on warnings.
            /////////////////////////////////////////////////////////////////////////////////
            void turnDebuggingOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches both logging and error reporting error on. All messages
            ///            and error messages will be sent to appropriate logger.
            /////////////////////////////////////////////////////////////////////////////////
            void turnAllOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches both logging and error reporting error off. No messages
            ///            will be logged and no error will be reported.
            /////////////////////////////////////////////////////////////////////////////////
            void turnAllOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting messages
            /// \return    True if message reporting false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            bool isReportingMessages() const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting errors
            /// \return    True if error reporting false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            bool isReportingErrors() const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting warnings
            /// \return    True if warning reporting false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            bool isReportingWarnings() const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting debug messages
            /// \return    True if debug messages are reported false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            bool isReportingDebugMessages() const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwMessagingManager);
            RwMessagingManager(); // singleton pattern
            
            bool m_sendingMessages;
            bool m_reportingErrors;
            bool m_debugging;
            bool m_reportingWarning;
            
            RwMessagingDispatcherBase* m_strategy;
        };
        
    }
}

#endif // _RWUTILS_RWLOG_RWMESSAGINGMANAGER_H_
