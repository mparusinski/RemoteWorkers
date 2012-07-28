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

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to bytesAvailable() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual qint64 bytesAvailable();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to readAll() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual QByteArray readAll();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to abort() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual void abort();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to close() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual void close();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to write(QByteArray&) from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual qint64 write(QByteArray& data);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to flush() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual void flush();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to waitForBytesWritten() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual bool waitForBytesWritten();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to waitForReadyRead() from QT
	////////////////////////////////////////////////////////////////////////////////
	virtual bool waitForReadyRead();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to connectToHost(QString&, int) from QT
	////////////////////////////////////////////////////////////////////////////////
	void connectToHost(QString& hostName, int port);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Proxy to disconnectFromHost() from QT
	////////////////////////////////////////////////////////////////////////////////
	void disconnectFromHost();

public slots:
	////////////////////////////////////////////////////////////////////////////////
	/// \brief Resends signal readyRead() from QT
	////////////////////////////////////////////////////////////////////////////////
	void readReady();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Resends signal error(QAbstractSocket::SocketError) from QT
	////////////////////////////////////////////////////////////////////////////////
	void socketError(QAbstractSocket::SocketError error);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Resends signal connected() from QT
	////////////////////////////////////////////////////////////////////////////////
	void connectedSlot();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Resends signal disconnected() from QT
	////////////////////////////////////////////////////////////////////////////////
	void disconnectedSlot();

private:
	DISALLOW_COPY_AND_ASSIGN(RwTCPSocket);

	void init();

	QTcpSocket* m_tcpSocket;

};

}

}

#endif // _RWNETWORKING_RWSOCKET_RWTCPSOCKET_H_
