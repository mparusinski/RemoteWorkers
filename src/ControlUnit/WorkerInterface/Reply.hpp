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
#include <vector>

#include "DataStructures/ByteStream.hpp"

using namespace std;
using namespace DataStructures;

namespace WorkerInterface
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class encapsulate the information of a worker reply. It contains
///        the raw data of a reply. This class should not be created directly,
///        but by a third party object like a worker.
////////////////////////////////////////////////////////////////////////////////
class Reply
{
public:
	typedef vector< pair<string, ByteStream> > ByteStreams;

	Reply();
	Reply(const ByteStreams& rawData);
	virtual ~Reply();

	bool empty() const;
	const ByteStreams& getRawData();

private:
	bool m_empty;
	ByteStreams m_rawData;

};

}

#endif // _REPLY_HPP_
