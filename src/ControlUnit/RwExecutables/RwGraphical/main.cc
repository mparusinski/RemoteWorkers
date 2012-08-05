/* 

main.cc: Creating a GUI executable for Remote Workers

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/07/2012

*/

#include <QApplication>

#include "RwHistory/RwEventLog.h"

#include "RwUtils/RwGlobal/RwDefines.h"
#include "RwUtils/RwLog/RwMessagingManager.h"
#include "RwGUI/RwMainWindow.h"

#include "RwNetworking/RwServers/RwCommandServerThread.h"

using namespace RwNetworking::RwServers;
using namespace RwGUI;

int main(int argc, char* argv[])
{
	RwUtils::RwLog::RwMessagingManager::turnAllOn();
    
    RwHistory::RwEventLog::getInstance()->restoreLog();

    RwCommandServerThread::getInstance()->start();
    
	QApplication app(argc, argv);
	app.setOrganizationName("Remote Workers Project");
	app.setApplicationName("RemoteWorkers Control Unit");
	app.setApplicationVersion(QString::number(RW_VERSION));
    
	RwMainWindow mainWin;
	mainWin.show();
    
    QObject::connect(&app, SIGNAL(aboutToQuit()), &mainWin, SLOT(closeRemoteWorkers()));

	return app.exec();
}
