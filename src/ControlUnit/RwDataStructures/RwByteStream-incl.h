/* 

ByteStream.cpp: Captures a stream of bytes in an efficient way

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#include "RwByteStream.h"

#include <cstring>

namespace RwDataStructures
{
    
    RwByteStream::RwByteStream(const int dataSize)
    {
        m_sizeOfData = dataSize;
        m_rawData = new RwByteType[m_sizeOfData];
        m_allocated = true;
    }
    
    RwByteStream::~RwByteStream()
    {
        if (m_allocated)
            delete[] m_rawData;
    }
    
    RwByteStream::RwByteStream(const RwByteStream & other)
    {
        m_allocated = other.m_allocated;
        m_sizeOfData = other.m_sizeOfData;
        if (m_allocated)
        {
            m_rawData = new RwByteType[m_sizeOfData];
            memcpy(m_rawData, other.m_rawData, m_sizeOfData);
        }
    }
    
    RwByteStream & RwByteStream::operator =(const RwByteStream & other)
    {
        if (this != &other)
        {
            const int sizeOfData  = other.m_sizeOfData;
            RwByteType * newRawData = 0;
            const bool allocated = other.m_allocated;
            if (allocated)
            {
                newRawData = new RwByteType[sizeOfData];
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
    
    void RwByteStream::reallocate(const int dataSize)
    {
        if (m_allocated)
            delete[] m_rawData;
        
        m_sizeOfData = dataSize;
        m_rawData = new RwByteType[m_sizeOfData];
        m_allocated = true;
    }
    
    void RwByteStream::free()
    {
        if (m_allocated)
            delete[] m_rawData;
        
        m_sizeOfData = 0;
        m_allocated = false;
    }
    
    const RwByteStream::RwByteType * RwByteStream::getRawData() const
    {
        return m_rawData;
    }
    
    RwByteStream::RwByteType * RwByteStream::getRawData()
    {
        return m_rawData;
    }
    
    int RwByteStream::size() const
    {
        return m_sizeOfData;
    }
    
}
