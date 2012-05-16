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
#include <boost/filesystem.hpp>

#include "CrossPlatform.hpp"

using namespace std;
using namespace boost::filesystem;

namespace WorkerInterface
{

Reply::Reply()
{
	m_replyBuilt = false;
}

bool Reply::isReplyBuilt()
{
	return m_replyBuilt;
}

void Reply::createReply(const Worker& worker)
{
	m_worker = worker;

	string outputPath = "";
	outputPath += m_worker.getName();
	outputPath += Utils::CrossPlatform::getPathSeparator();
	outputPath += "output";
	outputPath += Utils::CrossPlatform::getPathSeparator();

	const path outputPath_boost = outputPath;

	vector< string > files;

	try
	{
		if (exists(outputPath_boost) && is_directory(outputPath_boost))
		{
			for (directory_iterator iter(outputPath_boost); iter != directory_iterator(); ++iter)
			{
				if ( !is_directory((*iter).status()) )
				{
					const path& elemInDirectory = (*iter).path();
					files.push_back(elemInDirectory.filename().string());
				}
			}
		}
		else
		{
			cerr << "ERROR: Output directory for worker not found!" << endl;
			return;
		}
	}

	catch (const filesystem_error& ex)
	{
		cerr << "ERROR: Error caught when reading reply from worker";
		return;
	}

	const size_t numberOfFiles = files.size();

	ByteStreams allTheData;

	for (size_t i = 0; i < numberOfFiles; ++i)
	{
		const string& fileName = files[i];
		ifstream fileData(fileName.c_str(), ifstream::binary);

		fileData.seekg(0, ios::end);
		const size_t length = fileData.tellg();
		fileData.seekg(0, ios::beg);

		ByteStream bytes;
		for (size_t i = 0; i < length; ++i)
		{
			char character;
			fileData.get(character);
			bytes.push_back(character);
		}

		allTheData.push_back(pair<string, ByteStream>(fileName,bytes));
	}

	m_replyBuilt = true;
}

}
