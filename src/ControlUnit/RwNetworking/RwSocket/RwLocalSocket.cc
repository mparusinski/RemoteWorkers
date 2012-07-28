/* 

RwLocalSocket.cc: Interface class for QT sockets (avoids templating QObjects). Implements a local socket

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#include "RwLocalSocket.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {

namespace RwSocket {

RwLocalSocket::RwLocalSocket(QObject* parent) : RwAbstractSocket(parent)
{
	m_localSocket = new QLocalSocket(this);
	connect(m_localSocket, SIGNAL(readyRead()),
	        this, SLOT(readReady()));
	connect(m_localSocket, SIGNAL(connected()),
			this, SLOT(connectedSlot()));
	connect(m_localSocket, SIGNAL(disconnected()),
			this, SLOT(disconnectedSlot()));
	connect(m_localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)),
	        this, SLOT(socketError(QLocalSocket::LocalSocketError)));
}

RwLocalSocket::~RwLocalSocket()
{
	m_localSocket->abort();
	delete m_localSocket;
}

qint64 RwLocalSocket::bytesAvailable()
{
	return m_localSocket->bytesAvailable();
}

QByteArray RwLocalSocket::readAll()
{
	return m_localSocket->readAll();
}

void RwLocalSocket::abort()
{
	m_localSocket->abort();
}

void RwLocalSocket::close()
{
	m_localSocket->close();
}

qint64 RwLocalSocket::write(QByteArray& data)
{
	return m_localSocket->write(data);
}

void RwLocalSocket::flush()
{
	m_localSocket->flush();
}

bool RwLocalSocket::waitForBytesWritten()
{
	return m_localSocket->waitForBytesWritten();
}

void RwLocalSocket::readReady()
{
	emit dataReady();
}

void RwLocalSocket::socketError(QLocalSocket::LocalSocketError errorValue)
{
	rwError() << "Local socket error: " << m_localSocket->errorString() << endLine();
	emit error();
}

void RwLocalSocket::connectToServer(const QString& serverName)
{
	m_localSocket->connectToServer(serverName);
}

void RwLocalSocket::disconnectFromServer()
{
	m_localSocket->disconnectFromServer();
}

void RwLocalSocket::connectedSlot()
{
	emit connected();
}

void RwLocalSocket::disconnectedSlot()
{
	emit disconnected();
}

}

}
