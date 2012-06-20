/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _CONSOLELOGGER_HPP_
#define _CONSOLELOGGER_HPP_

#include <QString>

#include "Utils/Programming/Classes.h"

#include "LoggerBaseClass.h"

namespace Utils
{
    namespace Log
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class implements the a logger mechanism that writes to console.
        ///        Should not be instantiated, use instead the Logger class.
        ////////////////////////////////////////////////////////////////////////////////
        class ConsoleLogger : public LoggerBaseClass
        {
        public:
            
            ConsoleLogger();
            virtual ~ConsoleLogger();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Method for writing a message to the console
            /// \param[in] message	message to be logged
            ////////////////////////////////////////////////////////////////////////////////
            virtual void WriteToLog(const QString& message) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Method for reporting an error to the console
            /// \param[in] message	error message to reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void WriteToError(const QString& message) const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(ConsoleLogger);
            virtual void noInstantiation() {}
            
        };
        
    }
}

#endif // _CONSOLELOGGER_HPP_
