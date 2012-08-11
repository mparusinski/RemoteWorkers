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
        
        RwReturnType RwCommandReply::toRawData(QByteArray &rawData) const
        {
            QDataStream dataStream(&rawData, QIODevice::WriteOnly);
            
            int size = -1;
            dataStream << size; // will me modified later
            dataStream << m_isError;
            
            if (m_isError) {
                dataStream << m_errorCode;
            } else {
                const RwWorkerInterface::RwReply::ByteArrays& replies = m_reply->getRawData();
                dataStream << replies;
            }
            
            size = rawData.size();
            
            QByteArray tmpArray;
            QDataStream tmpData(&tmpArray, QIODevice::WriteOnly);
            tmpData << size;
            
            for (int i = 0; i < tmpArray.size(); ++i)
            {
            	rawData[i] = tmpArray[i]; // copying in place
            }
            
            return RW_NO_ERROR;
        }
        
        RwReturnType RwCommandReply::fromRawData(const QByteArray &rawData)
        {
            QDataStream dataStream(rawData);
            
            int sizeDummy;
            dataStream >> sizeDummy;
            dataStream >> m_isError;
            
            if (m_isError) {
                dataStream >> m_errorCode;
            } else {
                RwWorkerInterface::RwReply::ByteArrays arrays;
                dataStream >> arrays;
                m_reply = RwWorkerInterface::RwReply::RwReplyPtr(new RwWorkerInterface::RwReply(arrays));
            }
            
            return RW_NO_ERROR;
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
        
    }
    
}
