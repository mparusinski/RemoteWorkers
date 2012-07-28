/* 

RwLocalSocket.h: Interface class for QT sockets (avoids templating QObjects). Implements a local socket

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWLOCALSOCKET_H_
#define _RWNETWORKING_RWCLIENTS_RWLOCALSOCKET_H_

#include "RwAbstractSocket.h"

#include <QByteArray>
#include <QLocalSocket>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwSocket {

class RwLocalSocket : public RwAbstractSocket {

	Q_OBJECT

public:
	RwLocalSocket(QObject* parent);

	virtual ~RwLocalSocket();

	virtual qint64 bytesAvailable();

	virtual QByteArray readAll();

	virtual void close();

	virtual void abort();

	virtual qint64 write(QByteArray& data);

	virtual void flush();

	virtual bool waitForBytesWritten();

	void connectToServer(const QString& serverName);

	void disconnectFromServer();

public slots:

	void readReady();

	void socketError(QLocalSocket::LocalSocketError error);

	void connectedSlot();

	void disconnectedSlot();

private:
	DISALLOW_COPY_AND_ASSIGN(RwLocalSocket);

	QLocalSocket* m_localSocket;

};

}

}

#endif // _RWNETWORKING_RWCLIENTS_RWLOCALSOCKET_H_
