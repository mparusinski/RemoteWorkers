/* 

RwRemoteDeviceList.h: Handles the list of available clients

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 27/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICELIST_H_
#define _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICELIST_H_

#include <QObject>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {

namespace RwClients {

////////////////////////////////////////////////////////////////////////////////
/// \brief Represents the list of devices that are available.
///        The list of devices is read from a file but the user can add or remove
///        remote devices.
////////////////////////////////////////////////////////////////////////////////
class RwRemoteDeviceList : public QObject {

	Q_OBJECT

public:

	RwRemoteDeviceList(QObject* parent);

	virtual ~RwRemoteDeviceList();

private:
	DISALLOW_COPY_AND_ASSIGN(RwRemoteDeviceList);

};

}

}

#endif // _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICELIST_H_
