/* 

Worker.cpp: Interface to a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "RwWorker.h"

#include <fstream>

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
    
    RwWorker::RwWorker(const string& path)
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
    
    const string& RwWorker::getPath() const
    {
        return m_path;
    }
    
    RwReturnType RwWorker::executeCommand(const RwCommand& command) const
    {
        const string& order = command.getOrder();
        const vector<string>& arguments = command.getArguments();
        
        string fullPath = m_path;
        
        string commandPath = fullPath;
        commandPath += PATH_SEPERATOR;
        commandPath += order;
        
        if (RwUtils::RwLog::RwLogger::getInstance()->logging())
        {
            string logMessage = commandPath;
            logMessage += " is been executed";
            RwUtils::RwLog::RwLogger::getInstance()->log(logMessage);
        }
        
        RwExternalApplication application(commandPath, arguments);
        return application.execute();
    }
    
    string RwWorker::commandToString(const RwCommand& command) const
    {
        string commandName;
        
        commandName += "Command ";
        commandName += m_path;
        commandName += PATH_SEPERATOR;
        commandName += command.getOrder();
        
        return commandName;
    }
    
    void RwWorker::createReply(RwReply& reply) const
    {
        typedef RwReply::ByteStreams ByteStreams;
        
        vector<string> files;
        
        RwFileManagement::getListOfFilesInDir(m_outputPath, files);
        
        const int numberOfFiles = files.size();
        
        ByteStreams rawData;
        rawData.reserve(numberOfFiles);
        
        for (int i = 0; i < numberOfFiles; ++i)
        {
            string filePath = m_outputPath;
            filePath += files[i];
            ifstream dataFile(filePath.c_str(), ifstream::in);
            
            if ( !dataFile.is_open() )
            {
                string errorMessage = "Failed to open file ";
                errorMessage += filePath;
                RwUtils::RwLog::RwLogger::getInstance()->error_msg(errorMessage);
            }
            
            int length;
            RwFileManagement::getSizeOfFile(dataFile, length);
            
            RwByteStream bytes(length);
            dataFile.seekg(ifstream::beg);
            
            dataFile.read(bytes.getRawData(), length);
            dataFile.close();
            
            rawData.push_back(pair<string, RwByteStream>(filePath, bytes));
        }
        
        reply.setRawData(rawData);
    }
    
    void RwWorker::getOutputPath()
    {
        string fullPathString = m_path;
        fullPathString += PATH_SEPERATOR;
        fullPathString += "output";
        fullPathString += PATH_SEPERATOR;
        
        m_outputPath = fullPathString;
    }
    
    void RwWorker::cleanOutput() const
    {
        vector<string> files;
        RwFileManagement::getListOfFilesInDir(m_outputPath, files);
        RwFileManagement::deleteFiles(files);
    }
    
}
