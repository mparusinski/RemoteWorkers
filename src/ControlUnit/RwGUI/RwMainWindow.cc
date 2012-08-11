/* 

RwMainWindow.h: The main window of the application

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwMainWindow.h"

#include "RwHistory/RwEventLog.h"
#include "RwNetworking/RwServers/RwCommandServerThread.h"

namespace RwGUI {
    
    RwMainWindow::RwMainWindow()
    {
        setWindowAttributes();
        createMenuBar();
        createModes();
        createStatusBar();
    }
    
    RwMainWindow::~RwMainWindow()
    {
        
    }
    
    void RwMainWindow::setWindowAttributes()
    {
        setWindowTitle(tr("Remote Workers Control Unit"));
        setUnifiedTitleAndToolBarOnMac(true);
    }
    
    void RwMainWindow::createModes()
    {
        m_tools = addToolBar(tr("Tools"));
        m_mode = new RwModeWidget(parentWidget(), m_tools);
        setCentralWidget(m_mode);
        m_mode->setVisible(true);
    }
    
    void RwMainWindow::createStatusBar()
    {
        m_status = new QStatusBar(this);
        // m_status->showMessage(tr("Remote Workers server is on"));
        
        setStatusBar(m_status);
    }
    
    void RwMainWindow::closeRemoteWorkers()
    {
        // m_mode->setVisible(false);
        RwNetworking::RwServers::RwCommandServerThread::getInstance()->stopServers();
        
        RwHistory::RwEventLog::getInstance()->generateAll();
        RwHistory::RwEventLog::getInstance()->logRotate();
        RwHistory::RwEventLog::getInstance()->saveLog();
    }
    
    void RwMainWindow::createMenuBar()
    {
        QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
        // setMenuBar(m_menuBar);
        
        m_aboutWindow = new RwAboutWindow(this);
        m_aboutWindow->hide();
        fileMenu->addAction(tr("about.RemoteWorkers"), m_aboutWindow, SLOT(show()));
        
        m_prefWindow = new RwPrefWindow(this);
        m_prefWindow->hide();
        fileMenu->addAction(tr("preferences"), m_prefWindow, SLOT(show()));
        
        fileMenu->addAction(tr("quit"), this, SLOT(close()));
    }
    
}
