/* 

CrossPlatform.cpp: Handle cross platform stuff

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 15/04/2012 Michal Parusinski <mparusinski@googlemail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 

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
			Utils::Logger::getInstance()->error("Directory not found");
			return;
		}
	}

	catch (const filesystem_error& ex)
	{
		string errorMessage = "Unable to get list of files in directory in";
		errorMessage += directory;
		Utils::Logger::getInstance()->error(errorMessage);
		return;
	}
}

}
