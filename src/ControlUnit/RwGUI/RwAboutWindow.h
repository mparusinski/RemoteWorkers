/* 

RwAboutWindow.h: About Remote Workers Window

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 06/08/2012.

*/

#ifndef _RWGUI_RWABOUTWINDOW_H_
#define _RWGUI_RWABOUTWINDOW_H_

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {
    
    class RwAboutWindow : public QDialog {
        
        Q_OBJECT
        
    public:
        RwAboutWindow(QWidget* parent);
        
        virtual ~RwAboutWindow();
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwAboutWindow);
        
        QHBoxLayout* m_aboutLayout;
        QLabel* m_aboutText;
        
    };
    
}

#endif // _RWGUI_RWABOUTWINDOW_H_
