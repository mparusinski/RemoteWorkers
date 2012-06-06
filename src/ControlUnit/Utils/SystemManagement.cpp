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

int SystemManagement::executeCommand(
			const string& directory,
			const string& command,
			const vector<string>& arguments)
{
	QString fullCommand("");
	fullCommand += directory.c_str();
	fullCommand += PATH_SEPERATOR;
	fullCommand += command.c_str();

	QStringList argumentsList;

	for (size_t i = 0; i < arguments.size(); i++)
	{
		argumentsList.push_back(QString(arguments[i].c_str()));
	}

	QProcess process;
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	setSafeEnvironment(env);
	process.setProcessEnvironment(env);

	process.start(fullCommand, argumentsList);
	bool finished = process.waitForFinished(300000);

	if (!finished)
	{
		Utils::Logger::getInstance()->error_msg("The run command did not finish properly! May have timed out");
		process.kill();
		return 0;
	}

	int exitCode = process.exitCode();

	return exitCode;
}

void SystemManagement::getListOfFilesInDir(const string& directory, vector<string>& files)
{
	QFileInfo directoryPath(QString(directory.c_str()));

	if (directoryPath.exists() && directoryPath.isDir())
	{
		const QDir directoryReal(directoryPath.absolutePath());
	    const QFileInfoList fileList = directoryReal.entryInfoList(QDir::Files);
		for (int i = 0; i < fileList.length(); ++i)
		{
			files.push_back(fileList[i].filePath().toStdString());
		}
	}
	else
	{
		string errorMessage = "Directory ";
		errorMessage += directoryPath.absoluteFilePath().toStdString();

		errorMessage += " not found";
		Utils::Logger::getInstance()->error_msg(errorMessage);
		return;
	}
}

void SystemManagement::getListOfDirsInDir(const string& directory, vector<string>& directories)
{
	const QFileInfo directoryPath(QString(directory.c_str()));

	if (directoryPath.exists() && directoryPath.isDir())
	{
		const QDir directoryReal(directoryPath.absolutePath());
		const QFileInfoList directoryList = directoryReal.entryInfoList(QDir::Dirs);
		//Utils::Logger::getInstance()->debug(directoryReal.absolutePath().toStdString());

		for (int i = 0; i < directoryList.size(); ++i)
		{
			//Utils::Logger::getInstance()->debug(directoryList[i].fileName().toStdString());
			directories.push_back(directoryList[i].fileName().toStdString());
		}
	}
	else
	{
		string errorMessage = "Directory ";
		errorMessage += directoryPath.absoluteFilePath().toStdString();
		errorMessage += " not found";
		Utils::Logger::getInstance()->error_msg(errorMessage);
		return;
	}
}

void SystemManagement::deleteFiles(const vector<string>& files)
{
	const size_t numberOfFiles = files.size();

	for (size_t i = 0; i < numberOfFiles; ++i)
	{
		const QFileInfo filePath(QString(files[i].c_str()));
		QDir fileDirectory = filePath.absoluteDir();
		fileDirectory.remove(filePath.filePath());
	}
}

void SystemManagement::setSafeEnvironment(QProcessEnvironment& environment)
{

}

}
