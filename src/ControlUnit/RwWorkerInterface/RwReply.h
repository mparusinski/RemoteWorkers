/* 

RwReply.h: Captures the response of a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _RWWORKERINTERFACE_RWREPLY_H_
#define _RWWORKERINTERFACE_RWREPLY_H_

#include <QString>
#include <QPair>
#include <QList>
#include <QByteArray>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwWorkerInterface
{
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class encapsulate the information of a worker reply. It contains
    ///        the raw data of a reply. This class should not be created directly,
    ///        but by a third party object like a worker.
    ////////////////////////////////////////////////////////////////////////////////
    class RwReply
    {
    public:
        typedef QList< QPair<QString, QByteArray> > ByteArrays;
        
        RwReply();
        explicit RwReply(const ByteArrays& rawData);
        virtual ~RwReply();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Checks if the reply has data corresponding to a reply from a
        ///            worker.
        /// \return    True if the reply has no data, false otherwise
        ////////////////////////////////////////////////////////////////////////////////
        bool empty() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Return the raw data in the byte arrays
        ////////////////////////////////////////////////////////////////////////////////
        ByteArrays& getRawData();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Return the raw data in the byte arrays
        ////////////////////////////////////////////////////////////////////////////////
        const ByteArrays& getRawData() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Copies from another reply
        /// \param[in] other Other Reply
        ////////////////////////////////////////////////////////////////////////////////
        void copyFrom(const RwReply& other);
            
    private: 
        DISALLOW_COPY_AND_ASSIGN(RwReply);
        ByteArrays m_rawData;
        
    };
    
}

#endif // _RWWORKERINTERFACE_RWREPLY_H_
