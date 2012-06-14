/* 

CrossPlatform.cpp: Handle cross platform stuff

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "SystemManagement.hpp"

#include "Utils/Logger.hpp"

#include <QFileInfo>
#include <QDir>

#define PATH_SEPERATOR "/";

namespace Utils
{

void SystemManagement::getListOfFilesInDir(const QFileInfo& directory, QFileInfoList& files)
{
	if (directory.exists() && directory.isDir())
	{
		const QDir directoryReal(directory.absolutePath());
		files = directoryReal.entryInfoList(QDir::Files);
	}
	else
	{
		QString errorMessage = "Directory ";
		errorMessage += directory.filePath();
		errorMessage += " not found";

		Utils::Logger::getInstance()->error_msg(errorMessage);
	}
}

void SystemManagement::getListOfDirsInDir(const QFileInfo& directory, QFileInfoList& directories)
{
	if (directory.exists() && directory.isDir())
	{
		const QDir directoryReal(directory.absolutePath());
		directories = directoryReal.entryInfoList(QDir::Dirs);
		//Utils::Logger::getInstance()->debug(directoryReal.absolutePath().toStdString());
	}
	else
	{
		QString errorMessage = "Directory ";
		errorMessage += directory.filePath();
		errorMessage += " not found";
		Utils::Logger::getInstance()->error_msg(errorMessage);
		return;
	}
}

void SystemManagement::deleteFiles(const QFileInfoList& files)
{
	const int numberOfFiles = files.size();

	for (int i = 0; i < numberOfFiles; ++i)
	{
		const QFileInfo& filePath = files[i];
		QDir fileDirectory = filePath.absoluteDir();
		fileDirectory.remove(filePath.filePath());
	}
}

void SystemManagement::setSafeEnvironment(QProcessEnvironment& environment)
{

}

}
