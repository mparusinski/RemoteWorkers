/* 

SanitizedEnvironment.cc: Check if the environment is sanitized

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/07/2012.

*/

#include "SanitizedEnvironment.h"

#include <cstdlib>
#include <cstdio>
#include <QProcess>

void checkForModificationsOfEnv()
{
    const QProcessEnvironment currentEnv = QProcessEnvironment::systemEnvironment();
    const QString homeValue = currentEnv.value("HOME");
    const QString userValue = currentEnv.value("USER");
    if ( (homeValue != "/Users/" + userValue) || (homeValue != "/Users/" + userValue + "/") ) {
        printf("MAC OS X detected or system environment has been modified\n");
    } else if ( (homeValue != "/home/" + userValue) || (homeValue != "/home/" + userValue + "/") ) {
        printf("Unix/Linux detected or system environment has been modified\n");
    } else {
        printf("System environment has been modified\n");
    } // WINDOWS NOT TREATED YET
}