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

#define BEGIN "BEGIN"
#define END   "END"
#define VERSION "RW_VERSION"
#define WORKER  "WORKER"
#define ORDER   "ORDER"
#define ARG_NUMBER "ARG_NUMBER"
#define ARG "ARG"
#define DEFINE " "
#define NEW_SECTION "\n";

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
    
    RwReturnType RwCommandRequest::toRawData(RwDataStructures::RwByteArray& rawData) const
    {
        // Packing the message together
        QString order    = m_command.getOrder();
        QStringList args = m_command.getArguments();
        
        QString message;
        
        message += BEGIN;
        message += NEW_SECTION;
        
        message += VERSION;
        message += DEFINE;
        message += QString::number(RW_VERSION);
        message += NEW_SECTION;
        
        message += WORKER;
        message += DEFINE;
        message += m_workerName;
        message += NEW_SECTION;
        
        message += ORDER;
        message += DEFINE;
        message += order;
        message += NEW_SECTION;
        
        const int numberOfArguments = args.length();
        
        message += ARG_NUMBER;
        message += DEFINE;
        message += QString::number(numberOfArguments);
        message += NEW_SECTION;
        
        for (int i = 0; i < numberOfArguments; ++i)
        {
            message += ARG;
            message += DEFINE;
            message += QString::number(i);
            message += DEFINE;
            message += args[i];
            message += NEW_SECTION;
        }

        message += END;
        message += NEW_SECTION;
        
        // rwMessage() << message << endLine();
        
        // Turn it raw
        QByteArray byteArray = message.toLocal8Bit();
        const int totalLength = byteArray.length();
        rawData.setRawData(byteArray.data(), totalLength);
        
        return RW_NO_ERROR;
    }
    
    RwReturnType RwCommandRequest::fromRawData(const RwDataStructures::RwByteArray &rawData)
    {
        // CONVERTING RAW DATA INTO TEXT STREAM
        QByteArray byteArray(rawData.getRawData(), rawData.size());
        QTextStream textStream(byteArray, QIODevice::ReadOnly);
        
        // READING TEXT
        QString currentText;
        textStream >> currentText;
        
        if (currentText != BEGIN)
        {
            rwError() << "Did not find begin delimiter when reading string" << endLine();
            return RW_ERROR_READING_REQUEST;
        }
        
        QStringList arguments;
        QString workerName;
        QString orderName;
        int currentArgument   = 0;
        int numberOfArguments = -1;
        
        double versionNumber  = 0.0;
        
        do {
            textStream >> currentText;
            
            if (currentText == VERSION) {
                textStream >> versionNumber;
                if (versionNumber < 0.0)
                {
                    rwError() << "Error when reading version number in request" << endLine();
                    return RW_ERROR_READING_REQUEST;
                } else if (versionNumber < RW_VERSION)
                {
                    rwWarning() << "Request received was created for an older version of Remote Workers, may not work" << endLine();
                }
            } else if (currentText == WORKER) {
                textStream >> workerName;
            } else if (currentText == ORDER) {
                textStream >> orderName;
            } else if (currentText == ARG_NUMBER) {
                textStream >> numberOfArguments;
                if (numberOfArguments < 0)
                {
                    rwError() << "Error when processing number of arguments in the request" << endLine();
                    return RW_ERROR_READING_REQUEST;
                }
                arguments.reserve(numberOfArguments);
            } else if (currentText == ARG) {
                int argumentNumber = -1;
                textStream >> argumentNumber;
                if (argumentNumber == -1)
                {
                    rwError() << "Error when reading argument number of current argument in request" << endLine();
                    return RW_ERROR_READING_REQUEST;
                } else if (argumentNumber != currentArgument) {
                    rwError() << "Arguments in request may be out of order or simply malformed" << endLine();
                    return RW_ERROR_READING_REQUEST;
                }
                
                currentArgument = currentArgument + 1;
                
                QString tmpArgument;
                textStream >> tmpArgument;
                arguments.push_back(tmpArgument);
            } else if (currentText == END) {
                // DO NOTHING
            } else {
                rwError() << "Request is malformed" << endLine();
                return RW_ERROR_READING_REQUEST;
            }
            
        } while (currentText != END || textStream.atEnd());
        
        // POST PROCESSING CHECKING
        if (currentText != END)
        {
            rwError() << "End delimiter in request was not found" << endLine();
            return RW_ERROR_READING_REQUEST;
        }
        
        if (workerName == QString()) {
            rwError() << "Worker name was not read in request" << endLine();
            return RW_ERROR_READING_REQUEST;
        }
        
        if (orderName == QString()) {
            rwError() << "Order for worker was not read in request" << endLine();
            return RW_ERROR_READING_REQUEST;
        }
        
        // BUILDING REQUEST
        m_workerName = workerName;
        m_command = RwCommand(orderName, arguments);
        
        return RW_NO_ERROR;
    }
    
    QString RwCommandRequest::getWorkerName() const {
        return m_workerName;
    }
    
    RwCommand RwCommandRequest::getCommand() const {
        return m_command;
    }
    
}
