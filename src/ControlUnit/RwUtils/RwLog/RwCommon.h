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
            RW_WRITER_INFO,
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
            
            inline RwWriter& operator <<(const char * cString)
            {
                write(cString);
                return *this;
            }
            
            inline RwWriter& operator <<(const QString& qString)
            {
                const QByteArray byteArray = qString.toLocal8Bit();
                write(byteArray.data());
                return *this;
            }
            
            inline RwWriter& operator <<(const char ch)
            {
                const char msg[] = {ch, '\0'};
                write(msg);
                return *this;
            }
            
            inline RwWriter& operator <<(const quint8 number)
            {
                return operator<<(QString::number(number));
            }
            
            inline RwWriter& operator <<(const quint16 number)
            {
                return operator<<(QString::number(number));
            }
            
            inline RwWriter& operator <<(const quint32 number)
            {
                return operator<<(QString::number(number));
            }
            
            inline RwWriter& operator <<(const qint8 number)
            {
                return operator<<(QString::number(number));
            }
            
            inline RwWriter& operator <<(const qint16 number)
            {
                return operator<<(QString::number(number));
            }
            
            inline RwWriter& operator <<(const qint32 number)
            {
                return operator<<(QString::number(number));
            }
            
            inline RwWriter& operator <<(const QByteArray& array)
            {
                const int size = array.size();
                write(array.data(), size);
                return *this;
            }
            
            inline RwWriter& operator <<(const bool boolVar)
            {
                return operator<<(static_cast<quint8>(boolVar));
            }
            
        private:
            inline void write(const char * messageToWrite) const
            {
                switch (m_writerType)
                {
                    case RW_WRITER_INFO:
#ifndef RW_NO_INFO_REPORTING
                        RwMessagingManager::reportInfo(messageToWrite);
#endif // RW_NO_INFO_REPORTING
                        break;
                    case RW_WRITER_ERROR:
#ifndef RW_NO_ERROR_REPORTING
                        RwMessagingManager::reportError(messageToWrite);
#endif // RW_NO_ERROR_REPORTING
                        break;
                    case RW_WRITER_DEBUG:
#ifndef NDEBUG
                        RwMessagingManager::reportBug(messageToWrite);
#endif // NDEBUG
                        break;
                    case RW_WRITER_WARNING:
#ifndef RW_NO_WARNING
                        RwMessagingManager::reportWarning(messageToWrite);
#endif // RW_NO_WARNING
                        break;
                    default:
                        break;
                }
            }
            
            inline void write(const char * messageToWrite, int size) const
            {
                switch (m_writerType)
                {
                    case RW_WRITER_INFO:
#ifndef RW_NO_INFO_REPORTING
                        RwMessagingManager::reportInfo(messageToWrite, size);
#endif // RW_NO_INFO_REPORTING
                        break;
                    case RW_WRITER_ERROR:
#ifndef RW_NO_ERROR_REPORTING
                        RwMessagingManager::reportError(messageToWrite, size);
#endif // RW_NO_ERROR_REPORTING
                        break;
                    case RW_WRITER_DEBUG:
#ifndef NDEBUG
                        RwMessagingManager::reportBug(messageToWrite, size);
#endif // NDEBUG
                        break;
                    case RW_WRITER_WARNING:
#ifndef RW_NO_WARNING
                        RwMessagingManager::reportWarning(messageToWrite, size);
#endif // RW_NO_WARNING
                        break;
                    default:
                        break;
                }
            }
            
            WriterType m_writerType;
        };
        
        inline char endLine()
        {
            return '\n';
        }
        
        //////////////////////////////////////////////////////////////////////////////// 
        /// \brief Returns a stream to message. Acts like a function.
        ////////////////////////////////////////////////////////////////////////////////
        inline RwWriter rwInfo()
        {
            return RwWriter(RW_WRITER_INFO);
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
        
    }
}

#endif // _RWUTILS_RWLOG_RWCOMMON_H_
