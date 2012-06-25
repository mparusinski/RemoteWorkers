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

#define REQUEST_BEGIN "REQUEST_START"
#define REQUEST_END   "REQUEST_END"
#define REQUEST_RW_VERSION "REQUEST_RW_VERSION"
#define REQUEST_WORKER  "REQUEST_WORKER"
#define REQUEST_ORDER   "REQUEST_ORDER"
#define REQUEST_ARG_NUMBER "REQUEST_ARG_NUMBER"

using namespace RwUtils::RwLog;

inline QDataStream &operator<<(QDataStream & stream, const QString& string) {
    QByteArray stringArray = string.toLocal8Bit();
    stream << stringArray.data();
    return stream;
}

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
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
        
        RwReturnType RwCommandRequest::toRawData(QByteArray& rawData) const
        {
            QDataStream dataStream(&rawData, QIODevice::WriteOnly);
            dataStream.setVersion(QDataStream::Qt_4_8);
            
            dataStream << REQUEST_BEGIN;
            
            dataStream << REQUEST_RW_VERSION;
            dataStream << RW_VERSION;
            
            dataStream << REQUEST_WORKER;
            dataStream << m_workerName;
            
            dataStream << REQUEST_ORDER;
            dataStream << m_command.getOrder();
            
            const QStringList& args = m_command.getArguments();
            const int numberOfArguments = args.size();
            
            dataStream << REQUEST_ARG_NUMBER;
            dataStream << numberOfArguments;
            //        rwDebug() << qRawData << endLine();
            
            for (int i = 0; i < numberOfArguments; ++i)
            {
                dataStream << i;
                dataStream << args[i];
            }
            
            dataStream << REQUEST_END;
            
            return RW_NO_ERROR;
        }
        
        RwReturnType RwCommandRequest::fromRawData(const QByteArray &rawData)
        {
            // CONVERTING RAW DATA INTO TEXT STREAM
            QDataStream dataStream(rawData);
            
            char* beginRequest = 0;
            dataStream >> beginRequest;
            if (QString(beginRequest) != REQUEST_BEGIN)
            {
                rwError() << "Request does not have a begin delimiter" << endLine();
                return RW_ERROR_READING_NETWORK_MESSAGE;
            }
            delete[] beginRequest;
            
            QString order;
            QStringList argumentsList;
            
            bool readWorkerName = false;
            bool readOrder      = false;
            bool readArguments  = false;
            
            while (!dataStream.atEnd()) {
                char * nextText = 0;
                dataStream >> nextText;
                
                QString qString(nextText);
                if (qString == REQUEST_RW_VERSION) {
                    double rwVersion = 0.0;
                    dataStream >> rwVersion;
                    
                    if (rwVersion <= 0) {
                        rwError() << "Error when reading remote workers version number" << endLine();
                        return RW_ERROR_READING_NETWORK_MESSAGE;
                    } else if (rwVersion < RW_VERSION) {
                        rwWarning() << "Request was created for an older version of Remote Workers, may not work" << endLine();
                    }
                } else if (qString == REQUEST_WORKER) {
                    char * workerNameCString = 0;
                    dataStream >> workerNameCString;
                    
                    m_workerName = QString(workerNameCString);
                    readWorkerName = true;
                    
                    delete[] workerNameCString;
                } else if (qString == REQUEST_ORDER) {
                    char * orderNameCString = 0;
                    dataStream >> orderNameCString;
                    
                    order = QString(orderNameCString);
                    readOrder = true;
                    
                    delete[] orderNameCString;
                } else if (qString == REQUEST_ARG_NUMBER) {
                    int numberOfArguments = -1;
                    dataStream >> numberOfArguments;
                    
                    if (numberOfArguments < 0) {
                        rwError() << "Error when reading number of arguments" << endLine();
                        return RW_ERROR_READING_NETWORK_MESSAGE;
                    }
                    
                    argumentsList.reserve(numberOfArguments);
                    
                    for (int i = 0; i < numberOfArguments; ++i)
                    {
                        int currentIndex = -1;
                        dataStream >> currentIndex;
                        
                        if (currentIndex < 0) {
                            rwError() << "Error when reading argument index" << endLine();
                            return RW_ERROR_READING_NETWORK_MESSAGE;
                        } else if (currentIndex != i) {
                            rwError() << "Arguments out of order or arguments skipped" << endLine();
                            return RW_ERROR_READING_NETWORK_MESSAGE;
                        }
                        
                        char * currentArgumentCString = 0;
                        dataStream >> currentArgumentCString;
                        
                        QString currentArgument(currentArgumentCString);
                        argumentsList.push_back(currentArgument);
                    }
                    
                    readArguments = true;
                } else if (qString == REQUEST_END) {
                    break;
                } else {
                    rwError() << "Unexpected symbol in request " << qString << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                
                delete[] nextText;
            }
            
            if (!readWorkerName || !readOrder || !readArguments) {
                rwError() << "Request does not define all components" << endLine();
                return RW_ERROR_READING_NETWORK_MESSAGE;
            }
            
            m_command = RwCommand(order, argumentsList);
            return RW_NO_ERROR;
        }
        
        bool RwCommandRequest::operator==(const RwNetworking::RwNetDataStructures::RwCommandRequest &other) const
        {
            return (m_workerName == other.m_workerName) && (m_command.getOrder() == other.m_command.getOrder()) && (m_command.getArguments() == other.m_command.getArguments());
        }
        
    }
    
}
