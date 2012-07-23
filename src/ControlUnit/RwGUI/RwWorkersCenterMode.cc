/* 

RwWorkersCenterMode.cc: Workers mode (part of the GUI) for managing workers. Inherits RwAbstractMode

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwWorkersCenterMode.h"

namespace RwGUI {

RwWorkersCenterMode::RwWorkersCenterMode(QWidget * parent, QToolBar * toolBar) : RwAbstractMode(parent, toolBar)
{
	m_action = new QAction(tr("Workers Center"), this); // TODO ADD ICON
	m_action->setToolTip(tr("View and manage available and installed workers"));
	// TODO: Connect button to a slot
	attach();
}

RwWorkersCenterMode::~RwWorkersCenterMode()
{

}

}
