/* 

RwCommandServerLocal.h: Emulates a local command server

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDSERVERLOCAL_H_
#define _RWNETWORKING_RWCOMMANDSERVERLOCAL_H_

#include "RwCommandServerBase.h"

#include <QString>
#include <QLocalServer>

#include "RwUtils/RwProgramming/RwClasses.h"
#include "RwUtils/RwProgramming/RwReturn.h"

namespace RwNetworking {
 
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class represents a local server. This allows to interact with 
    ///        the software even outside the network
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandServerLocal : public RwCommandServerBase
    {
        
    public:
        RwCommandServerLocal(const QString& serverName);
        virtual ~RwCommandServerLocal();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Starts listening for commands
        /// \return Return an error message accordingly
        ////////////////////////////////////////////////////////////////////////////////
        virtual RwReturnType listen();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Check if the server is listenting
        /// \return Return true if listening
        ////////////////////////////////////////////////////////////////////////////////
        virtual bool isListening() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Close the server
        /// \return Return an error message accordingly
        ////////////////////////////////////////////////////////////////////////////////
        virtual RwReturnType close();
        
    public slots:
        void simpleTest() const;
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwCommandServerLocal);
        
        void init();
        
        QLocalServer m_localServer;
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDSERVERLOCAL_H_
