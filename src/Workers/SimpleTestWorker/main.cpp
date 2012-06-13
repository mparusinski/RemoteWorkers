/* 

main.cpp: main file for the simple test worker that generates a generic output

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include <iostream>
#include <string>
#include <cstdio>
#include <QFileInfo>
#include <QDir>

#include "SimpleTestWorker.hpp"

#if defined(__APPLE__) || defined(__unix__)
	#define PATH_SEPARATOR "/"
#else
 	#define PATH_SEPARATOR "\\"
#endif // __APPLE__ || __unix__

using namespace std;

int main(int argc, char *argv[])
{
	QFileInfo pathToExecutable(argv[0]);
	string outputPath = pathToExecutable.absoluteDir().absolutePath().toStdString();
	outputPath += PATH_SEPARATOR "output" PATH_SEPARATOR "index.html";
	cout << outputPath << endl;

	SimpleTestWorker::createGenericHTMLFile(outputPath);

	cout << "Worker successfully ran" << endl;

	return 0;
}
