/* 

RwWorkersCenterMode.cc: Workers mode (part of the GUI) for managing workers. Inherits RwAbstractMode

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwWorkersCenterMode.h"

#include "RwWorkerInterface/RwWorkerList.h"

#include "RwWorkerWidget.h"

using namespace RwWorkerInterface;

namespace RwGUI {

RwWorkersCenterMode::RwWorkersCenterMode(QWidget * parent, QToolBar * toolBar, int index) : RwAbstractMode(parent, toolBar, index)
{
	m_modeName = "Workers Center Mode";

	setAction();
	setLayout();

	attach();
}

RwWorkersCenterMode::~RwWorkersCenterMode()
{

}

void RwWorkersCenterMode::setAction()
{
	m_action = new QAction(tr("Workers Center"), this); // TODO ADD ICON
	m_action->setToolTip(tr("View and manage available and installed workers"));
}

void RwWorkersCenterMode::setLayout()
{
	m_mainLayout = new QHBoxLayout(this);

	m_optionsList = new QListWidget(this);
	m_optionsList->setWindowTitle("Options");
	m_optionsList->addItem("All");
	m_workersWidget = new QWidget(this);

	m_workersLayout = new QVBoxLayout(m_workersWidget);

	m_mainLayout->addWidget(m_optionsList, 3);
	m_mainLayout->addWidget(m_workersWidget, 7);

	m_installedWorkers = new QListWidget(this);
	m_installedWorkers->setSortingEnabled(true);
	m_installedWorkers->setViewMode(QListView::IconMode);
	m_installedWorkers->setDragEnabled(false);
	m_installedWorkers->setAcceptDrops(false);

	m_availableWorkers = new QListWidget(this);
	m_availableWorkers->setSortingEnabled(true);
	m_availableWorkers->setViewMode(QListView::IconMode);
	m_availableWorkers->setDragEnabled(false);
	m_availableWorkers->setAcceptDrops(false);

	m_workersLayout->addWidget(m_installedWorkers);
	m_workersLayout->addWidget(m_availableWorkers);

	readWorkers();
}

void RwWorkersCenterMode::readWorkers()
{
	RwWorkerList::getInstance()->readWorkers();
	QList<QString> listOfWorkers = RwWorkerList::getInstance()->getListOfWorkers();
	QList<QString>::iterator iter;
	for (iter = listOfWorkers.begin(); iter != listOfWorkers.end(); ++iter)
	{
		RwWorkerWidget* workerWidget = new RwWorkerWidget(m_installedWorkers, *iter, RW_WORKER_WIDGET_DELETABLE);
		m_installedWorkers->addItem(workerWidget);
	}
}

}
