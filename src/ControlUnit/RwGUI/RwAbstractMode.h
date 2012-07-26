/* 

RwAbstractMode.h: Abstract base class for modes (part of the UI)

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWABSTRACTMODE_H_
#define _RWGUI_RWABSTRACTMODE_H_

#include <QMainWindow>
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QString>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {

class RwAbstractMode : public QWidget {

	Q_OBJECT;

public :
	RwAbstractMode(QWidget* parent, QToolBar* toolBar, int index);

	virtual ~RwAbstractMode();

public slots:
	void focus();

protected:
	QAction* m_action;
	QToolBar* m_toolBar;
	QString m_modeName; // useful for debugging
	int m_index;

	void attach();

private:
	virtual void abstract() = 0;
};

}

#endif // _RWGUI_RWABSTRACTMODE_H_
