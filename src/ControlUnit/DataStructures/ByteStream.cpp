/* 

ByteStream.cpp: Captures a stream of bytes in an efficient way

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

#include "ByteStream.hpp"

#include <cstring>

namespace DataStructures
{

ByteStream::ByteStream()
{
	m_allocated = false;
	m_sizeOfData = 0;
	m_rawData = 0;
}

ByteStream::ByteStream(const int dataSize)
{
	m_sizeOfData = dataSize;
	m_rawData = new ByteType[m_sizeOfData];
	m_allocated = true;
}

ByteStream::~ByteStream()
{
	if (m_allocated)
		delete[] m_rawData;
}

ByteStream::ByteStream(const ByteStream & other)
{
	m_allocated = other.m_allocated;
	m_sizeOfData = other.m_sizeOfData;
	if (m_allocated)
	{
		m_rawData = new ByteType[m_sizeOfData];
		memcpy(m_rawData, other.m_rawData, m_sizeOfData);
	}
}

ByteStream & ByteStream::operator =(const ByteStream & other)
{
	if (this != &other)
	{
		const int sizeOfData  = other.m_sizeOfData;
		ByteType * newRawData = 0;
		const bool allocated = other.m_allocated;
		if (allocated)
		{
			newRawData = new ByteType[sizeOfData];
			memcpy(newRawData, other.m_rawData, sizeOfData);
		}

		if (m_allocated)
			delete[] m_rawData;

		m_sizeOfData = sizeOfData;
		m_allocated = allocated;
		m_rawData = newRawData;
	}

	return *this;
}

void ByteStream::reallocate(const int dataSize)
{
	if (m_allocated)
		delete[] m_rawData;

	m_sizeOfData = dataSize;
	m_rawData = new ByteType[m_sizeOfData];
	m_allocated = true;
}

void ByteStream::free()
{
	if (m_allocated)
		delete[] m_rawData;

	m_sizeOfData = 0;
	m_allocated = false;
}

ByteStream::ByteType * ByteStream::getRawData()
{
	return m_rawData;
}

int ByteStream::size() const
{
	return m_sizeOfData;
}

}
