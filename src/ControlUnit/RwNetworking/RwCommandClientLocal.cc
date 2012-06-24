/* 

RwCommandClientLocal.cc: Client for RwCommandServerLocal

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/06/2012.

*/

#include "RwCommandClientLocal.h"

#include <QDataStream>

#include "RwUtils/RwGlobal/RwDefines.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwDataStructures/RwByteArray.h"

using namespace RwDataStructures;
using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    RwCommandClientLocal::RwCommandClientLocal(QObject* parent, const QString& serverName)
        : QObject(parent) 
    {
        m_connected = false;
        m_serverName = serverName;
        m_localSocket = new QLocalSocket(this);
        
        QObject::connect(m_localSocket, SIGNAL(connected()), 
                         this, SLOT(clientConnected()));
        QObject::connect(m_localSocket, SIGNAL(disconnected()), 
                         this, SLOT(clientDisconnected()));
        
        QObject::connect(m_localSocket, SIGNAL(readyRead()), 
                         this, SLOT(readReady()));
        QObject::connect(m_localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)),
                        this, SLOT(clientError(QLocalSocket::LocalSocketError)));
    }
    
    RwCommandClientLocal::~RwCommandClientLocal() 
    {
        m_localSocket->abort();
        delete m_localSocket;
    }
    
    void RwCommandClientLocal::clientConnected()
    {
        m_connected = true;
    }
    
    void RwCommandClientLocal::clientDisconnected()
    {
        m_connected = false;
        // rwDebug() << "local client has disconnected from server " << m_serverName << endLine();
    }
    
    void RwCommandClientLocal::readReady()
    {
        // rwDebug() << "local client is ready to read" << endLine();
    }
    
    void RwCommandClientLocal::connectToServer()
    {
        m_localSocket->abort();
//        rwDebug() << "Connecting to server " << m_serverName << endLine();
        m_localSocket->connectToServer(m_serverName);
    }
    
    void RwCommandClientLocal::disconnectFromServer()
    {
        m_localSocket->disconnectFromServer();
    }
    
    void RwCommandClientLocal::clientError(QLocalSocket::LocalSocketError socketError)
    {
        rwError() << "Client error: " << m_localSocket->errorString() << endLine();
    }
    
    RwReturnType RwCommandClientLocal::sendRequest(const RwCommandRequest &request)
    {
        if ( !m_connected )
        {
            rwError() << "The local client is not connected! Please connect to local server." << endLine();
            return RW_ERROR_NO_CONNECTION;
        }
        
        // SEND REQUEST
        RwByteArray rawData;
        const RwReturnType returnMsg = toRawData(request, rawData);
        
        m_localSocket->write(rawData.getRawData(), rawData.size());
        
        // READ REPLY
        RwByteArray replyRawData;
        QByteArray replyArray = m_localSocket->readAll();
        replyRawData.setRawData(replyArray.data(), replyArray.size());
        
        return returnMsg;
    }
    
    RwReturnType RwCommandClientLocal::toRawData(const RwCommandRequest& request, RwDataStructures::RwByteArray& rawData) const
    {
        // Packing the message together
        QString message = request.toString();
        
        // rwMessage() << message << endLine();
        
        // Turn it raw
        QByteArray byteArray = message.toLocal8Bit();
        const int totalLength = byteArray.length();
        rawData.setRawData(byteArray.data(), totalLength);
        
        return RW_NO_ERROR;
    }
    
    RwReturnType RwCommandClientLocal::fromRawData(RwNetworking::RwCommandReply &reply, const RwDataStructures::RwByteArray &rawData) const
    {
        QByteArray byteArray(rawData.getRawData(), rawData.size());
        QTextStream textStream(&byteArray, QIODevice::ReadOnly);
        
        QString currentText;
        textStream >> currentText;
        
        if (currentText != REPLY_BEGIN)
        {
            rwError() << "Begin delimiter is missing for reply" << endLine();
            return RW_ERROR_READING_NETWORK_MESSAGE;
        }
        
        textStream >> currentText;
        
        if (currentText != REPLY_TYPE)
        {
            rwError() << "Missing type information for reply" << endLine();
            return RW_ERROR_READING_NETWORK_MESSAGE;
        }
        
        textStream >> currentText;
        
        if (currentText == REPLY_ERROR) {
            RwReturnType errorCode;
            textStream >> errorCode;
            reply = RwCommandReply(errorCode);
            return RW_NO_ERROR;
        } else if (currentText == REPLY_REPLY) {
            textStream >> currentText;
            if (currentText != REPLY_FILES_NUMBER)
            {
                rwError() << "Expecting number of files" << endLine();
                return RW_ERROR_READING_NETWORK_MESSAGE;
            }
            
            int numberOfFiles = -1;
            
            textStream >> numberOfFiles;
            if (numberOfFiles <= 0)
            {
                rwError() << "Did not read the number of files correctly" << endLine();
                return RW_ERROR_READING_NETWORK_MESSAGE;
            } 
            
            for (int i = 0; i < numberOfFiles; ++i)
            {
                textStream >> currentText;
                if (currentText != REPLY_FILENAME)
                {
                    rwError() << "Expecting file name" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                
                QString currentFileName;
                textStream >> currentFileName;
                
                textStream >> currentText;
                if (currentText != REPLY_CONTENT_SIZE)
                {
                    rwError() << "Expecting content size" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                
                int elementSize = -1;
                textStream >> elementSize;
                
                if (elementSize <= 0)
                {
                    rwError() << "Wrong content size" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                
                // unfinished
            }
            
        } else {
            rwError() << "Missing type information for reply" << endLine();
            return RW_ERROR_READING_NETWORK_MESSAGE;
        }
        
        return RW_NO_ERROR;
    }
    
}
