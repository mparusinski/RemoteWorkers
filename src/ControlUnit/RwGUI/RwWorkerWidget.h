/* 

RwWorkerWidget.h: Widget displaying a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#ifndef _RWGUI_RWWORKERWIDGET_H_
#define _RWGUI_RWWORKERWIDGET_H_

#include <QWidget>
#include <QString>
#include <QListWidgetItem>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {

class RwWorkerWidget : public QListWidgetItem {

public:

#define RW_WORKER_WIDGET_INSTALLABLE 1
#define RW_WORKER_WIDGET_DELETABLE 2
#define RW_WORKER_WIDGET_EXECUTABLE 4

	typedef quint32 OptionsType;

	RwWorkerWidget(QListWidget* parent, QString& workerName, OptionsType type);

	virtual ~RwWorkerWidget();

	void setType(OptionsType type);

private:
	DISALLOW_COPY_AND_ASSIGN(RwWorkerWidget);

	void setLayout();

	QString m_workerName; // not using a worker directly (too much space)
	// possible menu
	OptionsType m_options;
};

}

#endif // _RWGUI_RWWORKERWIDGET_H_
