/* 

RwWorkerList.h: Handles the list of installed workers

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 21/07/2012.

*/

#include "RwWorkerList.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "RwUtils/RwLog/RwCommon.h"

#include "RwUtils/RwGlobal/RwConfiguration.h"

using namespace RwUtils::RwLog;
using namespace RwUtils::RwGlobal;

namespace RwWorkerInterface {
    
    RwWorkerList::RwWorkerList()
    {
        
    }
    
    RwWorkerList::~RwWorkerList()
    {
        
    }
    
    RwWorkerList* RwWorkerList::getInstance()
    {
        static RwWorkerList* instance = 0;
        if (instance == 0)
        {
            instance = new RwWorkerList;
        }
        return instance;
    }
    
    void RwWorkerList::addWorker(const QString& workerName)
    {
        addWorker(workerName, RW_WORKER_NO_TYPE);
    }
    
    void RwWorkerList::addWorker(const QString& workerName, const WorkerType type)
    {
        m_listOfWorkers[workerName] = WorkerDescriptionType(type, QDate::currentDate());
    }
    
    void RwWorkerList::removeWorker(const QString& workerName)
    {
        m_listOfWorkers.remove(workerName);
    }
    
    QList<QString> RwWorkerList::getListOfWorkers()
    {
        return m_listOfWorkers.keys();
    }
    
    const QList<QString> RwWorkerList::getListOfWorkers() const
    {
        return m_listOfWorkers.keys();
    }
    
    RwReturnType RwWorkerList::readWorkers()
    {
        QString workerListPath;
        RwConfiguration::getInstance()->getWorkersListPath(workerListPath);
        QFile workerListFile(workerListPath);
        
        if ( !workerListFile.open(QIODevice::ReadOnly | QIODevice::Text) ){
            rwError() << "Unable to read worker list file" << endLine();
            return RW_ERROR_FILE_NOT_READ;
        }
        
        QTextStream in(&workerListFile);
        
        while ( !in.atEnd())
        {
            QString workerName;
            int type;
            QString dateString;
            QStringList dateTokens;
            
            in >> workerName;
            
            if (workerName[0] == '#')
            {
                in.readLine();
                continue;
            } else if ( workerName.isEmpty() ) {
                break;
            }
            
            in >> type;
            in >> dateString;
            
            dateTokens = dateString.split("/");
            
            int day = dateTokens[0].toInt();
            int month = dateTokens[1].toInt();
            int year = dateTokens[2].toInt();
            
            QDate date(year, month, day);
            
            m_listOfWorkers[workerName] = WorkerDescriptionType(static_cast<WorkerType>(type), date);
        }
        
        workerListFile.close();
        return RW_NO_ERROR;
    }
    
}
