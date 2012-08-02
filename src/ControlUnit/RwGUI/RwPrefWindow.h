/* 

RwPrefWindow.h: Preferences window

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWPREFWINDOW_H_
#define _RWGUI_RWPREFWINDOW_H_

#include <QWidget>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {

    class RwPrefWindow : public QWidget {

    Q_OBJECT
    
public :
    RwPrefWindow(QWidget* parent);
    
    virtual ~RwPrefWindow();

private:
    DISALLOW_COPY_AND_ASSIGN(RwPrefWindow);

};

}

#endif // _RWGUI_RWPREFWINDOW_H_
