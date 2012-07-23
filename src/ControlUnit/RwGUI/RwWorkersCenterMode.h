/* 

RwWorkersCenterMode.h: Workers mode (part of the GUI) for managing workers. Inherits RwAbstractMode

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012.

*/

#ifndef _RWGUI_RWWORKERSCENTER_MODE_H_
#define _RWGUI_RWWORKERSCENTER_MODE_H_

#include "RwAbstractMode.h"

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwGUI {

class RwWorkersCenterMode : public RwAbstractMode {

	Q_OBJECT

public:
	RwWorkersCenterMode(QWidget* parent, QToolBar* toolBar);

	virtual ~RwWorkersCenterMode();

private:
	virtual void abstract() { }
};

}

#endif // _RWGUI_RWWORKERSCENTER_MODE_H_
