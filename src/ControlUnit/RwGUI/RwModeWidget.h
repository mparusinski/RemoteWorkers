/* 

RwModeWidget.h: Proxy for displaying widgets

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWMODEWIDGET_H_
#define _RWGUI_RWMODEWIDGET_H_

#include <QStackedWidget>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwEventsMode.h"
#include "RwWorkersCenterMode.h"
#include "RwRemoteDevicesMode.h"

namespace RwGUI {

class RwModeWidget : public QStackedWidget {

	Q_OBJECT

public:
	RwModeWidget(QWidget* parent, QToolBar* toolBar);

	virtual ~RwModeWidget();

private:
	RwWorkersCenterMode* m_workersCenter;
	RwRemoteDevicesMode* m_remoteDevices;
	RwEventsMode* m_events;

};

}

#endif // _RWGUI_RWMODEWIDGET_H_
