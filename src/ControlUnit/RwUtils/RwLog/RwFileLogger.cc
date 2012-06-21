/* 

RwFileLogger.cc: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwFileLogger.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        RwFileLogger::RwFileLogger()
        {
            m_out = fopen("out.log", "a");
            m_err = fopen("err.log", "a");
        }
        
        RwFileLogger::~RwFileLogger()
        {
            fclose(m_out);
            fclose(m_err);
        }
        
        void RwFileLogger::WriteToLog(const char* message) const
        {
            fprintf(m_out, "%s\n", message);
        }
        
        void RwFileLogger::WriteToError(const char* message) const
        {
            fprintf(m_err, "%s\n", message);
        }
        
    }
}
