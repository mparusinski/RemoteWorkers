/* 
 
 Return.cpp: Return error message
 
 As part of the RemoteWorkers program which creates a framework for remote
 management of laptops, desktop and servers. 
 
 Copyright (C) 2012 Remote Workers Project. All rights reserved.
 Created by Michal Parusinski <mparusinski@googlemail.com> on 15/06/2012.
 
 */

#include "RwReturn.h"

#include <QObject>
#include <QString>

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwUtils {
    
    namespace RwGlobal {
        
        QString retTypeToStr(const RwReturnType returnMsg)
        {
            QString msgStr;
            switch (returnMsg)
            {
                case RW_NO_ERROR:
                    rwWarning() << "Message represents no error, this function should not have been called" << endLine();
                    msgStr = QObject::tr("No error\n");
                    break;
                case RW_ERROR_GENERIC:
                    msgStr += QObject::tr("Unknown error\n");
                case RW_ERROR_NO_WORKER:
                    msgStr += QObject::tr("Worker not found\n");
                case RW_ERROR_NO_REPLY:
                    msgStr += QObject::tr("Reply not produced\n");
                case RW_ERROR_NO_EXECUTION:
                    msgStr += QObject::tr("Command did not execute\n");
                case RW_ERROR_EXECUTION_FAIL:
                    msgStr += QObject::tr("Command did not succeed. Execution failed\n");
                case RW_ERROR_FILE_OR_DIR_NOT_FOUND:
                    msgStr += QObject::tr("File or directory was not found\n");
                case RW_ERROR_FILE_NOT_READ:
                    msgStr += QObject::tr("File not read\n");
                case RW_ERROR_SERVER_NOT_STARTED:
                    msgStr += QObject::tr("Server is not running\n");
                case RW_ERROR_SERVER_ALREADY_STARTED:
                    msgStr += QObject::tr("Server already started\n");
                case RW_ERROR_READING_NETWORK_MESSAGE:
                    msgStr += QObject::tr("Problem when reading data from network\n");
                case RW_ERROR_NO_CONNECTION:
                    msgStr += QObject::tr("Connection not established\n");
                default:
                    // should not happen
                    rwError() << "retTypeToStr() did something unexpected" << endLine();
            }
            
            return msgStr;
        }
        
    }
    
}

