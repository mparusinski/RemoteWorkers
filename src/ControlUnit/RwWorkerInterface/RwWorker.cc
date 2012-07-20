/* 

RwWorker.ccs: Interface to a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "RwWorker.h"

#include <QFile>
#include <QDataStream>

#include "RwReply.h"
#include "RwUtils/RwSystem/RwFileManagement.h"
#include "RwUtils/RwSystem/RwExternalApplication.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwGlobal/RwReturn.h"

using namespace RwUtils::RwSystem;
using namespace RwUtils::RwLog;
using namespace RwUtils::RwGlobal;

namespace RwWorkerInterface
{
    
    RwWorker::RwWorker()
    {
        m_outputPathComputed = false; 
    }
    
    RwWorker::RwWorker(const QFileInfo& path)
    {
        m_path = path;
        m_workerName = m_path.fileName();
        m_outputPathComputed = false;
    }
    
    RwReturnType RwWorker::getReply(RwReply::RwReplyPtr& reply)
    {
        RwReturnType returnMsg = RW_NO_ERROR;
        returnMsg = returnMsg | createReply(reply);
        cleanOutput();
        
        if (reply->empty())
            returnMsg = returnMsg | RW_ERROR_NO_REPLY;

        return returnMsg;
    }
    
    const QFileInfo& RwWorker::getPath() const
    {
        return m_path;
    }
    
    const QString& RwWorker::getWorkerName() const
    {
    	return m_workerName;
    }
    
    RwReturnType RwWorker::executeCommand(const RwCommand::RwCommandPtr& command) const
    {
        const QString& order = command->getOrder();
        const QStringList& arguments = command->getArguments();
        
        QFileInfo fullPath = m_path;
        
        QString commandPath = fullPath.filePath();
        commandPath += PATH_SEPERATOR;
        commandPath += order;

        rwMessage() << commandPath << " has been executed" << endLine();

        RwExternalApplication application(commandPath, arguments);
        return application.execute();
    }
    
    QString RwWorker::commandToString(const RwCommand& command) const
    {
        QString commandName;
        
        commandName += "Command ";
        commandName += m_path.filePath();
        commandName += PATH_SEPERATOR;
        commandName += command.getOrder();
        
        return commandName;
    }
    
    RwReturnType RwWorker::createReply(RwReply::RwReplyPtr& reply)
    {
        typedef RwReply::ByteArrays ByteArrays;
        
        QFileInfoList files;
        
        if (!m_outputPathComputed)
            getOutputPath();
        
        RwFileManagement::getListOfFilesInDir(m_outputPath, files);
        
        const int numberOfFiles = files.size();
        
        reply = RwReply::RwReplyPtr(new RwReply);
        ByteArrays& rawData = reply->getRawData();
        rawData.reserve(numberOfFiles);
        
        for (int i = 0; i < numberOfFiles; ++i)
        {
            const QFileInfo& filePath = files[i];
            QFile dataFile(files[i].filePath());
            
            if ( !dataFile.open(QIODevice::ReadOnly) )
            {
                rwError() << "Failed to open file " << filePath.filePath() << endLine();                
                return RW_ERROR_FILE_NOT_READ;
            }
            
            qint64 length = dataFile.size();
            QDataStream dataFileIn(&dataFile);
            
            char * bytes = new char[length];
            dataFileIn.readRawData(bytes, length);
            
            
            rawData.append(QPair<QString, QByteArray>(filePath.fileName(), QByteArray(bytes, length)));
            delete[] bytes;
            
            dataFile.close();
        }
        
        return RW_NO_ERROR;
    }
    
    void RwWorker::getOutputPath()
    {
        QString fullPathString = m_path.filePath();
        fullPathString += PATH_SEPERATOR;
        fullPathString += "output";
        fullPathString += PATH_SEPERATOR;
        
        m_outputPath = QFileInfo(fullPathString);
        m_outputPathComputed = true;
    }
    
    void RwWorker::cleanOutput()
    {
        QFileInfoList files;
        
        if (!m_outputPathComputed)
            getOutputPath();
        
        RwFileManagement::getListOfFilesInDir(m_outputPath, files);
        RwFileManagement::deleteFiles(files);
    }
    
}
