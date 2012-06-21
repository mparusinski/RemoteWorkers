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
        m_allocated  = false;
        m_rawData    = 0;
        m_sizeOfData = 0;
    }
    
    RwByteStream::RwByteStream(const int dataSize)
    {
        m_sizeOfData = dataSize;
        m_allocated  = false;
        m_rawData    = 0;
        
        if (dataSize > 0)
        {
            m_allocated  = true;
            m_rawData    = new RwByteType[m_sizeOfData];
        }
    }
    
    RwByteStream::RwByteStream(const RwByteStream& other)
    {
        m_allocated  = other.m_allocated;
        m_sizeOfData = other.m_sizeOfData;
        m_rawData    = new RwByteType[m_sizeOfData];
        memcpy(m_rawData, other.m_rawData, m_sizeOfData);
    }
    
    RwByteStream & RwByteStream::operator=(const RwDataStructures::RwByteStream &other)
    {
        if (this != &other)
        {
            // Allocate new memory
            RwByteType * newMemory = 0;
            if (other.m_allocated)
            {
                newMemory = new RwByteType[other.m_sizeOfData];
                memcpy(newMemory, other.m_rawData, other.m_sizeOfData);
            }
            
            // Delete old memory
            if (m_allocated)
            {
                delete[] m_rawData;
                m_rawData = 0;
            }
            
            // Assign
            m_allocated  = other.m_allocated;
            m_sizeOfData = other.m_sizeOfData;
            m_rawData    = newMemory;
        }
        
        return *this;
    }
    
    RwByteStream::~RwByteStream()
    {
        if (m_allocated)
            delete[] m_rawData;
    }
    
    void RwByteStream::reallocate(const int dataSize)
    {
        if (m_allocated)
            delete[] m_rawData;
        
        m_allocated  = false;
        m_sizeOfData = dataSize;
        m_rawData    = 0;
        
        if (dataSize > 0)
        {
            m_rawData   = new RwByteType[dataSize];
            m_allocated = true;
        }
    }
    
    void RwByteStream::free()
    {
        if (m_allocated)
        {
            m_allocated  = false;
            m_sizeOfData = 0;
            delete[] m_rawData;
        }
    }
    
    RwByteStream::RwByteType * RwByteStream::getRawData()
    {
        return m_rawData;
    }
    
    const RwByteStream::RwByteType * RwByteStream::getRawData() const
    {
        return m_rawData;
    }
    
    int RwByteStream::size() const
    {
        return m_sizeOfData;
    }
}
