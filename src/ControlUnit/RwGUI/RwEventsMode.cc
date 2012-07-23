/* 

RwEventMode.cc: Event mode (part of the GUI) for displaying events. Inherits RwAbstractMode

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwEventsMode.h"

namespace RwGUI {

RwEventsMode::RwEventsMode(QWidget * parent, QToolBar * toolBar) : RwAbstractMode(parent, toolBar)
{
	m_action = new QAction(tr("Events"), this); // TODO ADD ICON
	m_action->setToolTip(tr("View all Remote Workers events on this computer"));
	// TODO: cConnect eventsButton to a slot
	attach();
}

RwEventsMode::~RwEventsMode()
{

}

}
