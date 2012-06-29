/* 

RwCommand.cc: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "RwCommand.h"

namespace RwWorkerInterface
{
    
    RwCommand::RwCommand()
    {
        
    }
    
    RwCommand::RwCommand(const QString& commandName, const QStringList& arguments)
    {
        m_order     = commandName;
        m_arguments = arguments;
    }
    
    const QString& RwCommand::getOrder() const
    {
        return m_order;
    }
    
    void RwCommand::setOrder(const QString &order)
    {
        m_order = order;
    }
    
    const QStringList& RwCommand::getArguments() const
    {
        return m_arguments;
    }
    
    void RwCommand::setArguments(const QStringList &arguments)
    {
        m_arguments = arguments;
    }
    
    void RwCommand::copyFrom(const RwWorkerInterface::RwCommand &other)
    {
        m_order     = other.m_order;
        m_arguments = other.m_arguments;
    }
    
}
