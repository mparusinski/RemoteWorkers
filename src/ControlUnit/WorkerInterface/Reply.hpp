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

#ifndef _REPLY_HPP_
#define _REPLY_HPP_

#include <iostream>
#include <fstream>

#include "Worker.hpp"

using namespace std;

namespace WorkerInterface
{

class Reply
{
public:
	typedef vector<char> ByteStream;
	typedef vector< pair<string, ByteStream> > ByteStreams;

	Reply();
	virtual ~Reply();

	bool isReplyBuilt();
	void createReply(const Worker& worker);

private:
	bool m_replyBuilt;
	ByteStreams m_compressedData;
	Worker m_worker;

};

}

#endif // _REPLY_HPP_
