/* 

LocalServerTest.cc: Checking if the local server works and more in general if server functionality works

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012

*/

#include "DummyClass.h"

#include <QApplication>

#include "RwUtils/RwLog/RwMessagingManager.h"

using namespace RwUtils::RwLog;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    RwMessagingManager::getInstance()->turnAllOn();
    
    DummyClass button;
    button.show();
    
    return app.exec();
}