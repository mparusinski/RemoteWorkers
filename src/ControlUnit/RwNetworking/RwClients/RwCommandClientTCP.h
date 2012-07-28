/* 

RwCommandClientTCP.h: Client for RwCommandServerTCP.

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTTCP_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTTCP_H_

#include "RwCommandClientBase.h"

#include <QObject>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwClients {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents a TCP socket to a TCP Command Server.
///        Use only in conjunction with RwCommandServerTCP
////////////////////////////////////////////////////////////////////////////////
class RwCommandClientTCP : public RwCommandClientBase {

	Q_OBJECT

public:
	RwCommandClientTCP(QObject* parent, const QString& hostName, quint16 portNumber);
	virtual ~RwCommandClientTCP();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Connects to local server at server name (given at construction).
	////////////////////////////////////////////////////////////////////////////////
	virtual void connectToServer();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Disconnects from local server.
	////////////////////////////////////////////////////////////////////////////////
	virtual void disconnectFromServer();

private:
	DISALLOW_COPY_AND_ASSIGN(RwCommandClientTCP);

	QString m_hostName;
	quint16 m_port;
};

}

}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTTCP_H_
