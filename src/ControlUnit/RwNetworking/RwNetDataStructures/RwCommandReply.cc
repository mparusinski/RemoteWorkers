/* 

RwCommandReply.h: Represents a reply from server after a worker executes a command

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#include "RwCommandReply.h"

#include <QPair>
#include <QDataStream>

#include "RwUtils/RwLog/RwCommon.h"

#define REPLY_BEGIN "REPLY_BEGIN"
#define REPLY_TYPE "REPLY_TYPE"
#define REPLY_FILES_NUMBER "REPLY_FILES_NUMBER"
#define REPLY_FILE "REPLY_FILE"
#define REPLY_END "REPLY_END"

using namespace RwUtils::RwLog;

inline QDataStream &operator<<(QDataStream & stream, const QString& string) {
    QByteArray stringArray = string.toLocal8Bit();
    stream << stringArray.data();
    return stream;
}

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        RwCommandReply::RwCommandReply()
        {
            m_isError = true;
            m_errorCode = RW_NO_ERROR;
        }
        
        RwCommandReply::RwCommandReply(const RwReturnType errorCode)
        {
            m_isError = true;
            m_errorCode = errorCode;
        }
        
        RwCommandReply::RwCommandReply(const RwWorkerInterface::RwReply& reply)
        {
            m_isError = false;
            m_reply.copyFrom(reply);
        }
        
        RwCommandReply::~RwCommandReply()
        {
            
        }
        
        void RwCommandReply::setErrorCode(const RwReturnType errorCode)
        {
            m_isError = true;
            m_errorCode = errorCode;
        }
        
        void RwCommandReply::setReply(const RwWorkerInterface::RwReply &reply)
        {
            m_isError = false;
            m_reply.copyFrom(reply);
        }
        
        void RwCommandReply::copyFrom(const RwCommandReply &other)
        {
            if (other.m_isError) {
                m_isError = true;
                m_errorCode = other.m_errorCode;
            } else {
                m_isError = false;
                m_reply.copyFrom(other.m_reply);
            }
        }
        
        bool RwCommandReply::isError() const
        {
            return m_isError;
        }
        
        RwReturnType RwCommandReply::getErrorCode() const
        {
            return m_errorCode;
        }
        
        RwWorkerInterface::RwReply& RwCommandReply::getReply()
        {
            return m_reply;
        }
        
        const RwWorkerInterface::RwReply& RwCommandReply::getReply() const
        {
            return m_reply;
        }
        
        RwReturnType RwCommandReply::fromRawData(const QByteArray &rawData)
        {
            QDataStream dataStream(rawData);
            
            int sizeDummy;
            dataStream >> sizeDummy;
            char * begin = 0;
            dataStream >> begin;
            
            if (QString(begin) != REPLY_BEGIN) {
                rwError() << "Error when reading reply from raw data! Begin delimiter is missing" << endLine();
                return RW_ERROR_READING_NETWORK_MESSAGE;
            }
            delete[] begin;
            
            char * replyType = 0;
            dataStream >> replyType;
            
            if (QString(replyType) != REPLY_TYPE) {
                rwError() << "Error when reading reply from raw data! Expecting reply type information" << endLine();
            }
            delete[] replyType;
            
            qint32 boolType;
            dataStream >> boolType;
            m_isError = static_cast<bool>(boolType);
            
            if (m_isError) {
                dataStream >> m_errorCode;
            } else {
                RwWorkerInterface::RwReply::ByteArrays arrays;
                
                char * fileNumberString = 0;
                dataStream >> fileNumberString;
                
                if (QString(fileNumberString) != REPLY_FILES_NUMBER) {
                    rwError() << "Error when reading reply from raw data! Expecting number of files information" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                delete[] fileNumberString;
                
                int numberOfFiles = -1;
                dataStream >> numberOfFiles;
                
                if (numberOfFiles < 0) {
                    rwError() << "Error when reading reply from raw data! Did not read the number of files properly" << endLine();
                    return RW_ERROR_READING_NETWORK_MESSAGE;
                }
                
                arrays.reserve(numberOfFiles);
                for (int i = 0; i < numberOfFiles; ++i)
                {
                    char * fileString = 0;
                    dataStream >> fileString;
                    
                    if (QString(fileString) != REPLY_FILE) {
                        rwError() << "Error when reading reply from raw data! Expecting information about files" << endLine();
                        return RW_ERROR_READING_NETWORK_MESSAGE;
                    }
                    delete[] fileString;
                    
                    QPair<QString, QByteArray> pair;
                    
                    char * fileName = 0;
                    dataStream >> fileName;
                    
                    pair.first = QString(fileName);
                    delete[] fileName;
                    
                    int fileSize = -1;
                    dataStream >> fileSize;
                    
                    if (fileSize <= 0) {
                        rwError() << "Error when reading reply from raw data! File " << pair.first << " has invalid size" << endLine();
                        return RW_ERROR_READING_NETWORK_MESSAGE;
                    }
                    
                    char * fileRawData = new char[fileSize];
                    dataStream.readRawData(fileRawData, fileSize);
                    pair.second = QByteArray(fileRawData, fileSize);
                    arrays.push_back(pair);
                    
                    delete[] fileRawData;
                }
                
                m_reply.setRawData(arrays);
            }
            
            char * end = 0;
            dataStream >> end;
            
            if (QString(end) != REPLY_END) {
                rwError() << "Error when reading reply from raw data! End delimiter is missing" << endLine();
                return RW_ERROR_READING_NETWORK_MESSAGE;
            }
            delete[] end;
            
            return RW_NO_ERROR;
        }
        
        RwReturnType RwCommandReply::toRawData(QByteArray &rawData) const
        {
            QDataStream dataStream(&rawData, QIODevice::WriteOnly);
            
            int size = -1;
            dataStream << size; // will me modified later
            dataStream << REPLY_BEGIN;
            
            dataStream << REPLY_TYPE;
            dataStream << static_cast<qint32>(m_isError);
            
            if (m_isError) {
                dataStream << m_errorCode;
            } else {
                RwWorkerInterface::RwReply::ByteArrays replies = m_reply.getRawData();
                const int numberOfFiles = replies.length();
                dataStream << REPLY_FILES_NUMBER;
                dataStream << numberOfFiles;
                
                for (int i = 0;i < numberOfFiles; ++i) {
                    const QPair<QString, QByteArray>& element = replies[i];
                    
                    dataStream << REPLY_FILE;
                    dataStream << element.first;
                    
                    const QByteArray& fileRawData = element.second;
                    const int fileDataSize = fileRawData.size();
                    dataStream << fileDataSize;
                    dataStream.writeRawData(fileRawData.data(), fileDataSize);
                }
            }
            
            dataStream << REPLY_END;
            
            size = rawData.size();

            QByteArray tmpArray;
            QDataStream tmpData(&tmpArray, QIODevice::WriteOnly);
            tmpData << size;

            for (int i = 0; i < tmpArray.size(); ++i)
            {
            	rawData[i] = tmpArray[i]; // copying in place
            }

            return RW_NO_ERROR;
        }
        
        bool RwCommandReply::operator==(const RwNetworking::RwNetDataStructures::RwCommandReply &other) const
        {
            if (m_isError && other.m_isError) {
                return m_errorCode == other.m_errorCode;
            } else if (!m_isError && !other.m_isError) {
                return m_reply.getRawData() == other.m_reply.getRawData();
            } else {
                return false;
            }
        }
        
    }
    
}
