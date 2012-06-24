/* 

RwCommandReply.h: Represents a reply from server after a worker executes a command

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandReply.h"

#include <QPair>

namespace RwNetworking {
    
    RwCommandReply::RwCommandReply()
    {
        
    }
    
    RwCommandReply::RwCommandReply(RwReturnType errorCode)
    {
        m_isError = true;
        m_errorCode = errorCode;
    }
    
    RwCommandReply::RwCommandReply(const RwWorkerInterface::RwReply& reply)
    {
        m_isError = false;
        m_reply = reply;
    }
    
    RwCommandReply::~RwCommandReply()
    {
        
    }
    
    QString RwCommandReply::toString() const
    {
        QString message;
        
        message += REPLY_BEGIN;
        message += REPLY_NEW_SECTION;
        
        message += REPLY_TYPE;
        message += REPLY_DEFINE;
        if (m_isError) {
            message += REPLY_ERROR;
            message += REPLY_NEW_SECTION;
            
            message += REPLY_ERROR_MESSAGE;
            message += REPLY_DEFINE;
            message += QString::number(m_errorCode);
            message += REPLY_NEW_SECTION;
        } else {
            message += REPLY_REPLY;
            message += REPLY_NEW_SECTION;
            
            const int numberOfFiles = m_reply.numberOfFiles();
            
            message += REPLY_FILES_NUMBER;
            message += REPLY_DEFINE;
            message += numberOfFiles;
            message += REPLY_NEW_SECTION;
            
            for (int i = 0; i < numberOfFiles; ++i)
            {
                const QPair<QString, RwByteArray>& pair = m_reply[i];
                message += REPLY_FILENAME;
                message += REPLY_DEFINE;
                message += pair.first;
                message += REPLY_NEW_SECTION;
                
                message += REPLY_CONTENT_SIZE;
                message += REPLY_DEFINE;
                message += pair.second.size();
                message += REPLY_NEW_SECTION;
                
                message += REPLY_CONTENT;
                message += REPLY_DEFINE;
                message += pair.second.getRawData();
                message += REPLY_NEW_SECTION;
            }
        }
        
        message += REPLY_END;
        
        return message;
    }
    
}
