/* 

ByteStream.hpp: Captures a stream of bytes in an efficient way

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 16/05/2012 Michal Parusinski <mparusinski@googlemail.com>

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

#ifndef _BYTESTREAM_HPP_
#define _BYTESTREAM_HPP_

namespace DataStructures
{

class ByteStream
{
public:
	typedef char ByteType;

	ByteStream();
	ByteStream(const int dataSize);
	ByteStream(const ByteStream& other);
	virtual ~ByteStream();

	ByteStream & operator=(const ByteStream & other);

	void reallocate(const int dataSize);
	void free();
	ByteType* getRawData();
	int size() const;

private:
	bool m_allocated;
	int m_sizeOfData;
	ByteType* m_rawData;

};

}

#endif // _BYTESTREAM_HPP_
