/* 

ByteStream.cc: Captures a stream of bytes in an efficient way

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 21/06/2012

*/

#include "RwByteStream.h"

#include <cstring>

namespace  RwDataStructures
{
    RwByteStream::RwByteStream()
    {
        allocate(0);
    }
    
    RwByteStream::RwByteStream(const int dataSize)
    {
        allocate(dataSize);
    }
    
    RwByteStream::RwByteStream(const RwByteStream& other)
    {
        grab(other);
    }
    
    RwByteStream & RwByteStream::operator=(const RwDataStructures::RwByteStream &other)
    {
        if (this != &other)
        {
            discard();
            grab(other);
        }
        
        return *this;
    }
    
    RwByteStream::~RwByteStream()
    {
        discard();
    }
    
    void RwByteStream::reallocate(const int dataSize)
    {
        discard();
        allocate(dataSize);
    }
    
    void RwByteStream::free()
    {
        if (!unique())
        {
            detach();
        }
        
        if (allocated())
        {
            m_sizeOfData = 0;
            delete[] m_rawData;
        }
    }
    
    RwByteStream::RwByteType * RwByteStream::getRawData()
    {
        if (!unique())
        {
            detach();
        }
        
        return m_rawData;
    }
    
    int RwByteStream::size() const
    {
        return m_sizeOfData;
    }
    
    bool RwByteStream::allocated() const
    {
        return m_rawData != 0;
    }
    
    bool RwByteStream::held() const
    {
        return (*m_refCounter) != 0;
    }
    
    bool RwByteStream::unique() const
    {
        return (*m_refCounter) == 1;
    }
    
    void RwByteStream::grab(const RwByteStream& other)
    {
        m_sizeOfData = other.m_sizeOfData;
        m_rawData    = other.m_rawData;
        
        m_refCounter  = other.m_refCounter;
        *m_refCounter = *m_refCounter + 1;
    }
    
    void RwByteStream::discard()
    {
        *m_refCounter = *m_refCounter - 1;
        if (!held())
        {
            delete m_refCounter;
            if (allocated())
                delete[] m_rawData;
        }
    }
    
    void RwByteStream::allocate(const int dataSize)
    {
        m_sizeOfData = dataSize;
        m_rawData    = 0;
        
        m_refCounter  = new int;
        *m_refCounter = 1;
        
        if (dataSize > 0)
        {
            m_rawData = new RwByteType[m_sizeOfData];
        }
    }
    
    void RwByteStream::detach()
    {
        m_refCounter  = new int;
        *m_refCounter = 1;
        
        const RwByteType* other = m_rawData;
        m_rawData = new RwByteType[m_sizeOfData];
        memcpy(m_rawData, other, m_sizeOfData);
    }
}
