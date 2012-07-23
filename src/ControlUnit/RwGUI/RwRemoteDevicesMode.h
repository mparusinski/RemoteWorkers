/* 

RwRemoteDevicesMode.h: Remote Devices mode (part of the GUI) for interacting with remote devices. Inherits RwAbstractMode

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWREMOTEDEVICESMODE_H_
#define _RWGUI_RWREMOTEDEVICESMODE_H_

#include "RwAbstractMode.h"

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {

class RwRemoteDevicesMode : public RwAbstractMode {

	Q_OBJECT

public:
	RwRemoteDevicesMode(QWidget* parent, QToolBar* toolBar);

	virtual ~RwRemoteDevicesMode();

private:
	virtual void abstract() { }
};

}

#endif // _RWGUI_RWREMOTEDEVICESMODE_H_
