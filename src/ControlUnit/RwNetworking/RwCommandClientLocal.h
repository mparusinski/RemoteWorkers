/* 

RwCommandClientLocal.h: Client for RwCommandServerLocal

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 23/06/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDCLIENTLOCAL_H_
#define _RWNETWORKING_RWCOMMANDCLIENTLOCAL_H_

#include <QObject>

#include <QString>
#include <QLocalSocket>

#include "RwUtils/RwProgramming/RwClasses.h"

namespace RwNetworking  {
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class represents a local client. This allows to interact with 
    ///        the server even outside the network. Use it with RwCommandServerLocal
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandClientLocal : public QObject {
        
        Q_OBJECT
        
    public:
        RwCommandClientLocal(QObject* parent, const QString& serverName);
        ~RwCommandClientLocal();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Connects to server
        ////////////////////////////////////////////////////////////////////////////////
        void connectToServer();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Disconnects from server
        ////////////////////////////////////////////////////////////////////////////////
        void disconnectFromServer();
        
    public slots:
        void clientConnected();
        void clientDisconnected();
        void readReady();
        void clientError(QLocalSocket::LocalSocketError socketError);
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwCommandClientLocal);
        
        QString m_serverName;
        QLocalSocket* m_localSocket;
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDCLIENTLOCAL_H_
