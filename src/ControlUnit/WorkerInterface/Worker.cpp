/* 

Worker.cpp: Interface to a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "Worker.hpp"

#include <iostream>
#include <fstream>

#include <QDir>

#include "Reply.hpp"
#include "Utils/SystemManagement.hpp"
#include "Utils/Logger.hpp"
#include "DataStructures/ByteStream.hpp"

using namespace std;
using namespace DataStructures;

namespace WorkerInterface
{

Worker::Worker()
{
}

Worker::Worker(const QFileInfo& path)
{
	m_path = path;
	getOutputPath();
}

Reply Worker::getReply() const
{
	Reply reply = createReply();
	cleanOutput();
	return reply;
}

const QFileInfo& Worker::getPath() const
{
	return m_path;
}

bool Worker::executeCommand(const Command& command) const
{
	const QString& order = command.getOrder();
	const QStringList& arguments = command.getArguments();

	QString fullPath = m_path.filePath();

	QString fullCommand = commandToString(command);
	fullCommand += " ";
	for (size_t i = 0; i < arguments.size(); ++i)
	{
		fullCommand += arguments[i];
	}
	fullCommand += "\" was executed";
	Utils::Logger::getInstance()->log(fullCommand);

	return Utils::SystemManagement::executeCommand(fullPath, order, arguments) == 0;
}

QString Worker::commandToString(const Command& command) const
{
	QString commandName;

	commandName += "Command ";
	commandName += m_path.filePath();
	commandName +=PATH_SEPERATOR;
	commandName += command.getOrder();

	return commandName;
}

Reply Worker::createReply() const
{
	typedef Reply::ByteStreams ByteStreams;

	QFileInfoList files;

	Utils::SystemManagement::getListOfFilesInDir(m_outputPath, files);

	const size_t numberOfFiles = files.size();

	ByteStreams rawData;

	ifstream file;
	for (size_t i = 0; i < numberOfFiles; ++i)
	{
		const QString& filePath = files[i].filePath();
		const char * fileName   = filePath.toAscii().data();
		file.open(fileName, ifstream::binary);
		if ( !file.is_open() )
		{
			QString errorMessage = "Failed to open file ";
			errorMessage += filePath;
			Utils::Logger::getInstance()->error_msg(errorMessage);
			return Reply();
		}

		file.seekg(0, ios::end);
		const int length = file.tellg();
		if (length < 0)
			continue;
		file.seekg(0, ios::beg);

		ByteStream bytes(length);
		file.read(bytes.getRawData(), length);
		file.close();

		rawData.push_back(pair<QString, ByteStream>(fileName, bytes));
	}

	return Reply(rawData);
}

void Worker::getOutputPath()
{
	QString fullPathString = m_path.filePath();
	fullPathString += PATH_SEPERATOR;
	fullPathString += "output";
	fullPathString += PATH_SEPERATOR;

	m_outputPath = QFileInfo(fullPathString);
}

void Worker::cleanOutput() const
{
	QFileInfoList files;
	Utils::SystemManagement::getListOfFilesInDir(m_outputPath, files);
	Utils::SystemManagement::deleteFiles(files);
}

}
