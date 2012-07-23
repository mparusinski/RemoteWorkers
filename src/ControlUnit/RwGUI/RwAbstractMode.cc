/* 

RwAbstractMode.cc: Abstract base class for modes (part of the UI)

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwAbstractMode.h"

#include "RwMainWindow.h"

namespace RwGUI {

RwAbstractMode::RwAbstractMode(QWidget* parent, QToolBar* toolBar) : QWidget(parent)
{
	m_toolBar = toolBar;
}

RwAbstractMode::~RwAbstractMode()
{

}

void RwAbstractMode::attach()
{
	m_toolBar->addAction(m_action);
	connect(m_action, SIGNAL(triggered()), this, SLOT(focus()));
}

void RwAbstractMode::focus()
{
	RwModeWidget* mainWindow = dynamic_cast<RwModeWidget*>(parentWidget());
	mainWindow->focus(this);
}

}
