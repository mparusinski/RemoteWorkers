/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _RWCONSOLELOGGER_HPP_
#define _RWCONSOLELOGGER_HPP_

#include "RwUtils/RwProgramming/RwClasses.h"

#include "RwLoggerBaseClass.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class implements the a logger mechanism that writes to console.
        ///        Should not be instantiated, use instead the Logger class.
        ////////////////////////////////////////////////////////////////////////////////
        class RwConsoleLogger : public RwLoggerBaseClass
        {
        public:
            
            RwConsoleLogger();
            virtual ~RwConsoleLogger();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Method for writing a message to the console
            /// \param[in] message	message to be logged
            ////////////////////////////////////////////////////////////////////////////////
            virtual void WriteToLog(const char* message) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Method for reporting an error to the console
            /// \param[in] message	error message to reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void WriteToError(const char* message) const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwConsoleLogger);
            virtual void noInstantiation() {}
            
        };
        
    }
}

#endif // _RWCONSOLELOGGER_HPP_
