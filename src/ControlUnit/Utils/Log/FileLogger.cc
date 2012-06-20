/* 

LoggerFileStrategy.hpp: Strategy for logging which output everything to a file

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "FileLogger.h"

namespace Utils
{
    namespace Log
    {
        
        FileLogger::FileLogger()
        {
            m_out = fopen("out.log", "a");
            m_err = fopen("err.log", "a");
        }
        
        FileLogger::~FileLogger()
        {
            fclose(m_out);
            fclose(m_err);
        }
        
        void FileLogger::WriteToLog(const QString& message) const
        {
            fprintf(m_out, "%s\n", message.toAscii().data());
        }
        
        void FileLogger::WriteToError(const QString& message) const
        {
            fprintf(m_err, "%s\n", message.toAscii().data());
        }
        
    }
}
