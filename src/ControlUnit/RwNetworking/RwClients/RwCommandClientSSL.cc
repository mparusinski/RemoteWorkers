/* 

RwCommandClientSSL.cc: Client for RwCommandServerSSL.

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012

*/

#include "RwCommandClientSSL.h"

#include "RwUtils/RwLog/RwCommon.h"

#include "../RwSocket/RwSSLSocket.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {

namespace RwClients {

RwCommandClientSSL::RwCommandClientSSL(QObject* parent, const QString& hostName, quint16 portNumber)
: RwCommandClientBase(parent)
{
	rwWarning() << "RwCommandClientSSL not implemented yet" << endLine();
	m_hostName = hostName;
	m_port = portNumber;
	m_socket = new RwSocket::RwSSLSocket(this);

	connectSignalAndSlots();
}

RwCommandClientSSL::~RwCommandClientSSL()
{
	rwWarning() << "RwCommandClientSSL not implemented yet" << endLine();
	m_socket->abort();
	delete m_socket;
}

void RwCommandClientSSL::connectToServer()
{
	rwWarning() << "RwCommandClientSSL not implemented yet" << endLine();
	m_socket->abort();
	dynamic_cast<RwSocket::RwSSLSocket*>(m_socket)->connectToHost(m_hostName, m_port);
}

void RwCommandClientSSL::disconnectFromServer()
{
	rwWarning() << "RwCommandClientSSL not implemented yet" << endLine();
	dynamic_cast<RwSocket::RwSSLSocket*>(m_socket)->disconnectFromHost();
}

}

}
