/* 

RwAbstractSocket.h: Interface class for QT sockets (avoids templating QObjects)

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#ifndef _RWNETWORKING_RWSOCKET_RWABSTRACTSOCKET_
#define _RWNETWORKING_RWSOCKET_RWABSTRACTSOCKET_

#include <QObject>
#include <QByteArray>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwSocket {

class RwAbstractSocket : public QObject {

	Q_OBJECT

public:
	RwAbstractSocket(QObject* parent);

	virtual ~RwAbstractSocket();

	virtual qint64 bytesAvailable() = 0;

	virtual QByteArray readAll() = 0;

	virtual void abort() = 0;

	virtual void close() = 0;

	virtual qint64 write(QByteArray& data) = 0;

	virtual void flush() = 0;

	virtual bool waitForBytesWritten() = 0;

	virtual bool waitForReadyRead() = 0;

signals:
	void dataReady();

	void error();

	void connected();

	void disconnected();

private:
	DISALLOW_COPY_AND_ASSIGN(RwAbstractSocket);

};

}

}

#endif // _RWNETWORKING_RWSOCKET_RWABSTRACTSOCKET_
