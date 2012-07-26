/* 

RwWorkersCenterMode.h: Workers mode (part of the GUI) for managing workers. Inherits RwAbstractMode

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWWORKERSCENTER_MODE_H_
#define _RWGUI_RWWORKERSCENTER_MODE_H_

#include "RwAbstractMode.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QListWidget>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {

class RwWorkersCenterMode : public RwAbstractMode {

	Q_OBJECT

public:
	RwWorkersCenterMode(QWidget* parent, QToolBar* toolBar, int index);

	virtual ~RwWorkersCenterMode();

private:
	virtual void abstract() { }

	void setAction();

	void setLayout();

	void readWorkers();

	QHBoxLayout* m_mainLayout;
	QVBoxLayout* m_workersLayout;
	QWidget* m_workersWidget;

	QListWidget* m_optionsList;
	QListWidget* m_availableWorkers;
	QListWidget* m_installedWorkers;

};

}

#endif // _RWGUI_RWWORKERSCENTER_MODE_H_
