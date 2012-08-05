/* 

RwEventLog.h: Container class for a list of events

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012.

*/

#include "RwEventLog.h"

#include <QtAlgorithms>
#include <QTextStream>

#include "RwUtils/RwGlobal/RwConfiguration.h"
#include "RwUtils/RwLog/RwCommon.h"

#include "RwServerStartedEvent.h"
#include "RwServerStoppedEvent.h"
#include "RwWorkerAddedEvent.h"
#include "RwWorkerRemovedEvent.h"
#include "RwWorkerExecutionEvent.h"

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
        static RwEventLog* instance = 0;
        if (instance == 0)
        {
            instance = new RwEventLog;
        }
        return instance;
    }
    
    RwEventLog::EventListType& RwEventLog::getEventList()
    {
        return m_eventList;
    }
    
    const RwEventLog::EventListType& RwEventLog::getEventList() const
    {
        return m_eventList;
    }
    
    void RwEventLog::addEvent(const RwEvent& event)
    {
        if (m_eventList.empty() || event > m_eventList.last()) // cut through for more performance
        {
            m_eventList.push_back(event);
        }
        else
        {
            EventListType::iterator position = qLowerBound(m_eventList.begin(), m_eventList.end(), event);
            m_eventList.insert(position, event); // ensures the list is always in order
        }
        
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
        EventListType::iterator iter;
        for (iter = m_eventList.begin(); iter != m_eventList.end(); ++iter)
        {
            iter->generateEvent();
        }
    }
    
    void RwEventLog::logRotate(int eventsToKeep)
    {
        const int currentSize   = m_eventList.size();
        const int elemsToDelete = currentSize - eventsToKeep;
        if (elemsToDelete > 0)
        {
            for (int i = 0; i < elemsToDelete; ++i)
            {
                m_eventList.removeFirst();
            }
        }
    }
    
    void RwEventLog::saveLog()
    {
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
        
        QTextStream out(&eventLogFile);
        
        out << m_eventList.length();
        
        EventListType::iterator iter;
        for (iter = m_eventList.begin(); iter != m_eventList.end(); ++iter)
        {
            const QDateTime& eventDate = iter->eventDate();
            const QString& description = iter->description();
            
            out << eventDate.toString() << endLine();
            out << description << endLine();
        }
        
        eventLogFile.flush(); 
        eventLogFile.close();
    }
    
    void RwEventLog::restoreLog()
    {
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
        
        QTextStream in(&eventLogFile);
        
        int length;
        in >> length;
        
        for (int i = 0; i < length; ++i)
        {
            QString eventDateString = in.readLine();
            QString description = in.readLine();
            
            QDateTime eventDate = QDateTime::fromString(eventDateString);
            
            RwEventType::RwEventTypeHandle handleToEvent = RwEventType::create(eventDate, description);
            // This may be not the smartest (fastest) way to add events in this case
            m_eventList.push_back(RwEvent(handleToEvent));
        }
        
        qSort(m_eventList.begin(), m_eventList.end());
        
        eventLogFile.flush();
        eventLogFile.close();
    }
    
}
