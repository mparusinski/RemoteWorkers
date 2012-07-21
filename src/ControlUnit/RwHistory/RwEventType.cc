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

RwEventType::~RwEventType()
{

}

RwEventType::RwEventTypeSubClassType RwEventType::getSubClassType() const
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

}
