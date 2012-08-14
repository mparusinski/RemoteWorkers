/* 

main.cpp: main file for the simple test worker that generates a generic output

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include <QFileInfo>
#include <QDir>

#include "SimpleTestWorker.h"

int main(int argc, char *argv[])
{
	SimpleTestWorker::createGenericHTMLFile();
	return 0;
}
