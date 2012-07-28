/* 

RwCommandClientSSL.h: Client for RwCommandServerSSL.

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTSSL_H_
#define _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTSSL_H_

#include "RwCommandClientBase.h"

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwClients {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents a SSL socket to a SSL Command Server.
///        Use only in conjunction with RwCommandServerSSL
////////////////////////////////////////////////////////////////////////////////
class RwCommandClientSSL : public RwCommandClientBase {

	Q_OBJECT

public:
	RwCommandClientSSL(QObject* parent, const QString& hostName, quint16 portNumber);
	virtual ~RwCommandClientSSL();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Connects to local server at server name (given at construction).
	////////////////////////////////////////////////////////////////////////////////
	virtual void connectToServer();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Disconnects from local server.
	////////////////////////////////////////////////////////////////////////////////
	virtual void disconnectFromServer();

private:
	DISALLOW_COPY_AND_ASSIGN(RwCommandClientSSL);

	QString m_hostName;
	quint16 m_port;
};

}

}

#endif // _RWNETWORKING_RWCLIENTS_RWCOMMANDCLIENTSSL_H_
