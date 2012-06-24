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

#include "RwCommandRequest.h"
#include "RwCommandReply.h"
#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwDataStructures/RwByteArray.h"
#include "RwWorkerInterface/RwReply.h"

using namespace RwWorkerInterface;
using namespace RwUtils::RwGlobal;

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
        
        RwReturnType fromRawData(const RwDataStructures::RwByteArray& rawData, 
                                 RwCommandRequest& request) const;
        
        RwReturnType toRawData(const RwCommandReply& request, 
                               RwDataStructures::RwByteArray& rawData) const;
        
        RwReturnType executeRequest(const RwCommandRequest& request, RwReply& reply) const;
        
        void init();

        bool m_pendingConnection;
        QLocalServer* m_localServer;
        QLocalSocket* m_currentConnection;
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDSERVERLOCAL_H_
