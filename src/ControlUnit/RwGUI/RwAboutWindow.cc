/* 

RwPrefWindow.cc: Preferences window

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 06/08/2012.

*/

#include "RwAboutWindow.h"

namespace RwGUI {
    
    RwAboutWindow::RwAboutWindow(QWidget* parent) : QDialog(parent)
    {
        setWindowTitle(tr("About Remote Workers"));
        
        m_aboutLayout = new QHBoxLayout(this);
        
        QString about = tr("Remote Workers allows to interact with remote computers, laptops and mobile devices");
        m_aboutText = new QLabel(about, this);
        m_aboutLayout->addWidget(m_aboutText);
    }
    
    RwAboutWindow::~RwAboutWindow()
    {
        
    }
    
}