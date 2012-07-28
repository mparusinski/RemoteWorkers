/* 

RwRemoteDevice.h: Encapsulate data for remote devices

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#include "RwRemoteDevice.h"

namespace RwNetworking {

namespace RwClients {

RwRemoteDevice::RwRemoteDevice(QObject* parent, const QString& deviceName) : QObject(parent)
{
	m_deviceName = deviceName;
}

RwRemoteDevice::~RwRemoteDevice()
{

}

QString& RwRemoteDevice::getDeviceName()
{
	return m_deviceName;
}

const QString& RwRemoteDevice::getDeviceName() const
{
	return m_deviceName;
}

}

}
