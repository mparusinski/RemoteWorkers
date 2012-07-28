/* 

RwTCPSocket.h: Interface class for QT sockets (avoids templating QObjects). Implements a TCP socket

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 28/07/2012.

*/

#ifndef _RWNETWORKING_RWSOCKET_RWTCPSOCKET_H_
#define _RWNETWORKING_RWSOCKET_RWTCPSOCKET_H_

#include "RwAbstractSocket.h"

#include <QByteArray>
#include <QTcpSocket>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwSocket {

class RwTCPSocket : public RwAbstractSocket {

	Q_OBJECT

public :
	RwTCPSocket(QObject* parent);

	RwTCPSocket(QTcpSocket* socket);

	virtual ~RwTCPSocket();

	virtual qint64 bytesAvailable();

	virtual QByteArray readAll();

	virtual void abort();

	virtual void close();

	virtual qint64 write(QByteArray& data);

	virtual void flush();

	virtual bool waitForBytesWritten();

	virtual bool waitForReadyRead();

	void connectToHost(QString& hostName, int port);

	void disconnectFromHost();

public slots:

	void readReady();

	void socketError(QAbstractSocket::SocketError error);

	void connectedSlot();

	void disconnectedSlot();

private:
	DISALLOW_COPY_AND_ASSIGN(RwTCPSocket);

	void init();

	QTcpSocket* m_tcpSocket;

};

}

}

#endif // _RWNETWORKING_RWSOCKET_RWTCPSOCKET_H_
