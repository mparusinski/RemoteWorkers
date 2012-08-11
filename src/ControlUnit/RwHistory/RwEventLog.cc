/* 

RwEventLog.h: Container class for a list of events

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwEventLog.h"

#include <QtAlgorithms>
#include <QDataStream>

#include "RwUtils/RwGlobal/RwConfiguration.h"
#include "RwUtils/RwLog/RwCommon.h"

#include "RwServerStartedEvent.h"
#include "RwServerStoppedEvent.h"
#include "RwWorkerAddedEvent.h"
#include "RwWorkerRemovedEvent.h"
#include "RwWorkerExecutionEvent.h"

#define THREAD_LOCK m_mutex.lock()
#define THREAD_UNLOCK m_mutex.unlock()

using namespace RwUtils::RwGlobal;
using namespace RwUtils::RwLog;

namespace RwHistory {
    
    RwEventLog::RwEventLog()
    {
        
    }
    
    RwEventLog::~RwEventLog()
    {
        
    }
    
    RwEventLog* RwEventLog::getInstance()
    {
        static QMutex staticMutex;
        staticMutex.lock();
        static RwEventLog* instance = 0;
        if (instance == 0)
        {
            instance = new RwEventLog;
        }
        staticMutex.unlock();
        return instance;
    }
    
    void RwEventLog::lockEventList() const
    {
        THREAD_LOCK;
    }
    
    void RwEventLog::unlockEventList() const
    {
        THREAD_UNLOCK;
    }
    
    int RwEventLog::getNumOfEvents() const
    {
        return m_eventList.size();
    }
    
    RwEvent& RwEventLog::getEvent(int index)
    {
        return m_eventList[index];
    }
    
    const RwEvent& RwEventLog::getEvent(int index) const
    {
        return m_eventList[index];
    }
    
    RwEventLog::EventListType& RwEventLog::getListOfEvents()
    {
        return m_eventList;
    }
    
    const RwEventLog::EventListType& RwEventLog::getListOfEvents() const
    {
        return m_eventList;
    }
    
    void RwEventLog::addEvent(const RwEvent& event)
    {
        THREAD_LOCK;
        if (m_eventList.empty() || event > m_eventList.last()) // cut through for more performance
        {
            m_eventList.push_back(event);
        }
        else
        {
            EventListType::iterator position = qLowerBound(m_eventList.begin(), m_eventList.end(), event);
            m_eventList.insert(position, event); // ensures the list is always in order
        }
        THREAD_UNLOCK;
        
        emit eventAdded();
    }
    
    void RwEventLog::serverStarted()
    {
        RwEvent event(RwServerStartedEvent::create());
        addEvent(event);
    }
    
    void RwEventLog::serverStopped()
    {
        RwEvent event(RwServerStoppedEvent::create());
        addEvent(event);
    }
    
    void RwEventLog::workerAdded(const RwWorker::RwWorkerPtr& worker)
    {
        RwEvent event(RwWorkerAddedEvent::create(worker));
        addEvent(event);
    }
    
    void RwEventLog::workerRemoved(const RwWorker::RwWorkerPtr& worker)
    {
        RwEvent event(RwWorkerRemovedEvent::create(worker));
        addEvent(event);
    }
    
    void RwEventLog::workerExecutedCommand(const RwWorker::RwWorkerPtr& worker, const RwCommand::RwCommandPtr& command)
    {
        RwEvent event(RwWorkerExecutionEvent::create(worker, command));
        addEvent(event);
    }
    
    void RwEventLog::generateAll()
    {
        THREAD_LOCK;
        EventListType::iterator iter;
        for (iter = m_eventList.begin(); iter != m_eventList.end(); ++iter)
        {
            iter->generateEvent();
        }
        THREAD_UNLOCK;
    }
    
    void RwEventLog::logRotate(int eventsToKeep)
    {
        THREAD_LOCK;
        const int currentSize   = m_eventList.size();
        const int elemsToDelete = currentSize - eventsToKeep;
        if (elemsToDelete > 0)
        {
            for (int i = 0; i < elemsToDelete; ++i)
            {
                m_eventList.removeFirst();
            }
        }
        THREAD_UNLOCK;
    }
    
    void RwEventLog::saveLog()
    {
        THREAD_LOCK;
        QString eventLogPath;
        if ( RwConfiguration::getInstance()->getEventLogPath(eventLogPath) != RW_NO_ERROR )
        {
            return;
        }
        
        // opening file
        QFile eventLogFile(eventLogPath);
        if ( !eventLogFile.open(QIODevice::WriteOnly) )
        {
            rwError() << "Unable to open event log file" << endLine();
            return;
        }
        
        QDataStream out(&eventLogFile);
        
        EventListType::iterator iter;
        for (iter = m_eventList.begin(); iter != m_eventList.end(); ++iter)
        {
            const QDateTime& eventDate = iter->eventDate();
            const QString& description = iter->description();
            
            // rwDebug() << eventDate.toString() << endLine();
            // rwDebug() << description << endLine();
            
            out << eventDate;
            out << description;
        }
        
        eventLogFile.flush(); 
        eventLogFile.close();
        THREAD_UNLOCK;
    }
    
    void RwEventLog::restoreLog()
    {
        THREAD_LOCK;
        QString eventLogPath;
        if ( RwConfiguration::getInstance()->getEventLogPath(eventLogPath) != RW_NO_ERROR )
        {
            return;
        }
        
        // opening file
        QFile eventLogFile(eventLogPath);
        if ( !eventLogFile.open(QIODevice::ReadOnly) )
        {
            rwError() << "Unable to open event log file" << endLine();
            return;
        }
        
        QDataStream in(&eventLogFile);
        
        while ( !eventLogFile.atEnd() )
        {
            QDateTime eventDate;
            QString description;
            
            in >> eventDate >> description;
            // in >> description;
            
            // rwDebug() << eventDate.toString() << endLine();
            // rwDebug() << description << endLine();
            
            RwEventType::RwEventTypeHandle handleToEvent = RwEventType::create(eventDate, description);
            // This may be not the smartest (fastest) way to add events in this case
            m_eventList.push_back(RwEvent(handleToEvent));
        }
        
        qSort(m_eventList.begin(), m_eventList.end());
        
        // eventLogFile.flush();
        eventLogFile.close();
        THREAD_UNLOCK;
    }
    
}
