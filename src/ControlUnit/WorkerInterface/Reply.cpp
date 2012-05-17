/* 

Reply.hpp: Captures the response of a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 15/05/2012 Michal Parusinski <mparusinski@googlemail.com>

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

#include "Reply.hpp"

#include <string>
#include <LzmaLib.h>

#include "Worker.hpp"

#include "Utils/CrossPlatform.hpp"
#include "Utils/Logger.hpp"

using namespace std;

namespace WorkerInterface
{

Reply::Reply()
{

}

Reply::~Reply()
{

}

Reply::Reply(const Worker& worker)
{
	m_replyBuilt = false;
	m_worker = worker;
	createReply();
}

bool Reply::isReplyBuilt() const
{
	return m_replyBuilt;
}

string Reply::getOutputPath() const
{
	string outputPath = "";
	outputPath += m_worker.getPath();
	outputPath += Utils::CrossPlatform::getPathSeparator();
	outputPath += "output";
	outputPath += Utils::CrossPlatform::getPathSeparator();

	return outputPath;
}

void Reply::createReply()
{
	string outputPath = getOutputPath();

	vector< string > files;

	Utils::CrossPlatform::getListOfFilesInDir(outputPath, files);

	const size_t numberOfFiles = files.size();

	m_rawData.clear();
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
			return;
		}

		file.seekg(0, ios::end);
		const int length = file.tellg();
		if (length < 0)
			continue;
		file.seekg(0, ios::beg);

		ByteStream bytes(length);
		file.read(bytes.getRawData(), length);
		file.close();

		m_rawData.push_back(pair<string, ByteStream>(fileName, bytes));
	}

	m_replyBuilt = true;
}

void Reply::cleanWorkerOutput() const
{
	string outputPath = getOutputPath();

	vector< string > files;

	Utils::CrossPlatform::getListOfFilesInDir(outputPath, files);

	Utils::CrossPlatform::deleteFiles(files);
}

const Reply::ByteStreams& Reply::getRawData()
{
	return m_rawData;
}

}
