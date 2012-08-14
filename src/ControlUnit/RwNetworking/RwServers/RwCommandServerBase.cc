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

#include "../RwNetDataStructures/RwCommandReply.h"

using namespace RwUtils::RwLog;
using namespace RwNetworking::RwNetDataStructures;

namespace RwNetworking {
    
    namespace RwServers {
        
        RwReturnType RwCommandServerBase::processData(QDataStream& in, QDataStream& out) const
        {
            // READING REQUEST
            RwNetDataStructures::RwCommandRequest request;
            in >> request;
            
            // CREATING REPLY
            RwNetDataStructures::RwCommandReply commandReply;
            RwReturnType errorCode = executeRequest(request, commandReply);
            
            // SENDING REQUEST
            QByteArray dataBlock;
            QDataStream dataBlockStream(&dataBlock, QIODevice::WriteOnly);
            dataBlockStream << int(0);
            dataBlockStream << commandReply;
            
            const int size = dataBlock.size();
            
            dataBlockStream.device()->seek(0);
            dataBlockStream << size;
            
            out << dataBlock;
            
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
            
            QDataStream dataStream(m_currentConnection->getIODevice());
            processData(dataStream, dataStream);
            
            m_currentConnection->close();
        }
        
    }
    
}
