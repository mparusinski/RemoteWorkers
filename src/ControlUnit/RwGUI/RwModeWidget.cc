/* 

RwModeWidget.h: Proxy for displaying widgets

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwModeWidget.h"

namespace RwGUI {

RwModeWidget::RwModeWidget(QWidget* parent, QToolBar* toolBar) : QStackedWidget(parent)
{
	m_workersCenter = new RwWorkersCenterMode(this, toolBar, 0);
	m_remoteDevices = new RwRemoteDevicesMode(this, toolBar, 1);
	m_events = new RwEventsMode(this, toolBar, 2);

	insertWidget(0, m_workersCenter);
	insertWidget(1, m_remoteDevices);
	insertWidget(2, m_events);
}

RwModeWidget::~RwModeWidget()
{

}

}
