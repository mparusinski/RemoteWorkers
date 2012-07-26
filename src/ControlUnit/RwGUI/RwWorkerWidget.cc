/* 

RwWorkerWidget.cc: Widget displaying a worker

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#include "RwWorkerWidget.h"

#include "RwWorkerInterface/RwConfiguration.h"

using namespace RwWorkerInterface;

namespace RwGUI {

RwWorkerWidget::RwWorkerWidget(QListWidget* parent, QString& workerName, OptionsType type) : QListWidgetItem(parent)
{
	m_workerName = workerName;
	m_options = type;
	setLayout();
}

RwWorkerWidget::~RwWorkerWidget()
{

}

void RwWorkerWidget::setLayout()
{
	QString pathToWorkersIcon = "";
	RwConfiguration::getInstance()->getWorkersPath(pathToWorkersIcon);
	pathToWorkersIcon += m_workerName;
	pathToWorkersIcon += '/';
	pathToWorkersIcon += "icon.png";

	QIcon m_icon(pathToWorkersIcon); // hope this works
	setIcon(m_icon);
	setText(m_workerName);

	setType(m_options);
}

void RwWorkerWidget::setType(OptionsType type)
{
	m_options = type;
	switch (m_options)
	{
	case RW_WORKER_WIDGET_INSTALLABLE:
		setToolTip("Install " + m_workerName);
		break;
	case RW_WORKER_WIDGET_DELETABLE:
		setToolTip("Delete " + m_workerName);
		break;
	case RW_WORKER_WIDGET_EXECUTABLE:
		setToolTip("Execute " + m_workerName);
		break;
	}
}

}
