/* 

RwClientList.h: Handles the list of available clients

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWCLIENTLIST_H_
#define _RWNETWORKING_RWCLIENTS_RWCLIENTLIST_H_

#include <QObject>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwClients {

class RwClientList : public QObject {

	Q_OBJECT

public:

	RwClientList(QObject* parent);

	virtual ~RwClientList();

private:
	DISALLOW_COPY_AND_ASSIGN(RwClientList);

};

}

}

#endif // _RWNETWORKING_RWCLIENTS_RWCLIENTLIST_H_
