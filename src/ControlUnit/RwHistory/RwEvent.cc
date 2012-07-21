/* 

RwEvent.h: Class capturing a server event. Will be used for logging activity

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/08/2012.

*/

#include "RwEvent.h"

namespace RwHistory {

RwEvent::RwEvent(const RwEventType::RwEventTypeHandle& handleToEvent)
{
	m_eventTypeVar = handleToEvent;
}

RwEvent::~RwEvent()
{

}

bool RwEvent::operator <(const RwEvent& other) const
{
	return (m_eventTypeVar->date()) < (other.m_eventTypeVar->date());
}

bool RwEvent::operator >(const RwEvent& other) const
{
	return (m_eventTypeVar->date()) > (other.m_eventTypeVar->date());
}

const QDate& RwEvent::eventDate() const
{
	return m_eventTypeVar->date();
}

QDate& RwEvent::eventDate()
{
	return m_eventTypeVar->date();
}

void RwEvent::generateEvent()
{
	if ( !m_eventTypeVar->hasBeenGenerated() )
		m_eventTypeVar = m_eventTypeVar->generate();
}

const QString& RwEvent::description()
{
	generateEvent();
	return m_eventTypeVar->getEventDescription();
}

}
