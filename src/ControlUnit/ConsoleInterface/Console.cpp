/* 

Console.cpp: Entry point for the server side

As part of the Remote Workers project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

// NO FUNCTIONS TO BE ADDED TO THIS FILE

#include <string>
#include <vector>
#include <iostream>

#include "WorkerInterface/Reply.hpp"
#include "WorkerInterface/Worker.hpp"
#include "WorkerInterface/Command.hpp"
#include "WorkerInterface/Management.hpp"
#include "Utils/Logger.hpp"

using namespace std;
using namespace WorkerInterface;

int main(int argc, char *argv[])
{
	Utils::Logger::getInstance()->switchAllOn();

	Worker worker = Management::getInstance()->createWorker("SimpleTestWorker");
	Command command("SimpleTestWorker", vector<string>());
	worker.executeCommand(command);
	Reply reply = worker.getReply();

	if ( !reply.isReplyBuilt() )
	{
		Utils::Logger::getInstance()->error("Reply is not built");
		return -1;
	}
	else
	{
		Utils::Logger::getInstance()->log("Reply is built");
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
