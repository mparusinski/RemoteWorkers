/* 

RwWorkerWidget.cc: Widget displaying a worker

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#include "RwWorkerWidget.h"

#include "RwUtils/RwGlobal/RwConfiguration.h"

using namespace RwUtils::RwGlobal;

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
		setToolTip("Right-click to install " + m_workerName);
		break;
	case RW_WORKER_WIDGET_DELETABLE:
		setToolTip("Right-click to delete " + m_workerName);
		break;
	case RW_WORKER_WIDGET_EXECUTABLE:
		setToolTip("Right-click to execute " + m_workerName);
		break;
	}
}

}
