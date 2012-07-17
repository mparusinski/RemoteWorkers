/* 

RwCommandServerBase.cc: Interface to the network socket

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

//#include "RwCommandServerBase.h"

#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwWorkerInterface/RwCommand.h"
#include "RwWorkerInterface/RwReply.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;
using namespace RwWorkerInterface;

namespace RwNetworking {
    
    namespace RwServers {
        
        template <typename SocketType>
        RwCommandServerBase<SocketType>::RwCommandServerBase(QObject* parent) 
        : QObject(parent)
        {

        }
        
        template <typename SocketType>
        RwCommandServerBase<SocketType>::~RwCommandServerBase()
        {
            
        }
        
        template <typename SocketType>
        RwReturnType RwCommandServerBase<SocketType>::processData(const QByteArray &in, QByteArray &out) const
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
        
        template <typename SocketType>
        RwReturnType RwCommandServerBase<SocketType>::executeRequest(const RwNetDataStructures::RwCommandRequest &request, RwNetDataStructures::RwCommandReply &reply) const
        {
            RwReturnType errorCode = RW_NO_ERROR;
            
            RwWorker worker;
            errorCode = RwManagement::getInstance()->createWorker(request.getWorkerName(), worker);
            
            if (errorCode != RW_NO_ERROR) {
                rwError() << "The worker " << request.getWorkerName() << " was not found" << endLine();
                return errorCode;
            }
            
            errorCode = worker.executeCommand(request.getCommand());
            
            if (errorCode != RW_NO_ERROR) {
                rwError() << "The worker " << request.getWorkerName() << " did not execute order " << request.getCommand().getOrder() << " properly" << RwUtils::RwLog::endLine();
                
                reply.setErrorCode(errorCode);
                return errorCode;
            }
            
            RwReply realReply;
            errorCode = worker.getReply(realReply);
            
            if ( errorCode != RW_NO_ERROR ) {
                rwError() << "The worker did not produce a good reply" << RwUtils::RwLog::endLine();
                reply.setErrorCode(errorCode);
            } else {
                reply.setReply(realReply);
            }
            
            return errorCode;
        }
        
        template <typename SocketType>
        void RwCommandServerBase<SocketType>::abstractProcessConnection() const
        {
            QObject::connect(m_currentConnection, SIGNAL(disconnected()), 
                             m_currentConnection, SLOT(deleteLater()));
            
            while (m_currentConnection->bytesAvailable() < (int)sizeof(quint32)) // waiting for at least 32 bits of data
                m_currentConnection->waitForReadyRead();
            
            // RECEIVING DATA
            QByteArray receivedData = m_currentConnection->readAll(); // This may be dangerous
            QByteArray responseData;
            RwReturnType errorCode = processData(receivedData, responseData);
            
            if (errorCode != RW_NO_ERROR)
            {   
                // ERROR WILL ALREADY BEEN REPORTED
                return;
            }
            
            // SENDING RAW DATA
            m_currentConnection->write(responseData);
            
            delete m_currentConnection;
        }
        
    }
    
}
