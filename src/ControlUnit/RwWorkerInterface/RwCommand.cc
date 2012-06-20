/* 

Command.cpp: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "RwCommand.h"

using namespace std;

namespace RwWorkerInterface
{

RwCommand::RwCommand(const QString& commandName, const QStringList& arguments)
{
	m_order = commandName;
	m_arguments = arguments;
}

const QString& RwCommand::getOrder() const
{
	return m_order;
}

const QStringList& RwCommand::getArguments() const
{
	return m_arguments;
}

}
