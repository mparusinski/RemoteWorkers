/* 

RwSSLSocket.h: Interface class for QT sockets (avoids templating QObjects). Implements a ssl socket

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 28/07/2012.

*/

#ifndef _RWNETWORKING_RWSOCKET_RWSSLSOCKET_H_
#define _RWNETWORKING_RWSOCKET_RWSSLSOCKET_H_

#include "RwAbstractSocket.h"

#include <QByteArray>
#include <QSslSocket>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwSocket {

class RwSSLSocket : public RwAbstractSocket {

	Q_OBJECT

public:
	RwSSLSocket(QObject* parent);

	virtual ~RwSSLSocket();

	virtual qint64 bytesAvailable();

	virtual QByteArray readAll();

	virtual void close();

	virtual void abort();

	virtual qint64 write(QByteArray& data);

	virtual void flush();

	virtual bool waitForBytesWritten();

	void connectToHost(QString& host, int port);

	void disconnectFromHost();

public slots:

	void readReady();

	void socketError(QAbstractSocket::SocketError error);

	void connectedSlot();

	void disconnectedSlot();

private:
	DISALLOW_COPY_AND_ASSIGN(RwSSLSocket);

	QSslSocket* m_sslSocket;


};

}

}

#endif // _RWNETWORKING_RWSOCKET_RWSSLSOCKET_H_
