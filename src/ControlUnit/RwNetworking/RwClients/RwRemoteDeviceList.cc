/* 

RwClientList.cc: Handles the list of available clients

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#include "RwClientList.h"

namespace RwNetworking {

namespace RwClients {

RwClientList::RwClientList(QObject* parent) : QObject(parent)
{

}

RwClientList::~RwClientList()
{

}

}

}
