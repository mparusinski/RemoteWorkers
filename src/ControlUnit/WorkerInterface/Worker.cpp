/* 

Worker.cpp: Interface to a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "Worker.hpp"

#include <string>
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
	m_path = string();
	m_name = string();
}

Worker::Worker(string path, string name)
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

string Worker::getPath() const
{
	return m_path;
}

string Worker::getName() const
{
	return m_name;
}

void Worker::executeCommand(const Command& command) const
{
	const string& order = command.getOrder();
	const vector<string>& arguments = command.getArguments();

	string fullPath = m_path;
	fullPath += Utils::SystemManagement::getPathSeparator();
	fullPath += m_name;

	if ( Utils::SystemManagement::executeCommand(fullPath, order, arguments) == 0 )
	{
		string errorMessage = commandToString(command);
		errorMessage += " did not execute properly";
		Utils::Logger::getInstance()->error(errorMessage);
	}
	else
	{
		string successMessage = commandToString(command);
		successMessage += " did execute properly";
		Utils::Logger::getInstance()->log(successMessage);
	}
}

string Worker::commandToString(const Command& command) const
{
	string commandName;

	commandName += "Command ";
	commandName += m_path;
	commandName += Utils::SystemManagement::getPathSeparator();
	commandName += command.getOrder();

	return commandName;
}

Reply Worker::createReply() const
{
	typedef Reply::ByteStreams ByteStreams;

	string outputPath = getOutputPath();

	vector< string > files;

	Utils::SystemManagement::getListOfFilesInDir(outputPath, files);

	const size_t numberOfFiles = files.size();

	ByteStreams rawData;

	ifstream file;
	for (size_t i = 0; i < numberOfFiles; ++i)
	{
		const string& fileName = files[i];
		file.open(fileName.c_str(), ifstream::binary);
		if ( !file.is_open() )
		{
			string errorMessage = "Failed to open file ";
			errorMessage += fileName;
			Utils::Logger::getInstance()->error(errorMessage);
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

		rawData.push_back(pair<string, ByteStream>(fileName, bytes));
	}

	return Reply(rawData);
}

string Worker::getOutputPath() const
{
	string outputPath = "";
	outputPath += m_path;
	outputPath += Utils::SystemManagement::getPathSeparator();
	outputPath += m_name;
	outputPath += Utils::SystemManagement::getPathSeparator();
	outputPath += "output";
	outputPath += Utils::SystemManagement::getPathSeparator();

	return outputPath;
}

void Worker::cleanOutput() const
{
	string outputPath = getOutputPath();

	vector< string > files;

	Utils::SystemManagement::getListOfFilesInDir(outputPath, files);

	Utils::SystemManagement::deleteFiles(files);
}

}
