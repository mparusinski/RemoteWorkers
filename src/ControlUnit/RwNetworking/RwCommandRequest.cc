/* 

RwCommandRequest.h: Represents a request to a server to have a worker execute a command

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandRequest.h"

#include <QByteArray>
#include <QTextStream>

#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwGlobal/RwDefines.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
 
    RwCommandRequest::RwCommandRequest()
    {
        
    }
    
    RwCommandRequest::RwCommandRequest(const QString& workerName, const RwCommand& command)
    {
        m_workerName = workerName;
        m_command    = command;
    }
    
    RwCommandRequest::~RwCommandRequest()
    {
        
    }
    
    QString RwCommandRequest::getWorkerName() const {
        return m_workerName;
    }
    
    RwCommand RwCommandRequest::getCommand() const {
        return m_command;
    }
    
    void RwCommandRequest::setWorkerName(const QString &workerName)
    {
        m_workerName = workerName;
    }
    
    void RwCommandRequest::setCommand(const RwWorkerInterface::RwCommand &command)
    {
        m_command = command;
    }
    
    QString RwCommandRequest::toString() const
    {
        QString order    = m_command.getOrder();
        QStringList args = m_command.getArguments();
        
        QString message;
        
        message += REQUEST_BEGIN;
        message += REQUEST_NEW_SECTION;
        
        message += REQUEST_RW_VERSION;
        message += REQUEST_DEFINE;
        message += QString::number(RW_VERSION);
        message += REQUEST_NEW_SECTION;
        
        message += REQUEST_WORKER;
        message += REQUEST_DEFINE;
        message += m_workerName;
        message += REQUEST_NEW_SECTION;
        
        message += REQUEST_ORDER;
        message += REQUEST_DEFINE;
        message += order;
        message += REQUEST_NEW_SECTION;
        
        const int numberOfArguments = args.length();
        
        message += REQUEST_ARG_NUMBER;
        message += REQUEST_DEFINE;
        message += QString::number(numberOfArguments);
        message += REQUEST_NEW_SECTION;
        
        for (int i = 0; i < numberOfArguments; ++i)
        {
            message += REQUEST_ARG;
            message += REQUEST_DEFINE;
            message += QString::number(i);
            message += REQUEST_DEFINE;
            message += args[i];
            message += REQUEST_NEW_SECTION;
        }
        
        message += REQUEST_END;
        message += REQUEST_NEW_SECTION;
        
        return message;
    }
    
}
