/* 

RwCommandRequest.h: Represents a request to a server to have a worker execute a command

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandRequest.h"

#include <QByteArray>
#include <QDataStream>
#include <QTextStream>

#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwGlobal/RwDefines.h"

// #define REQUEST_BEGIN "REQUEST_START"
// #define REQUEST_END   "REQUEST_END"
// #define REQUEST_RW_VERSION "REQUEST_RW_VERSION"
// #define REQUEST_WORKER  "REQUEST_WORKER"
// #define REQUEST_ORDER   "REQUEST_ORDER"
// #define REQUEST_ARG_NUMBER "REQUEST_ARG_NUMBER"

using namespace RwUtils::RwLog;

//inline QDataStream &operator<<(QDataStream & stream, const QString& string) {
//    QByteArray stringArray = string.toLocal8Bit();
//    stream << stringArray.data();
//    return stream;
//}

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        RwCommandRequest::RwCommandRequest()
        {
            
        }
        
        RwCommandRequest::RwCommandRequest(const QString& workerName, const RwCommand::RwCommandPtr& command)
        {
            m_workerName = workerName;
            m_command = command;
        }
        
        RwCommandRequest::~RwCommandRequest()
        {
            
        }
        
        QString RwCommandRequest::getWorkerName() const {
            return m_workerName;
        }
        
        const RwCommand::RwCommandPtr& RwCommandRequest::getCommand() const {
            return m_command;
        }
        
        void RwCommandRequest::setWorkerName(const QString &workerName)
        {
            m_workerName = workerName;
        }
        
        void RwCommandRequest::setCommand(const RwCommand::RwCommandPtr &command)
        {
            m_command = command;
        }
        
        RwReturnType RwCommandRequest::toRawData(QByteArray& rawData) const
        {
            QDataStream dataStream(&rawData, QIODevice::WriteOnly);
            dataStream.setVersion(QDataStream::Qt_4_8);
            
            dataStream << m_workerName;
            dataStream << m_command->getOrder();
            
            const QStringList& args = m_command->getArguments();
            dataStream << args;
          
            return RW_NO_ERROR;
        }
        
        RwReturnType RwCommandRequest::fromRawData(const QByteArray &rawData)
        {
            // CONVERTING RAW DATA INTO TEXT STREAM
            QDataStream dataStream(rawData);
            
            QString order;
            QStringList argumentsList;
            
            dataStream >> m_workerName;
            dataStream >> order;
            dataStream >> argumentsList;
            
            m_command = RwCommand::RwCommandPtr(new RwCommand(order, argumentsList));

            return RW_NO_ERROR;
        }
        
        bool RwCommandRequest::operator==(const RwNetworking::RwNetDataStructures::RwCommandRequest &other) const
        {
            return (m_workerName == other.m_workerName)
            		&& (m_command->getOrder() == other.m_command->getOrder())
            		&& (m_command->getArguments() == other.m_command->getArguments());
        }
        
    }
    
}
