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

#include "RwUtils/RwProgramming/RwClasses.h"
#include "RwDataStructures/RwByteArray.h"

using namespace RwDataStructures;

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
        typedef QList< QPair<QString, RwByteArray> > ByteArrays;
        
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
        /// \brief     Returns the raw data representing the reply
        /// \return    Raw data representing the reply
        ////////////////////////////////////////////////////////////////////////////////
        const ByteArrays& getRawData() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Returns the raw data representing the reply
        /// \return    Raw data representing the reply
        ////////////////////////////////////////////////////////////////////////////////
        ByteArrays& getRawData();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief        Returns the raw data representing the reply
        /// \param[in]    rawData Raw data representing the reply
        ////////////////////////////////////////////////////////////////////////////////
        void setRawData(ByteArrays& rawData);
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwReply);
        
        ByteArrays m_rawData;
        
    };
    
}

#endif // _RWWORKERINTERFACE_RWREPLY_H_
