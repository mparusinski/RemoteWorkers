/* 

<file name>: <purpose>

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include "SimpleTestWorker.hpp"

#include <iostream>
#include <fstream>

using namespace std;

SimpleTestWorker::SimpleTestWorker()
{

}

SimpleTestWorker::~SimpleTestWorker()
{

}

void SimpleTestWorker::createGenericHTMLFile(const string& fileName)
{
	cout << "Generating generic HTML 5 web page with no content" << endl;

	ofstream outputFile;
	outputFile.open(fileName.c_str());

	if ( !outputFile.is_open() )
	{
		cerr << "Unable to open file. Page not successfully generated" << endl;
		return;
	}

	outputFile << "<!DOCTYPE html>" << endl;
	outputFile << "<html>" << endl;
	outputFile << "\t<head>" << endl;
	outputFile << "\t\t<meta charset=\"utf-8\" />" << endl;
	outputFile << "\t\t<title>Generic web page</title>" << endl;
	outputFile << "\t</head>" << endl;
	outputFile << endl;
	outputFile << "\t<body>" << endl;
	outputFile << "Simple message" << endl;
	outputFile << "\t</body>" << endl;
	outputFile << "</html>" << endl;

	outputFile.close();
}
