/* 

RwCommandServerLocal.cc: Emulates a local command server

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandServerLocal.h"

#include <QLocalSocket>

#include "RwUtils/RwGlobal/RwDefines.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwDataStructures/RwByteArray.h"
#include "RwWorkerInterface/RwManagement.h"

using namespace RwUtils::RwLog;
using namespace RwDataStructures;

namespace RwNetworking {
    
    RwCommandServerLocal::RwCommandServerLocal(QObject* parent, const QString& serverName) : 
        RwCommandServerBase(parent, serverName)
    {
        m_localServer = new QLocalServer(this);
        m_pendingConnection = false;
    }
    
    RwCommandServerLocal::~RwCommandServerLocal()
    {
        delete m_localServer;
    }
    
    void RwCommandServerLocal::start()
    {
        if ( isRunning() )
        {
            rwError() << "A local server with name " << getServerName() << " has already started" << endLine();
            return;
        }
        
        QLocalServer::removeServer(m_serverName);
        
        if ( !m_localServer->listen(m_serverName) )
        {
            rwError() << "Unable to start server: " << m_localServer->errorString() << endLine();
            return;
        }
        
        init();
    }
    
    void RwCommandServerLocal::stop()
    {
        if (m_localServer != 0)
        {
            m_localServer->close();
        }
    }
    
    bool RwCommandServerLocal::isRunning() const
    {
        if (m_localServer != 0)
        {
            return m_localServer->isListening();
        }
        return false;
    }
    
    void RwCommandServerLocal::processConnection()
    {
        m_pendingConnection = true;
        
        // ESTABLISHING CONNECTION
        m_currentConnection = m_localServer->nextPendingConnection();
        QObject::connect(m_currentConnection, SIGNAL(disconnected()), 
                         m_currentConnection, SLOT(deleteLater()));
        
        // RECEIVING DATA
        QByteArray receivedData = m_currentConnection->readAll(); // This may be dangerous
        const char* rawData  = receivedData.data();
        const int sizeOfData = receivedData.size();
        
        // COPYING DATA
        RwByteArray byteArray;
        byteArray.setRawData(rawData, sizeOfData); // implicit copy. Should it be optimised?
        
        // READING REQUEST
        RwCommandRequest request;
        RwReturnType errorCode = fromRawData(byteArray, request);
        
        RwCommandReply commandReply;
        // CHECKING IF EVERYTHING IS IN ORDER SO FAR
        if ( errorCode != RW_NO_ERROR ) {
            commandReply = RwCommandReply(errorCode);
        } else {
            // EXECUTING THE REQUEST AND READING REPLY
            RwReply reply;
            errorCode = executeRequest(request, reply);
            
            if ( errorCode != RW_NO_ERROR ) {
                commandReply = RwCommandReply(errorCode);
            } else {
                commandReply = RwCommandReply(reply);
            }
        }
        
        RwByteArray responseRawData;
        toRawData(commandReply, responseRawData);
        
        m_currentConnection->write(responseRawData.getRawData(), responseRawData.size());
        
        m_pendingConnection = false;
    }
 
    void RwCommandServerLocal::init()
    {
        QObject::connect(m_localServer, SIGNAL(newConnection()), 
                         this, SLOT(processConnection()));
        QObject::connect(this, SIGNAL(errorAtProcessing(RwReturnType)),
                         this, SLOT(captureError(RwReturnType)));
    }
    
    RwReturnType RwCommandServerLocal::fromRawData(const RwDataStructures::RwByteArray &rawData,
                                                   RwCommandRequest& request) const
    {
        // CONVERTING RAW DATA INTO TEXT STREAM
        QByteArray byteArray(rawData.getRawData(), rawData.size());
        QTextStream textStream(byteArray, QIODevice::ReadOnly);
        
        // READING TEXT
        QString currentText;
        textStream >> currentText;
        
        if (currentText != REQUEST_BEGIN)
        {
            rwError() << "Did not find begin delimiter when reading string" << endLine();
            return RW_ERROR_READING_NETWORK_MESSAGE;
        }
        
        QStringList arguments;
        QString workerName;
        QString orderName;
        int currentArgument   = 0;
        int numberOfArguments = -1;
        
        double versionNumber  = 0.0;
        
        do {
            textStream >> currentText;
            
            if (currentText == REQUEST_RW_VERSION) {
                textStream >> versionNumber;
                if (versionNumber < 0.0)
                {
                    rwError() << "Error when reading version number in request" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                } else if (versionNumber < RW_VERSION)
                {
                    rwWarning() << "Request received was created for an older version of Remote Workers, may not work" << endLine();
                }
            } else if (currentText == REQUEST_WORKER) {
                textStream >> workerName;
            } else if (currentText == REQUEST_ORDER) {
                textStream >> orderName;
            } else if (currentText == REQUEST_ARG_NUMBER) {
                textStream >> numberOfArguments;
                if (numberOfArguments < 0)
                {
                    rwError() << "Error when processing number of arguments in the request" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                arguments.reserve(numberOfArguments);
            } else if (currentText == REQUEST_ARG) {
                int argumentNumber = -1;
                textStream >> argumentNumber;
                if (argumentNumber == -1)
                {
                    rwError() << "Error when reading argument number of current argument in request" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                } else if (argumentNumber != currentArgument) {
                    rwError() << "Arguments in request may be out of order or simply malformed" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                
                currentArgument = currentArgument + 1;
                
                QString tmpArgument;
                textStream >> tmpArgument;
                arguments.push_back(tmpArgument);
            } else if (currentText == REQUEST_END) {
                // DO NOTHING
            } else {
                rwError() << "Request is malformed" << endLine();
                return RW_ERROR_READING_NETWORK_MESSAGE;
            }
            
        } while (currentText != REQUEST_END || textStream.atEnd());
        
        // POST PROCESSING CHECKING
        if (currentText != REQUEST_END)
        {
            rwError() << "End delimiter in request was not found" << endLine();
            return RW_ERROR_READING_NETWORK_MESSAGE;
        }
        
        if (workerName == QString()) {
            rwError() << "Worker name was not read in request" << endLine();
            return RW_ERROR_READING_NETWORK_MESSAGE;
        }
        
        if (orderName == QString()) {
            rwError() << "Order for worker was not read in request" << endLine();
            return RW_ERROR_READING_NETWORK_MESSAGE;
        }
        
        // BUILDING REQUEST
        request.setWorkerName(workerName);
        request.setCommand(RwCommand(orderName, arguments));
        
        return RW_NO_ERROR;
    }
    
    RwReturnType RwCommandServerLocal::executeRequest(const RwCommandRequest &request, 
                                                      RwReply &reply) const
    {
        RwReturnType errorCode = RW_NO_ERROR;
        
        RwWorker worker;
        RwManagement::getInstance()->createWorker(request.getWorkerName(), worker);
        
        errorCode = worker.executeCommand(request.getCommand());
        
        if (errorCode != RW_NO_ERROR)
        {
            rwError() << "The worker " << request.getWorkerName() << " did not execute order " << request.getCommand().getOrder() << " properly" << endLine();
            return errorCode;
        }
        
        errorCode = worker.getReply(reply);
        return errorCode;
    }
    
    RwReturnType RwCommandServerLocal::toRawData(const RwNetworking::RwCommandReply &request, RwDataStructures::RwByteArray &rawData) const
    {
        QString message = request.toString();
        QByteArray byteArray = message.toLocal8Bit();
        const int totalLength = byteArray.length();
        
        rawData.setRawData(byteArray.data(), totalLength);
        return RW_NO_ERROR;
    }
}

