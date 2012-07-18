/* 

RwEventType.h: Capture the type of an event

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/07/2012

*/

#include "RwEventType.h"

namespace RwHistory {

RwEventType::~RwEventType()
{

}

RwEventType::RwEventTypeSubClassType RwEventType::getSubClassType() const
{
	return m_subClassType;
}

RwEventType::RwEventTypeHandle RwEventType::generate()
{
	// RwEventType and its subclass will always be dynamically allocated, so this should work
	return RwEventType::RwEventTypeHandle(this);
}

void RwEventType::copyEssentials(const RwEventType* other)
{
	m_eventDate = other->m_eventDate;
	m_subClassType = other->m_subClassType;
}

}
