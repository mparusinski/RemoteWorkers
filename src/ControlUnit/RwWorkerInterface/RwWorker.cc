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
    
    RwWorker::RwWorker(const QDir& path)
    {
        m_path = path;
        m_workerName = m_path.dirName();
        m_outputPathComputed = false;
    }
    
    RwReturnType RwWorker::getReply(RwReply::RwReplyPtr& reply)
    {
//        RwReturnType returnMsg = RW_NO_ERROR;
//        returnMsg = returnMsg | createReply(reply);
//        cleanOutput();
//        
//        if (reply->empty())
//            returnMsg = returnMsg | RW_ERROR_NO_REPLY;
//
//        return returnMsg;
        
        return createReply(reply);
    }
    
    const QDir& RwWorker::getPath() const
    {
        return m_path;
    }
    
    const QString& RwWorker::getWorkerName() const
    {
    	return m_workerName;
    }
    
    RwReturnType RwWorker::executeCommand(const RwCommand::RwCommandPtr& command)
    {        
        const QString& order = command->getOrder();
        const QStringList& arguments = command->getArguments();
        
        QFileInfo commandPath = m_path.filePath(order);

        RwExternalApplication application(commandPath, arguments);
        return application.execute(m_outputData);
    }
    
    QString RwWorker::commandToString(const RwCommand& command) const
    {
        return "Command " + m_path.filePath(command.getOrder());
    }
    
    RwReturnType RwWorker::createReply(RwReply::RwReplyPtr& reply)
    {
//        typedef RwReply::ByteArrays ByteArrays;
//        
//        QFileInfoList files;
//        
//        if (!m_outputPathComputed)
//            getOutputPath();
//        
//        RwFileManagement::getListOfFilesInDir(m_outputPath, files);
//        
//        const int numberOfFiles = files.size();
//        
//        reply = RwReply::RwReplyPtr(new RwReply);
//        ByteArrays& rawData = reply->getRawData();
//        rawData.reserve(numberOfFiles);
//        
//        QFileInfoList::const_iterator iter;
//        for (iter = files.begin(); iter != files.end(); ++iter)
//        {
//            const QString& filePath = iter->filePath();
//            QFile dataFile(filePath);
//            
//            if ( !dataFile.open(QIODevice::ReadOnly) )
//            {
//                rwError() << "Failed to open file " << filePath << endLine();                
//                return RW_ERROR_FILE_NOT_READ;
//            }
//            
//            rawData << QPair<QString, QByteArray>(iter->fileName(), dataFile.readAll());
//            
//            dataFile.close();
//        }
//        
//        return RW_NO_ERROR;
        
        typedef RwReply::ByteArrays ByteArrays;
        ByteArrays array;
        
        QDataStream streamIn(&m_outputData, QIODevice::ReadOnly);
        
        streamIn >> array;
        reply = RwReply::RwReplyPtr(new RwReply(array));
        
        return RW_NO_ERROR;
    }
    
    void RwWorker::getOutputPath()
    {
        m_outputPath = m_path;
        m_outputPath.cd("output");
        
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
