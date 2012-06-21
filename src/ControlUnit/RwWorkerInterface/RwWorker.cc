/* 

Worker.cpp: Interface to a worker

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
#include "RwUtils/RwLog/RwLogger.h"
#include "RwDataStructures/RwByteStream.h"

using namespace RwDataStructures;
using namespace RwUtils::RwSystem;

namespace RwWorkerInterface
{
    
    RwWorker::RwWorker()
    {
        
    }
    
    RwWorker::RwWorker(const QFileInfo& path)
    {
        m_path = path;
        getOutputPath();
    }
    
    RwReturnType RwWorker::getReply(RwReply& reply) const
    {
        createReply(reply);
        cleanOutput();
        
        if (reply.empty())
            return RW_ERROR_NO_REPLY;
        else 
            return RW_NO_ERROR;
    }
    
    RwWorker::RwWorker(const RwWorker& otherWorker)
    {
        m_path       = otherWorker.m_path;
        m_outputPath = otherWorker.m_outputPath;
    }
    
    RwWorker& RwWorker::operator=(const RwWorker &otherWorker)
    {
        if (this != &otherWorker)
        {
            m_path = otherWorker.m_path;
            m_outputPath = otherWorker.m_outputPath;
        }
        
        return *this;
    }
    
    const QFileInfo& RwWorker::getPath() const
    {
        return m_path;
    }
    
    RwReturnType RwWorker::executeCommand(const RwCommand& command) const
    {
        const QString& order = command.getOrder();
        const QStringList& arguments = command.getArguments();
        
        QFileInfo fullPath = m_path;
        
        QString commandPath = fullPath.filePath();
        commandPath += PATH_SEPERATOR;
        commandPath += order;
        
        if (RwUtils::RwLog::RwLogger::getInstance()->logging())
        {
            QString logMessage = commandPath;
            logMessage += " is been executed";
            RwUtils::RwLog::RwLogger::getInstance()->log(logMessage);
        }
        
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
    
    void RwWorker::createReply(RwReply& reply) const
    {
        typedef RwReply::ByteStreams ByteStreams;
        
        QFileInfoList files;
        
        RwFileManagement::getListOfFilesInDir(m_outputPath, files);
        
        const int numberOfFiles = files.size();
        
        ByteStreams rawData;
        rawData.reserve(numberOfFiles);
        
        for (int i = 0; i < numberOfFiles; ++i)
        {
            const QFileInfo& filePath = files[i];
            QFile dataFile(files[i].filePath());
            
            if ( !dataFile.open(QIODevice::ReadOnly) )
            {
                QString errorMessage = "Failed to open file ";
                errorMessage += filePath.filePath();
                RwUtils::RwLog::RwLogger::getInstance()->error_msg(errorMessage);
            }
            
            qint64 length = dataFile.size();
            QDataStream dataFileIn(&dataFile);
            
            RwByteStream bytes(length);
            
            dataFileIn.readRawData(bytes.getRawData(), length);
            
            dataFile.close();
            
            rawData.push_back(QPair<QString, RwByteStream>(filePath.filePath(), bytes));
        }
        
        reply.setRawData(rawData);
    }
    
    void RwWorker::getOutputPath()
    {
        QString fullPathString = m_path.filePath();
        fullPathString += PATH_SEPERATOR;
        fullPathString += "output";
        fullPathString += PATH_SEPERATOR;
        
        m_outputPath = QFileInfo(fullPathString);
    }
    
    void RwWorker::cleanOutput() const
    {
        QFileInfoList files;
        RwFileManagement::getListOfFilesInDir(m_outputPath, files);
        RwFileManagement::deleteFiles(files);
    }
    
}
