/* 

Console.cpp: Entry point for the server side

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 14/05/2012 Michal Parusinski <mparusinski@googlemail.com>

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

// NO FUNCTIONS TO BE ADDED TO THIS FILE

#include <string>
#include <vector>
#include <iostream>

#include "WorkerInterface/Reply.hpp"
#include "WorkerInterface/Worker.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	WorkerInterface::Worker worker("/Users/mparusinski/Desktop/");
	WorkerInterface::Reply reply;
	reply.createReply(worker);

	if ( !reply.isReplyBuilt() )
	{
		cerr << "Reply is not being built" << endl;
		return -1;
	}
	else
	{
		cout << "Reply is successfully built" << endl;
	}

	vector< pair< string, ByteStream > > rawData = reply.getRawData();
	const size_t numberOfByteStreams = rawData.size();
	for (size_t i = 0; i < numberOfByteStreams; ++i)
	{
		const string& fileName = rawData[i].first;
		ByteStream& byteStream = rawData[i].second;
		cout << "File: " << fileName << endl;

		const size_t lengthOfStream = byteStream.size();
		const char * rawData = byteStream.getRawData();
		for (size_t j = 0; j < lengthOfStream; ++j)
		{
			cout << rawData[j];
		}
		cout << endl << endl;
	}

	return 1;
}
