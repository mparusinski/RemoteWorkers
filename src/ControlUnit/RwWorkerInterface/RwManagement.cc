/* 

RwManagement.cc: Manages workers

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012

*/

#include "RwManagement.h"

#include <cstdio>

#include "RwConfiguration.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwSystem/RwFileManagement.h"

using namespace RwUtils::RwSystem;
using namespace RwUtils::RwLog;

namespace RwWorkerInterface
{
    
    RwManagement::RwManagement()
    {
    }
    
    RwManagement::~RwManagement()
    {
        
    }
    
    RwManagement* RwManagement::getInstance()
    {
        static RwManagement* instance = 0;
        if (instance == 0)
        {
            instance = new RwManagement();
        }
        return instance;
    }
    
    RwReturnType RwManagement::createWorker(const QString& workerName, RwWorker& worker)
    {
        getListOfWorkers();
        const int numberOfWorkers = m_availableWorkers.size();
        for (int i = 0; i < numberOfWorkers; ++i)
        {
            const QString& currentWorkerName = m_availableWorkers[i].fileName();;
            if (currentWorkerName == workerName)
            {
                QString fullPath = m_pathToWorkers.filePath();
                fullPath += currentWorkerName;
                worker = RwWorker(QFileInfo(fullPath));
                return RW_NO_ERROR;
            }
        }
        
        rwError() << "Worker is not available" << endLine();        
        return RW_ERROR_NO_WORKER;
    }
    
    const QFileInfoList& RwManagement::listAvailableWorkers()
    {
        getListOfWorkers();
        return m_availableWorkers;
    }
    
    RwReturnType RwManagement::getListOfWorkers()
    {
        RwReturnType returnMsg = RW_NO_ERROR;
        if (m_availableWorkers.empty())
        {
            returnMsg = init();
            returnMsg = returnMsg | 
                RwFileManagement::getListOfDirsInDir(m_pathToWorkers, m_availableWorkers);
        }
        return returnMsg;
    }
    
    RwReturnType RwManagement::init()
    {
        RwReturnType returnMsg = RW_NO_ERROR;
        
        QString pathToWorkersStr;
        returnMsg = RwConfiguration::getInstance()->getWorkersPath(pathToWorkersStr);
        m_pathToWorkers = QFileInfo(pathToWorkersStr);
        
        if (m_pathToWorkers == QFileInfo())
        {
            rwError() << "Path to workers not read! File closing" << endLine();
        }
        return RW_NO_ERROR;
    }
    
}
