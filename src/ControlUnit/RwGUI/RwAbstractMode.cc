/* 

RwAbstractMode.cc: Abstract base class for modes (part of the UI)

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwAbstractMode.h"

#include "RwUtils/RwLog/RwCommon.h"

#include "RwMainWindow.h"

using namespace RwUtils::RwLog;

namespace RwGUI {

RwAbstractMode::RwAbstractMode(QWidget* parent, QToolBar* toolBar, int index) : QWidget(parent)
{
	m_toolBar = toolBar;
	m_index = index;
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
	RwModeWidget* parent = dynamic_cast<RwModeWidget*>(parentWidget());
	parent->setCurrentIndex(m_index);
}

}
