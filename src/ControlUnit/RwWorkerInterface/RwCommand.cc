/* 

Command.cpp: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "RwCommand.h"

namespace RwWorkerInterface
{
    
    RwCommand::RwCommand(const string& commandName, const vector<string>& arguments)
    {
        m_order = commandName;
        m_arguments = arguments;
    }
    
    const string& RwCommand::getOrder() const
    {
        return m_order;
    }
    
    const vector<string>& RwCommand::getArguments() const
    {
        return m_arguments;
    }
    
}
