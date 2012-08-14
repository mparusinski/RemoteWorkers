/* 

RwCommandReply.h: Represents a reply from server after a worker executes a command

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandReply.h"

#include <QPair>
#include <QDataStream>

#include "RwUtils/RwLog/RwCommon.h"

#define REPLY_BEGIN "REPLY_BEGIN"
#define REPLY_TYPE "REPLY_TYPE"
#define REPLY_FILES_NUMBER "REPLY_FILES_NUMBER"
#define REPLY_FILE "REPLY_FILE"
#define REPLY_END "REPLY_END"

using namespace RwUtils::RwLog;

//inline QDataStream &operator<<(QDataStream & stream, const QString& string) {
//    QByteArray stringArray = string.toLocal8Bit();
//    stream << stringArray.data();
//    return stream;
//}

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        RwCommandReply::RwCommandReply()
        {
            m_isError = true;
            m_errorCode = RW_NO_ERROR;
        }
        
        RwCommandReply::RwCommandReply(const RwReturnType errorCode)
        {
            m_isError = true;
            m_errorCode = errorCode;
        }
        
        RwCommandReply::RwCommandReply(const RwWorkerInterface::RwReply::RwReplyPtr& reply)
        {
            m_isError = false;
            m_reply = reply;
        }
        
        RwCommandReply::~RwCommandReply()
        {
            
        }
        
        void RwCommandReply::setErrorCode(const RwReturnType errorCode)
        {
            m_isError = true;
            m_errorCode = errorCode;
        }
        
        void RwCommandReply::setReply(const RwWorkerInterface::RwReply::RwReplyPtr &reply)
        {
            m_isError = false;
            m_reply = reply;
        }
        
        void RwCommandReply::copyFrom(const RwCommandReply &other)
        {
            if (other.m_isError) {
                m_isError = true;
                m_errorCode = other.m_errorCode;
            } else {
                m_isError = false;
                m_reply = other.m_reply;
            }
        }
        
        bool RwCommandReply::isError() const
        {
            return m_isError;
        }
        
        RwReturnType RwCommandReply::getErrorCode() const
        {
            return m_errorCode;
        }
        
        RwWorkerInterface::RwReply::RwReplyPtr& RwCommandReply::getReply()
        {
            return m_reply;
        }
        
        const RwWorkerInterface::RwReply::RwReplyPtr& RwCommandReply::getReply() const
        {
            return m_reply;
        }
        
        bool RwCommandReply::operator==(const RwNetworking::RwNetDataStructures::RwCommandReply &other) const
        {
            if (m_isError && other.m_isError) {
                return m_errorCode == other.m_errorCode;
            } else if (!m_isError && !other.m_isError) {
                return m_reply->getRawData() == other.m_reply->getRawData();
            } else {
                return false;
            }
        }
        
        QString RwCommandReply::toString() const
        {
            typedef RwWorkerInterface::RwReply::ByteArrays ByteArrays;
            
            if (m_isError)
            {
                return QString("Reply is an error: ") + retTypeToStr(m_errorCode);
            }
            else
            {
                QString stringVersion = "Reply is not an error: \n";
                const ByteArrays& arrays = m_reply->getRawData();
                ByteArrays::const_iterator iter;
                for (iter = arrays.begin(); iter != arrays.end(); ++iter)
                {
                    const QString& fileName = iter->first;
                    const QByteArray& fileData = iter->second;
                    stringVersion += fileName;
                    stringVersion += ": \n";
                    stringVersion += fileData.data();
                    stringVersion += "\n";
                }
                
                return stringVersion;
            }
        }
        
    }
    
}
