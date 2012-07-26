/* 

RwRemoteDevicesMode.cc: Remote Devices mode (part of the GUI) for interacting with remote devices. Inherits RwAbstractMode

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwRemoteDevicesMode.h"

namespace RwGUI {

RwRemoteDevicesMode::RwRemoteDevicesMode(QWidget* parent, QToolBar* toolBar, int index) : RwAbstractMode(parent, toolBar, index)
{
	m_modeName = "Remote Devices Mode";

	m_action = new QAction(tr("Remote Devices"), this); // TODO ADD ICON
	m_action->setToolTip(tr("Interact with remote devices"));
	// TODO: Connect remoteDevicesButton to a slot
	attach();
}

RwRemoteDevicesMode::~RwRemoteDevicesMode()
{

}

}
