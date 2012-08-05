/* 

RwCommandServerBase.cc: Interface to the network socket

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#include "RwCommandServerBase.h"

#include "RwUtils/RwLog/RwCommon.h"
#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwHistory/RwEventLog.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwServers {
        
        RwReturnType RwCommandServerBase::processData(const QByteArray& in, QByteArray& out) const
        {
            // READING REQUEST
            RwNetDataStructures::RwCommandRequest request;
            RwReturnType errorCode = request.fromRawData(in);
            
            // CREATING REPLY
            RwNetDataStructures::RwCommandReply commandReply;
            errorCode = errorCode | executeRequest(request, commandReply);
            
            commandReply.toRawData(out);
            
            return errorCode;
        }
        
        RwReturnType RwCommandServerBase::executeRequest(const RwNetDataStructures::RwCommandRequest& request, RwNetDataStructures::RwCommandReply& reply) const
        {
            RwReturnType errorCode = RW_NO_ERROR;
            RwReply::RwReplyPtr realReply;
            RwWorker::RwWorkerPtr worker;
            
            errorCode = RwManagement::getInstance()->createWorker(request.getWorkerName(), worker);
            
            if (errorCode != RW_NO_ERROR)
                goto cut_through;
            
            errorCode = worker->executeCommand(request.getCommand());
            
            RwHistory::RwEventLog::getInstance()->workerExecutedCommand(worker, request.getCommand());
            
            if (errorCode != RW_NO_ERROR)
                goto cut_through;
            
            errorCode = worker->getReply(realReply);
            
        cut_through:
            
            if ( errorCode != RW_NO_ERROR ) {
                reply.setErrorCode(errorCode);
            } else {
                reply.setReply(realReply);
            }
            
            return errorCode;
        }
        
        void RwCommandServerBase::abstractProcessConnection() const
        {
            QObject::connect(m_currentConnection, SIGNAL(disconnected()),
                             m_currentConnection, SLOT(deleteLater()));
            
            while (m_currentConnection->bytesAvailable() < (int)sizeof(quint32)) // waiting for at least 32 bits of data
                m_currentConnection->waitForReadyRead();
            
            // RECEIVING DATA
            QByteArray receivedData = m_currentConnection->readAll(); // This may be dangerous
            QByteArray responseData;
            processData(receivedData, responseData);
            
            // SENDING RAW DATA
            m_currentConnection->write(responseData);
        }
        
    }
    
}
