/* 

RwTCPSocket.cc: Interface class for QT sockets (avoids templating QObjects). Implements a TCP socket

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 28/07/2012.

*/

#include "RwTCPSocket.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {

namespace RwSocket {

RwTCPSocket::RwTCPSocket(QObject* parent) : RwAbstractSocket(parent)
{
	m_tcpSocket = new QTcpSocket(this);
	init();
}

RwTCPSocket::RwTCPSocket(QTcpSocket* socket) : RwAbstractSocket(socket->parent())
{
	m_tcpSocket = socket; // takes ownership
	init();
}

RwTCPSocket::~RwTCPSocket()
{
	m_tcpSocket->abort();
	delete m_tcpSocket;
}

void RwTCPSocket::init()
{
	connect(m_tcpSocket, SIGNAL(readyRead()),
			this, SLOT(readReady()));
	connect(m_tcpSocket, SIGNAL(connected()),
			this, SLOT(connectedSlot()));
	connect(m_tcpSocket, SIGNAL(disconnected()),
			this, SLOT(disconnectedSlot()));
	connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(socketError(QAbstractSocket::SocketError)));
}

qint64 RwTCPSocket::bytesAvailable()
{
	return m_tcpSocket->bytesAvailable();
}

QByteArray RwTCPSocket::readAll()
{
	return m_tcpSocket->readAll();
}

void RwTCPSocket::close()
{
	return m_tcpSocket->close();
}

void RwTCPSocket::abort()
{
	m_tcpSocket->abort();
}

qint64 RwTCPSocket::write(QByteArray& data)
{
	return m_tcpSocket->write(data);
}

void RwTCPSocket::flush()
{
	m_tcpSocket->flush();
}

bool RwTCPSocket::waitForBytesWritten()
{
	return m_tcpSocket->waitForBytesWritten();
}

bool RwTCPSocket::waitForReadyRead()
{
	return m_tcpSocket->waitForReadyRead();
}

void RwTCPSocket::readReady()
{
	emit dataReady();
}

void RwTCPSocket::socketError(QAbstractSocket::SocketError errorValue)
{
	rwError() << "Socket error: " << m_tcpSocket->errorString() << endLine();
	emit error();
}

void RwTCPSocket::connectToHost(QString& hostname, int port)
{
	m_tcpSocket->connectToHost(hostname, port);
}

void RwTCPSocket::disconnectFromHost()
{
	m_tcpSocket->disconnectFromHost();
}

void RwTCPSocket::connectedSlot()
{
	emit connected();
}

void RwTCPSocket::disconnectedSlot()
{
	emit disconnected();
}

}

}
