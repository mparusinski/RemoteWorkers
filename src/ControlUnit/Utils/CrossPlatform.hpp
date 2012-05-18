/* 

CrossPlatform.hpp: Handle cross platform stuff

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _CROSSPLATFORM_HPP_
#define _CROSSPLATFORM_HPP_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace Utils
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class contains a set of function to allow cross platform
///        functionality.
////////////////////////////////////////////////////////////////////////////////
class CrossPlatform
{
public:
	static string getPathSeparator();

	static int executeCommand(
				const string& directory,
				const string& command,
				const vector<string>& arguments);

	static void getListOfFilesInDir(const string& directory, vector<string>& files);
	static void getListOfDirsInDir(const string& directory, vector<string>& directories);
	static void deleteFiles(const vector<string>& files);
};

}

#endif //_CROSSPLATFORM_HPP_
