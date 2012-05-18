/* 

ByteStream.hpp: Captures a stream of bytes in an efficient way

As part of the Remote Workers project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _BYTESTREAM_HPP_
#define _BYTESTREAM_HPP_

namespace DataStructures
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class encapsulate raw data (used by the reply class). This is
///        used instead of a vector<char> since the latter is harder to be
///        written to by a file object. It is also of simple design.
////////////////////////////////////////////////////////////////////////////////
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
