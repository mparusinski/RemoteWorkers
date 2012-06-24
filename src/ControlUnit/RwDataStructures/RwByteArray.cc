/* 

ByteStream.cc: Captures a stream of bytes in an efficient way

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 21/06/2012

*/

#include "RwByteArray.h"

#include <cstring>

namespace  RwDataStructures
{
    RwByteArray::RwByteArray()
    {
        allocate(0);
    }
    
    RwByteArray::RwByteArray(const int dataSize)
    {
        allocate(dataSize);
    }
    
    RwByteArray::RwByteArray(const RwByteArray& other)
    {
        grab(other);
    }
    
    RwByteArray & RwByteArray::operator=(const RwDataStructures::RwByteArray &other)
    {
        if (this != &other)
        {
            discard();
            grab(other);
        }
        
        return *this;
    }
    
    RwByteArray::~RwByteArray()
    {
        discard();
    }
    
    void RwByteArray::reallocate(const int dataSize)
    {
        discard();
        allocate(dataSize);
    }
    
    void RwByteArray::free()
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
    
    RwByteArray::RwByteType * RwByteArray::getRawData()
    {
        if (!unique())
        {
            detach();
        }
        
        return m_rawData;
    }
    
    const RwByteArray::RwByteType * RwByteArray::getRawData() const
    {        
        return m_rawData;
    }
    
    void RwByteArray::setRawData(RwByteType *rawData, const int dataSize)
    {
        discard();
        allocate(dataSize);
        memcpy(m_rawData, rawData, dataSize);
    }
    
    int RwByteArray::size() const
    {
        return m_sizeOfData;
    }
    
    bool RwByteArray::allocated() const
    {
        return m_rawData != 0;
    }
    
    bool RwByteArray::held() const
    {
        return (*m_refCounter) != 0;
    }
    
    bool RwByteArray::unique() const
    {
        return (*m_refCounter) == 1;
    }
    
    void RwByteArray::grab(const RwByteArray& other)
    {
        m_sizeOfData = other.m_sizeOfData;
        m_rawData    = other.m_rawData;
        
        m_refCounter  = other.m_refCounter;
        *m_refCounter = *m_refCounter + 1;
    }
    
    void RwByteArray::discard()
    {
        *m_refCounter = *m_refCounter - 1;
        if (!held())
        {
            delete m_refCounter;
            if (allocated())
                delete[] m_rawData;
        }
    }
    
    void RwByteArray::allocate(const int dataSize)
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
    
    void RwByteArray::detach()
    {
        m_refCounter  = new int;
        *m_refCounter = 1;
        
        const RwByteType* other = m_rawData;
        m_rawData = new RwByteType[m_sizeOfData];
        memcpy(m_rawData, other, m_sizeOfData);
    }
}
