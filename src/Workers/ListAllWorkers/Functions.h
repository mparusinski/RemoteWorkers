/* 

Functions.h: All the useful functions of ListAllWorkers worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 05/08/2012.

*/

#ifndef _LISTALLWORKERS_FUNCTIONS_H_
#define _LISTALLWORKERS_FUNCTIONS_H_

#include <QString>
#include <QStringList>

#define THIS_WORKER "ListAllWorkers"

void getListOfWorkers(QStringList& listOfWorkers);

void generateHTMLContent(const QStringList& listOfWorkers, QString& htmlData);

void writeDataToFile(const QString& rawData, const QString& fileName);

#endif // _LISTALLWORKERS_FUNCTIONS_H_
