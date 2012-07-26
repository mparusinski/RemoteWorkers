/* 

RwEventMode.h: Event mode (part of the GUI) for displaying events. Inherits RwAbstractMode

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWEVENTMODE_H_
#define _RWGUI_RWEVENTMODE_H_

#include "RwAbstractMode.h"

#include <QListWidget>
#include <QVBoxLayout>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {

class RwEventsMode : public RwAbstractMode {

	Q_OBJECT

public:
	RwEventsMode(QWidget* parent, QToolBar* toolBar, int index);

	virtual ~RwEventsMode();

public slots:

	void displayEvents();

private:
	virtual void abstract() { }

	void setAction();

	void setEventsWidget();

	QVBoxLayout* m_mainLayout;
	QListWidget* m_eventsWidget;
};

}

#endif // _RWGUI_RWEVENTMODE_H_
