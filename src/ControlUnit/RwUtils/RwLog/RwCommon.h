/* 

RwCommon.h: Common defines for Log

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWUTILS_RWLOG_RWCOMMON_H_
#define _RWUTILS_RWLOG_RWCOMMON_H_

#include <QString>

#include "RwMessagingManager.h"

namespace RwUtils
{
    namespace RwLog {
        
        typedef enum {
            RW_WRITER_MESSAGE,
            RW_WRITER_ERROR,
            RW_WRITER_WARNING,
            RW_WRITER_DEBUG
        } WriterType;
        
        class RwWriter {
            
        public:
            RwWriter(const WriterType writerType) { m_writerType = writerType; }
            ~RwWriter() { }
            
            inline const RwWriter& operator <<(const char * cString) const
            {
                write(cString);
                return *this;
            }
            
            inline const RwWriter& operator <<(const QString& qString) const
            {
                write(qString.toAscii().data());
                return *this;
            }
            
            inline const RwWriter& operator <<(const char ch) const
            {
                const char msg[] = {ch, '\0'};
                write(msg);
                return *this;
            }
            
            inline const RwWriter& operator <<(const int number) const
            {
                return operator<<(QString::number(number));
            }
            
        private:
            inline void write(const char * messageToWrite) const
            {
                switch (m_writerType)
                {
                    case RW_WRITER_MESSAGE:
                        RwMessagingManager::getInstance()->reportMessage(messageToWrite);
                        break;
                    case RW_WRITER_ERROR:
#ifndef RW_NO_ERROR
                        RwMessagingManager::getInstance()->reportError(messageToWrite);
#endif // RW_NO_ERROR
                        break;
                    case RW_WRITER_DEBUG:
#ifndef NDEBUG
                        RwMessagingManager::getInstance()->reportBug(messageToWrite);
#endif // NDEBUG
                        break;
                    case RW_WRITER_WARNING:
#ifndef RW_NO_WARNING
                        RwMessagingManager::getInstance()->reportWarning(messageToWrite);
#endif // RW_NO_WARNING
                        break;
                    default:
                        RwMessagingManager::getInstance()->reportMessage(messageToWrite);
                        break;
                }
            }
            
            WriterType m_writerType;
        };
        
        inline RwWriter rwMessage()
        {
            return RwWriter(RW_WRITER_MESSAGE);
        }
        
        inline RwWriter _rwDebug(const char* fileName, 
                                 const char* funcName, 
                                 const int lineNum)
        {
            RwWriter machine(RW_WRITER_DEBUG);
            machine << "(DEBUG: " << fileName << " in " << funcName << " at " << lineNum << ") ";
            return machine;
        }
        
#define rwDebug() _rwDebug(__FILE__,(__func__), __LINE__)
        
        inline RwWriter _rwError(const char* fileName, 
                                 const char* funcName, 
                                 const int lineNum)
        {
            RwWriter machine(RW_WRITER_ERROR);
            machine << "(ERROR: " << fileName << " in " << funcName << " at " << lineNum << ") ";
            return machine;
        }
        
#define rwError() _rwError(__FILE__,(__func__), __LINE__)
        
        inline RwWriter _rwWarning(const char* fileName, 
                                   const char* funcName, 
                                   const int lineNum)
        {
            RwWriter machine(RW_WRITER_WARNING);
            machine << "(WARNING: " << fileName << " in " << funcName << " at " << lineNum << ") ";
            return machine;
        }
        
#define rwWarning() _rwWarning(__FILE__,(__func__), __LINE__)
        
        inline char endLine()
        {
            return '\n';
        }
        
    }
}

#endif // _RWUTILS_RWLOG_RWCOMMON_H_
