/* 

RwEventType.h: Capture the type of an event

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012

*/

#include "RwEventType.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwHistory {
    
    RwEventType::RwEventType()
    {
        m_eventDate = QDateTime::currentDateTimeUtc();
        m_generated = true;
    }
    
    RwEventType::RwEventType(const QDateTime& eventDate, const QString& description)
    {
        m_generated = true;
        m_eventDate = eventDate;
        m_eventDescription = description;
    }
    
    RwEventType::~RwEventType()
    {
        
    }
    
    RwEventType::RwEventTypeHandle RwEventType::create(const QDateTime& eventDate, const QString& description)
    {
        RwEventType* ptrToObject = new RwEventType(eventDate, description);
        RwEventTypeHandle handle(ptrToObject);
        return handle;
    }
    
    RwEventType::RwEventTypeSubClassType RwEventType::getEventType() const
    {
        return m_subClassType;
    }
    
    RwEventType::RwEventTypeHandle RwEventType::generate()
    {
        rwError() << "Can't generate an already generated event" << endLine();
        return RwEventType::RwEventTypeHandle(new RwEventType);
    }
    
    void RwEventType::copyEssentials(const RwEventType* other)
    {
        m_eventDate = other->m_eventDate;
        m_subClassType = other->m_subClassType;
    }
    
    const QString& RwEventType::getEventDescription() const
    {
        return m_eventDescription;
    }
    
    void RwEventType::setEventDescription(QString& eventDescription)
    {
        m_eventDescription = eventDescription;
    }
    
}
