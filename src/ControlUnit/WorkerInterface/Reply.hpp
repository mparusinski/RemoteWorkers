/* 

Reply.hpp: Captures the response of a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _REPLY_HPP_
#define _REPLY_HPP_

#include <iostream>
#include <fstream>
#include <vector>

#include "Worker.hpp"
#include "DataStructures/ByteStream.hpp"

using namespace std;
using namespace DataStructures;

namespace WorkerInterface
{

class Reply
{
public:
	typedef vector< pair<string, ByteStream> > ByteStreams;

	Reply();
	Reply(const Worker& worker);
	virtual ~Reply();

	bool isReplyBuilt() const;
	void createReply();
	void cleanWorkerOutput() const;
	const ByteStreams& getRawData();

private:
	string getOutputPath() const;

	bool m_replyBuilt;
	ByteStreams m_rawData;
	Worker m_worker;

};

}

#endif // _REPLY_HPP_
