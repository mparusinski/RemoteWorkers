/* 

RwLogger.h: System to log errors and message smartly

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _RWUTILS_RWLOG_RWLOGGER_H_
#define _RWUTILS_RWLOG_RWLOGGER_H_

#include "RwUtils/RwProgramming/RwClasses.h"

#include <QString>

#include "RwLoggerBaseClass.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class provides an interface to logging, report errors and
        ///        debugging. It does so using external logging mechanism classes.
        ///        It also provides the necessary mechanism to easily silence all
        ///        logging/error messages. It also provide a framework allowing to choose
        ///        where to send the logs and the errors messages. The logger is a
        ///        singleton class
        ////////////////////////////////////////////////////////////////////////////////
        class RwLogger
        {
        public:
            virtual ~RwLogger();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Returns an instance of the object (see Singleton pattern).
            ///            Most important function as it is the only way to access the object
            /// \return    The only possible instance of the object
            ////////////////////////////////////////////////////////////////////////////////
            static RwLogger* getInstance();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells the logger to use a console logger to perform all logging
            ///            and error reporting.
            ////////////////////////////////////////////////////////////////////////////////
            void useConsoleLogger();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells the logger to use a file logger to perform all logging
            ///            and error reporting.
            ////////////////////////////////////////////////////////////////////////////////
            void useFileLogger();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Function which logs a message (if logging if turned on)
            /// \param[in] message	Message to be logged
            ////////////////////////////////////////////////////////////////////////////////
            void log(const char* message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Function which logs a message (if logging if turned on)
            /// \param[in] message	Message to be logged
            /////////////////////////////////////////////////////////////////////////////////
            void log(const QString& message) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \def error(message)
            ///            Reports an error using the Logger class: it calls reportError
            ///            with appropriate input. The message obtained will display the file
            ///            in which the error occurred, the function name and the line number.
            ///            Use this instead of reportError.
            ////////////////////////////////////////////////////////////////////////////////
#define error_msg(message) reportError(__FILE__, (__func__), __LINE__, message)
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \def debug(message)
            ///            Macro expanding to _debugMessage a member function of Logger.
            ///            This macro reports a debugging message composed of the file name
            ///            and the debugging message. It will always report message on the
            ///            console regardless of the configuration of the logger. All
            ///            debugging messages are discarded in non DEBUG compiles
            ////////////////////////////////////////////////////////////////////////////////
#ifndef NDEBUG
#define debug(message) _debugMessage(__FILE__, message);
#else
#define debug(message)
#endif // NDEBUG
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly. Use the macro
            ///            error instead which will use the correct inputs
            /////////////////////////////////////////////////////////////////////////////////
            void reportError(
                             const char* file,
                             const char* function,
                             const int lineNumber,
                             const char* message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Reports an error, do not use this function directly. Use the macro
            ///            error instead which will use the correct inputs
            /////////////////////////////////////////////////////////////////////////////////
            void reportError(
                             const char* file,
                             const char* function,
                             const int lineNumber,
                             const QString& message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on logger to log all messages to appropriate logger.
            /////////////////////////////////////////////////////////////////////////////////
            void turnLoggingOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off logging for normal messages, no message will be logged
            /////////////////////////////////////////////////////////////////////////////////
            void turnLoggingOff();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches on error reporting and uses appropriate logger to
            ///            register errors
            /////////////////////////////////////////////////////////////////////////////////
            void turnErrorReportingOn();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Switches off error reporting. No error will be reported.
            /////////////////////////////////////////////////////////////////////////////////
            void turnErrorReportingOff();
            
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
            /// \brief     Tells whether logging is turned on
            /// \return    True if logging false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            bool logging();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Tells whether reporting errors is turned on
            /// \return    True if reporting error false otherwise
            /////////////////////////////////////////////////////////////////////////////////
            bool reportErrors();
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Sends a debug message to the console. Do not use this function
            ///            directly, use the debug macro instead
            /////////////////////////////////////////////////////////////////////////////////
            void _debugMessage(const char* file, const char* message) const;
            
            /////////////////////////////////////////////////////////////////////////////////
            /// \brief     Sends a debug message to the console. Do not use this function
            ///            directly, use the debug macro instead
            /////////////////////////////////////////////////////////////////////////////////
            void _debugMessage(const char* file, const QString& message) const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwLogger);
            RwLogger(); // singleton pattern
            
            bool m_logging;
            bool m_reportingErrors;
            
            RwLoggerBaseClass* m_strategy;
        };
        
    }
}

#endif // _RWUTILS_RWLOG_RWLOGGER_H_
