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
	m_path = QString();
	m_name = QString();
}

Worker::Worker(QString path, QString name)
{
	m_path = path;
	m_name = name;
}

Reply Worker::getReply() const
{
	Reply reply = createReply();
	cleanOutput();
	return reply;
}

QString Worker::getPath() const
{
	return m_path;
}

QString Worker::getName() const
{
	return m_name;
}

bool Worker::executeCommand(const Command& command) const
{
	const QString& order = command.getOrder();
	const vector<QString>& arguments = command.getArguments();

	QString fullPath = m_path;
	fullPath += PATH_SEPERATOR;
	fullPath += m_name;

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

	commandName += "Command \"";
	commandName += m_path;
	commandName +=PATH_SEPERATOR;
	commandName += command.getOrder();

	return commandName;
}

Reply Worker::createReply() const
{
	typedef Reply::ByteStreams ByteStreams;

	QString outputPath = getOutputPath();

	vector< QString > files;

	Utils::SystemManagement::getListOfFilesInDir(outputPath, files);

	const size_t numberOfFiles = files.size();

	ByteStreams rawData;

	ifstream file;
	for (size_t i = 0; i < numberOfFiles; ++i)
	{
		const QString& fileName = files[i];
		file.open(fileName.toStdString().c_str(), ifstream::binary);
		if ( !file.is_open() )
		{
			QString errorMessage = "Failed to open file ";
			errorMessage += fileName;
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

QString Worker::getOutputPath() const
{
	QString outputPath = "";
	outputPath += m_path;
	outputPath += PATH_SEPERATOR;
	outputPath += m_name;
	outputPath += PATH_SEPERATOR;
	outputPath += "output";
	outputPath += PATH_SEPERATOR;

	return outputPath;
}

void Worker::cleanOutput() const
{
	QString outputPath = getOutputPath();

	vector< QString > files;

	Utils::SystemManagement::getListOfFilesInDir(outputPath, files);

	Utils::SystemManagement::deleteFiles(files);
}

}
