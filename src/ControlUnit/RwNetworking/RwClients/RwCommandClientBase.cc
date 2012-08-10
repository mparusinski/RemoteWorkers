/* 

RwCommandClientBase.cc: Base class for all command clients

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

 */

#include "RwCommandClientBase.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwClients {
        
        RwCommandClientBase::RwCommandClientBase(QObject* parent) : QObject(parent)
        {
            m_connected = false;
            m_blockSize = 0;
        }
        
        RwCommandClientBase::~RwCommandClientBase()
        {
            
        }
        
        void RwCommandClientBase::clientConnected()
        {
            m_connected = true;
        }
        
        void RwCommandClientBase::clientDisconnected()
        {
            m_connected = false;
        }
        
        RwReturnType RwCommandClientBase::getReply(RwNetDataStructures::RwCommandReply &reply)
        {
            reply.copyFrom(m_reply);
            return RW_NO_ERROR;
        }
        
        void RwCommandClientBase::connectSignalAndSlots()
        {
            connect(m_socket, SIGNAL(connected()),
                    this, SLOT(clientConnected()));
            connect(m_socket, SIGNAL(disconnected()),
                    this, SLOT(clientDisconnected()));
            
            connect(m_socket, SIGNAL(dataReady()),
                    this, SLOT(readReady()));
        }
        
        void RwCommandClientBase::readReady()
        {
            while (m_socket->bytesAvailable() < (int) sizeof(quint32))
                m_socket->waitForBytesWritten();
            
            QByteArray block = m_socket->readAll();
            
            if (m_blockSize <= 0)
            {
                QDataStream in(block);
                in >> m_blockSize;
            }
            
            m_buffer += block;
            
            if (m_buffer.size() >= m_blockSize) // finished reading
            {
                m_reply.fromRawData(m_buffer);
                m_blockSize = 0;
                m_buffer.clear();
                m_socket->close();
                emit replyReady();
            }
        }
        
        RwReturnType RwCommandClientBase::sendRequest(const RwNetDataStructures::RwCommandRequest& request)
        {
            if ( !m_connected )
            {
                rwError() << "The client is not connected! Please connect to server first." << endLine();
                return RW_ERROR_NO_CONNECTION;
            }
            
            // SEND REQUEST
            QByteArray requestRawData;
            const RwReturnType returnMsg = request.toRawData(requestRawData);
            m_socket->write(requestRawData);
            m_socket->flush();
            
            return returnMsg;
        }
        
        RwReturnType RwCommandClientBase::sendRequest(QByteArray& requestInRawFormat)
        {
            if ( !m_connected )
            {
                rwError() << "The client is not connected! Please connect to server first." << endLine();
                return RW_ERROR_NO_CONNECTION;
            }
            
            m_socket->write(requestInRawFormat);
            m_socket->flush();
            
            return RW_NO_ERROR;
        }
        
    }

}
