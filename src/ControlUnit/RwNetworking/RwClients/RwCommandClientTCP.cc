/* 

RwCommandClientTCP.cc: Client for RwCommandServerTCP.

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012

*/

#include "RwCommandClientTCP.h"

#include "RwUtils/RwLog/RwCommon.h"

#include "../RwSocket/RwTCPSocket.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {

namespace RwClients {

RwCommandClientTCP::RwCommandClientTCP(QObject* parent, const QString& hostName, quint16 portNumber)
: RwCommandClientBase(parent)
{
	m_hostName = hostName;
	m_port = portNumber;
	m_socket = new RwSocket::RwTCPSocket(this);

	connectSignalAndSlots();
}

RwCommandClientTCP::~RwCommandClientTCP()
{
	m_socket->abort();
	delete m_socket;
}

void RwCommandClientTCP::connectToServer()
{
	m_socket->abort();
	dynamic_cast<RwSocket::RwTCPSocket*>(m_socket)->connectToHost(m_hostName, m_port);
}

void RwCommandClientTCP::disconnectFromServer()
{
	dynamic_cast<RwSocket::RwTCPSocket*>(m_socket)->disconnectFromHost();
}

}

}
