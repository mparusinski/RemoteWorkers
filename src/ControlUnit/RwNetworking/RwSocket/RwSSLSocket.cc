/* 

RwSSLSocket.h: Interface class for QT sockets (avoids templating QObjects). Implements a ssl socket

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 28/07/2012

*/

#include "RwSSLSocket.h"

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwNetworking {

namespace RwSocket {

RwSSLSocket::RwSSLSocket(QObject * parent) : RwAbstractSocket(parent)
{
	m_sslSocket = new QSslSocket(this);
	init();
}

RwSSLSocket::RwSSLSocket(QSslSocket* socket) : RwAbstractSocket(socket->parent())
{
	m_sslSocket = socket; // takes ownership
	init();
}

RwSSLSocket::~RwSSLSocket()
{
	m_sslSocket->abort();
	delete m_sslSocket;
}

void RwSSLSocket::init()
{
	connect(m_sslSocket, SIGNAL(readyRead()),
			this, SLOT(readReady()));
	connect(m_sslSocket, SIGNAL(connected()),
			this, SLOT(connectedSlot()));
	connect(m_sslSocket, SIGNAL(disconnected()),
			this, SLOT(disconnectedSlot()));
	connect(m_sslSocket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(socketError(QAbstractSocket::SocketError)));
}

qint64 RwSSLSocket::bytesAvailable()
{
	return m_sslSocket->bytesAvailable();
}

QByteArray RwSSLSocket::readAll()
{
	return m_sslSocket->readAll();
}

void RwSSLSocket::close()
{
	m_sslSocket->close();
}

qint64 RwSSLSocket::write(QByteArray& data)
{
	return m_sslSocket->write(data);
}

void RwSSLSocket::abort()
{
	m_sslSocket->abort();
}

void RwSSLSocket::flush()
{
	m_sslSocket->flush();
}

bool RwSSLSocket::waitForBytesWritten()
{
	return m_sslSocket->waitForBytesWritten();
}

bool RwSSLSocket::waitForReadyRead()
{
	return m_sslSocket->waitForReadyRead();
}

void RwSSLSocket::readReady()
{
	emit dataReady();
}

void RwSSLSocket::connectToHost(QString& host, int port)
{
	m_sslSocket->connectToHost(host, port);
}

void RwSSLSocket::disconnectFromHost()
{
	m_sslSocket->disconnectFromHost();
}

void RwSSLSocket::socketError(QAbstractSocket::SocketError errorValue)
{
	rwError() << "Socket error: " << m_sslSocket->errorString() << endLine();
	emit error();
}

void RwSSLSocket::connectedSlot()
{
	emit connected();
}

void RwSSLSocket::disconnectedSlot()
{
	emit disconnected();
}

}

}
