/* 

RwAbstractSocket.cc: Interface class for QT sockets (avoids templating QObjects)

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012

*/

#include "RwAbstractSocket.h"

namespace RwNetworking {

namespace RwSocket {

RwAbstractSocket::RwAbstractSocket(QObject* parent) : QObject(parent)
{
}

RwAbstractSocket::~RwAbstractSocket()
{
}

}

}
