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
#include <QDataStream>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwSocket {

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstract base class for a socket. This class is actually a proxy
///        to QT Sockets. This was created to avoid mixing templates and
///        QObjects.
////////////////////////////////////////////////////////////////////////////////
class RwAbstractSocket : public QObject {

	Q_OBJECT

public:
	RwAbstractSocket(QObject* parent);

	virtual ~RwAbstractSocket();

    ////////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the IO device the socket represents
	////////////////////////////////////////////////////////////////////////////////
    virtual QIODevice* getIODevice() = 0;
    
	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to bytesAvailable() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual qint64 bytesAvailable() = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to readAll() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual QByteArray readAll() = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to abort() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual void abort() = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to close() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual void close() = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to write(QByteArray&) from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual qint64 write(QByteArray& data) = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to flush() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual void flush() = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to waitForBytesWritten() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual bool waitForBytesWritten() = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to waitForReadyRead() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual bool waitForReadyRead() = 0;

signals:
	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to readyRead() signal from QT
	////////////////////////////////////////////////////////////////////////////////
	void dataReady();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to error() signal from QT
	////////////////////////////////////////////////////////////////////////////////
	void error();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to connected() signal from QT
	////////////////////////////////////////////////////////////////////////////////
	void connected();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to disconnected() signal from QT
	////////////////////////////////////////////////////////////////////////////////
	void disconnected();

private:
	DISALLOW_COPY_AND_ASSIGN(RwAbstractSocket);

};

}

}

#endif // _RWNETWORKING_RWSOCKET_RWABSTRACTSOCKET_
