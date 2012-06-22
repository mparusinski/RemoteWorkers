/* 

RwByteArray.h: Captures a stream of bytes in an efficient way

As part of the Remote Workers project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _RWDATASTRUCTURES_RWBYTEARRAY_H_
#define _RWDATASTRUCTURES_RWBYTEARRAY_H_

namespace RwDataStructures
{
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class encapsulate raw data (used by the reply class). This is
    ///        used instead of a vector<char> since the latter is harder to be
    ///        written to by a file object. It is also of simple design.
    ////////////////////////////////////////////////////////////////////////////////
    class RwByteArray
    {
    public:
        typedef char RwByteType;
        
        RwByteArray();
        explicit RwByteArray(const int dataSize);
        explicit RwByteArray(const RwByteArray& other);
        virtual ~RwByteArray();
        
        RwByteArray & operator=(const RwByteArray & other);
        
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
        RwByteType* getRawData();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Returns the byte-size of the data allocated by the object
        /// \return	   Integer representing the number of bytes allocated
        ////////////////////////////////////////////////////////////////////////////////
        int size() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Check if the object has memory allocated
        /// \return	   True if some bytes have been allocated
        ////////////////////////////////////////////////////////////////////////////////
        bool allocated() const;
        
    private:
        inline bool held() const;
        
        inline bool unique() const;
        
        inline void grab(const RwByteArray & other);
        
        inline void discard();
        
        inline void allocate(const int dataSize);
        
        inline void detach();
        
        int  m_sizeOfData;
        mutable int* m_refCounter;
        RwByteType* m_rawData;
        
    };
    
}

#endif // _RWDATASTRUCTURES_RWBYTEARRAY_H_
