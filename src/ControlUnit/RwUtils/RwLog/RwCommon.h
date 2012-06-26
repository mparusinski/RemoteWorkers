/* 

RwCommon.h: Common defines for Log

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWUTILS_RWLOG_RWCOMMON_H_
#define _RWUTILS_RWLOG_RWCOMMON_H_

#include <cstring>

#include <QString>
#include <QByteArray>

#include "RwMessagingManager.h"
#include "RwUtils/RwGlobal/RwReturn.h"

using namespace RwUtils::RwGlobal;

namespace RwUtils
{
    namespace RwLog {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief DO NOT USE!
        ////////////////////////////////////////////////////////////////////////////////
        typedef enum {
            RW_WRITER_MESSAGE,
            RW_WRITER_ERROR,
            RW_WRITER_WARNING,
            RW_WRITER_DEBUG
        } WriterType;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief DO NOT USE!
        ////////////////////////////////////////////////////////////////////////////////
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
                const QByteArray byteArray = qString.toLocal8Bit();
                write(byteArray.data());
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
            
            inline const RwWriter& operator <<(const QByteArray& array) const
            {
                return operator<<(array.data());
            }
            
            inline const RwWriter& operator <<(const bool boolVar)  const
            {
                return operator<<(static_cast<int>(boolVar));
            }
            
            inline const RwWriter& operator <<(const RwReturnType errorCode) const
            {
                return operator<<(static_cast<int>(errorCode));
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
#ifndef RW_NO_ERROR_REPORTING
                        RwMessagingManager::getInstance()->reportError(messageToWrite);
#endif // RW_NO_ERROR_REPORTING
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
        
        //////////////////////////////////////////////////////////////////////////////// 
        /// \brief Returns a stream to message. Acts like a function.
        ////////////////////////////////////////////////////////////////////////////////
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
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \def rwDebug() 
        /// \brief Returns a stream to debug. Acts like a function.
        ////////////////////////////////////////////////////////////////////////////////
#define rwDebug() _rwDebug(__FILE__,(__func__), __LINE__)
        
        
        
        inline RwWriter _rwError(const char* fileName, 
                                 const char* funcName, 
                                 const int lineNum)
        {
            RwWriter machine(RW_WRITER_ERROR);
            machine << "(ERROR: " << fileName << " in " << funcName << " at " << lineNum << ") ";
            return machine;
        }
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \def rwError() 
        /// \brief Returns a stream to error. Acts like a function.
        ////////////////////////////////////////////////////////////////////////////////
#define rwError() _rwError(__FILE__,(__func__), __LINE__)
        
        inline RwWriter _rwWarning(const char* fileName, 
                                   const char* funcName, 
                                   const int lineNum)
        {
            RwWriter machine(RW_WRITER_WARNING);
            machine << "(WARNING: " << fileName << " in " << funcName << " at " << lineNum << ") ";
            return machine;
        }
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \def rwError() 
        /// \brief Returns a stream to warning. Acts like a function.
        ////////////////////////////////////////////////////////////////////////////////
#define rwWarning() _rwWarning(__FILE__,(__func__), __LINE__)
        
        inline char endLine()
        {
            return '\n';
        }
        
    }
}

#endif // _RWUTILS_RWLOG_RWCOMMON_H_
