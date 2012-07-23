/* 

RwModeWidget.h: Proxy for displaying widgets

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwModeWidget.h"

namespace RwGUI {

RwModeWidget::RwModeWidget(QWidget* parent, QToolBar* toolBar) : QWidget(parent)
{
	m_workersCenter = new RwWorkersCenterMode(this, toolBar);
	m_remoteDevices = new RwRemoteDevicesMode(this, toolBar);
	m_events = new RwEventsMode(this, toolBar);
	m_currentMode = m_workersCenter;
}

RwModeWidget::~RwModeWidget()
{

}

void RwModeWidget::setVisible(bool visible)
{
	if (visible)
		m_currentMode->show();
	else
		m_currentMode->hide();
}

void RwModeWidget::focus(RwAbstractMode* mode)
{
	m_currentMode->hide();
	m_currentMode = mode;
	m_currentMode->show();
}

}
