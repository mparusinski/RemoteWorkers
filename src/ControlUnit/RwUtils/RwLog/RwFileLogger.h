/* 

RwFileLogger.h: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _RWUTILS_RWLOG_RWFILELOGGER_H_
#define _RWUTILS_RWLOG_RWFILELOGGER_H_

#include "RwLoggerBaseClass.h"

#include <cstdio>
#include <cstdlib>

#include "RwUtils/RwProgramming/RwClasses.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class implements the a logger mechanism that writes to files.
        ///        Should not be instantiated, use instead the Logger class.
        ////////////////////////////////////////////////////////////////////////////////
        class RwFileLogger : public RwLoggerBaseClass
        {
        public:
            
            RwFileLogger();
            virtual ~RwFileLogger();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Method for writing a message to a log which is stored in a file
            /// \param[in] message	message to be logged
            ////////////////////////////////////////////////////////////////////////////////
            virtual void WriteToLog(const char* message) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Method for reporting an error to an error file
            /// \param[in] message	error message to reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void WriteToError(const char* message) const;
            
        private:
            FILE* m_out;
            FILE* m_err;
            
            DISALLOW_COPY_AND_ASSIGN(RwFileLogger);
            virtual void noInstantiation() {}
        };
        
    }
}

#endif // _RWUTILS_RWLOG_RWFILELOGGER_H_
