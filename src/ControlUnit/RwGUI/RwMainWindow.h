/* 

RwMainWindow.h: The main window of the application

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWMAINWINDOW_H_
#define _RWGUI_RWMAINWINDOW_H_

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QPushButton>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwModeWidget.h"
#include "RwAboutWindow.h"
#include "RwPrefWindow.h"

namespace RwGUI {
    
    class RwMainWindow : public QMainWindow {
        
        Q_OBJECT
        
    public:
        
        RwMainWindow();
        
        virtual ~RwMainWindow();
        
    public slots:
        
        void closeRemoteWorkers();
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwMainWindow);
        
        void createMenuBar();
        void createModes();
        void setWindowAttributes();
        void createStatusBar();

        QToolBar* m_tools;
        QStatusBar* m_status;
        
        RwModeWidget* m_mode;
        RwAboutWindow* m_aboutWindow;
        RwPrefWindow* m_prefWindow;
        
    };
    
}

#endif // _RWGUI_RWMAINWINDOW_H_
