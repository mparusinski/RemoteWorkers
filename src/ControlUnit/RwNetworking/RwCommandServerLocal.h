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

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwNetworking {
 
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class represents a local server. This allows to interact with 
    ///        the software even outside the network
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandServerLocal : public RwCommandServerBase
    {
        Q_OBJECT
        
    public:
        RwCommandServerLocal(QObject* parent, const QString& serverName);
        virtual ~RwCommandServerLocal();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Starts listening for commands
        ////////////////////////////////////////////////////////////////////////////////
        virtual void start();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Close the server
        ////////////////////////////////////////////////////////////////////////////////
        virtual void stop();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Checks if the server is running
        ////////////////////////////////////////////////////////////////////////////////
        virtual bool isRunning() const;
        
    public slots:
        void processConnection();
        
    private:
        virtual void abstract() {}
        DISALLOW_COPY_AND_ASSIGN(RwCommandServerLocal);
        
        void init();

        QLocalServer* m_localServer;
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDSERVERLOCAL_H_
