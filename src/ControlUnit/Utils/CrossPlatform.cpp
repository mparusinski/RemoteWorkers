/* 

CrossPlatform.cpp: Handle cross platform stuff

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include <boost/filesystem.hpp>

#include "CrossPlatform.hpp"
#include "Utils/Logger.hpp"

using namespace boost::filesystem;

namespace Utils
{

string CrossPlatform::getPathSeparator()
{
#ifdef __APPLE__
		return string("/");
#else
#warning "Unknown operating system: getPathSeparator() might behave in the wrong way!"
		Utils::Logger::getInstance()->error("Operating system was not detected at compilation: getPathSeparator() might be broken");
		return string("/");
#endif _APPLE_
}

int CrossPlatform::executeCommand(
			const string& directory,
			const string& command,
			const vector<string>& arguments)
{
	string fullCommand = "";
	fullCommand += directory;
	fullCommand += getPathSeparator();
	fullCommand += command;

	for (size_t i = 0; i < arguments.size(); i++)
	{
		fullCommand += " ";
		fullCommand += arguments[i];
	}


	system(fullCommand.c_str());
	return 1;
}

void CrossPlatform::getListOfFilesInDir(const string& directory, vector<string>& files)
{
	const path directoryPath = directory;

	try
	{
		if (exists(directoryPath) && is_directory(directoryPath))
		{
			for (directory_iterator iter(directoryPath); iter != directory_iterator(); ++iter)
			{
				if ( !is_directory((*iter).status()) )
				{
					const path& elemInDirectory = (*iter).path();
					files.push_back(elemInDirectory.string());
				}
			}
		}
		else
		{
			string errorMessage = "Directory ";
			errorMessage += directoryPath.string();;
			errorMessage += " not found";
			Utils::Logger::getInstance()->error(errorMessage);
			return;
		}
	}

	catch (const filesystem_error& ex)
	{
		string errorMessage = "Unable to get list of files in directory in";
		errorMessage += directoryPath.string();
		Utils::Logger::getInstance()->error(errorMessage);
		return;
	}
}

void CrossPlatform::deleteFiles(const vector<string>& files)
{
	const size_t numberOfFiles = files.size();

	for (size_t i = 0; i < numberOfFiles; ++i)
	{
		const path filePath = files[i];
		remove(filePath);
	}
}

}
