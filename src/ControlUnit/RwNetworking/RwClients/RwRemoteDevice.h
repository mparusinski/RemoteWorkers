/* 

RwRemoteDevice.h: Encapsulate data for remote devices

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#ifndef _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICE_H_
#define _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICE_H_

#include <QObject>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwCommandClientBase.h"

namespace RwNetworking {

namespace RwClients {

////////////////////////////////////////////////////////////////////////////////
/// \brief Encapsulates a remote device accessible through a suitable client.
///        This class hides the actual implementation of the client.
///        Use this class to communicate with a remote device.
////////////////////////////////////////////////////////////////////////////////
class RwRemoteDevice : public QObject {

	Q_OBJECT

public:
	RwRemoteDevice(QObject* parent, const QString& deviceName);

	virtual ~RwRemoteDevice();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the name or address of the device (depending whether it a
	///        local or remote client).
	/// \return Name or address of the remote device
	////////////////////////////////////////////////////////////////////////////////
	QString& getDeviceName();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the name or address of the device (depending whether it a
	///        local or remote client).
	/// \return Name or address of the remote device
	////////////////////////////////////////////////////////////////////////////////
	const QString& getDeviceName() const;

private:
	DISALLOW_COPY_AND_ASSIGN(RwRemoteDevice);

	QString m_deviceName;
	RwCommandClientBase* m_client;

};

}

}

#endif // _RWNETWORKING_RWCLIENTS_RWREMOTEDEVICE_H_
