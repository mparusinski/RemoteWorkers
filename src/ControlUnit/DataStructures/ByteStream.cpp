/* 

ByteStream.cpp: Captures a stream of bytes in an efficient way

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "ByteStream.hpp"

#include <cstring>

namespace DataStructures
{

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
