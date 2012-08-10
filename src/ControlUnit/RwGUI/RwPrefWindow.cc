/* 

RwPrefWindow.cc: Preferences window

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#include "RwPrefWindow.h"

namespace RwGUI {

    RwPrefWindow::RwPrefWindow(QWidget* parent) : QDialog(parent)
    {
        setWindowTitle(tr("Remote Workers Preferences"));
        
        m_prefLayout = new QHBoxLayout(this);
        m_tmpLabel = new QLabel("Not ready yet", this);
    }
    
    RwPrefWindow::~RwPrefWindow()
    {
        
    }
    
}
