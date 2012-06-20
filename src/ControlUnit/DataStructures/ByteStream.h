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

	explicit ByteStream(const int dataSize);
	explicit ByteStream(const ByteStream& other);
	virtual ~ByteStream();

	ByteStream & operator=(const ByteStream & other);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Reallocate memory to hold the given amount of data. It discards
	///            all memory previously held. If no memory allocated by object
	///            the function allocates simply new memory.
	/// \param[in] dataSize 	Number of bytes to allocate
	////////////////////////////////////////////////////////////////////////////////
	void reallocate(const int dataSize);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Free all the data allocated (if any).
	////////////////////////////////////////////////////////////////////////////////
	void free();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Return a pointer to the data allocated by the object
	/// \return    Pointer to the data allocated by the object
	////////////////////////////////////////////////////////////////////////////////
	ByteType* getRawData();
    
    ////////////////////////////////////////////////////////////////////////////////
	/// \brief     Return a pointer to the data allocated by the object
	/// \return    Pointer to the data allocated by the object
	////////////////////////////////////////////////////////////////////////////////
    const ByteType* getRawData() const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Returns the byte-size of the data allocated by the object
	/// \return	   Integer representing the number of bytes allocated
	////////////////////////////////////////////////////////////////////////////////
	int size() const;

private:
	bool m_allocated;
	int m_sizeOfData;
	ByteType* m_rawData;

};

}

#endif // _BYTESTREAM_HPP_