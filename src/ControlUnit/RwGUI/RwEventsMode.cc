/* 

RwEventMode.cc: Event mode (part of the GUI) for displaying events. Inherits RwAbstractMode

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwEventsMode.h"

#include "RwHistory/RwEventLog.h"

using namespace RwHistory;

namespace RwGUI {
    
    RwEventsMode::RwEventsMode(QWidget * parent, QToolBar * toolBar, int index) : RwAbstractMode(parent, toolBar, index)
    {
        m_modeName = "Events Mode";
        
        setAction();
        setEventsWidget();
        
        RwEventLog* globalInstance = RwEventLog::getInstance();
        connect(globalInstance, SIGNAL(eventAdded()), this, SLOT(displayEvents()));
        
        attach();
    }
    
    RwEventsMode::~RwEventsMode()
    {
        
    }
    
    void RwEventsMode::setAction()
    {
        m_action = new QAction(tr("Events"), this); // TODO ADD ICON
        m_action->setToolTip(tr("View all Remote Workers events on this computer"));
        connect(m_action, SIGNAL(triggered()), this, SLOT(displayEvents()));
    }
    
    void RwEventsMode::setEventsWidget()
    {
        m_mainLayout = new QVBoxLayout(this);
        
        m_eventsWidget = new QListWidget(this);
        m_eventsWidget->setAcceptDrops(false);
        m_eventsWidget->setDragEnabled(false);
        // possibly other stuff to put here
        
        m_mainLayout->addWidget(m_eventsWidget);
        
        displayEvents();
    }
    
    void RwEventsMode::displayEvents()
    {
        m_eventsWidget->clear();
        RwEventLog::getInstance()->generateAll();
        RwEventLog::getInstance()->lockEventList();
        RwEventLog::EventListType& eventList = RwEventLog::getInstance()->getListOfEvents();
        RwEventLog::EventListType::iterator iter;
        for (iter = eventList.begin(); iter != eventList.end(); ++iter)
        {
            m_eventsWidget->addItem(iter->eventDate().toString() + ": " + iter->description());
        }
        RwEventLog::getInstance()->unlockEventList();
    }
    
    void RwEventsMode::setVisible(bool visible)
    {
        QWidget::setVisible(visible);
        RwEventLog* globalInstanceRwEventLog = RwEventLog::getInstance();
        if (visible)
        {
            connect(globalInstanceRwEventLog, SIGNAL(eventAdded()), this, SLOT(displayEvents()));
        }
        else
        {
            disconnect(globalInstanceRwEventLog, SIGNAL(eventAdded()), this, SLOT(displayEvents()));
        }
    }
    
}
