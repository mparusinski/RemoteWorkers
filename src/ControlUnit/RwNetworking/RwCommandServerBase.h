/* 

RwCommandServerBase.h: Interface to the network socket

As part of the RemoteWorkers program which creates a ramework for remote
management of laptops,desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#ifndef _RWNETWORKING_RWCOMMANDSERVERBASE_H_
#define _RWNETWORKING_RWCOMMANDSERVERBASE_H_

#include <QString>

#include "RwUtils/RwProgramming/RwClasses.h"
#include "RwUtils/RwProgramming/RwReturn.h"

using namespace RwUtils::RwProgramming;

namespace RwNetworking {
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This abstract class is an interface for basic server functionality
    ///        required for the Command Server (listening for commands)
    ///        Should not be instantiated
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommandServerBase : public QObject {
        
        Q_OBJECT
        
    public:
        RwCommandServerBase(const QString& name);
        virtual ~RwCommandServerBase();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Starts listening for commands
        /// \return Return an error message accordingly
        ////////////////////////////////////////////////////////////////////////////////
        virtual RwReturnType listen() = 0;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Check if the server is listenting
        /// \return Return true if listening
        ////////////////////////////////////////////////////////////////////////////////
        virtual bool isListening() const = 0;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Close the server
        /// \return Return an error message accordingly
        ////////////////////////////////////////////////////////////////////////////////
        virtual RwReturnType close() = 0;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief  Returns the name of the server
        /// \return Return the name of the server
        ////////////////////////////////////////////////////////////////////////////////
        QString getServerName();
        
    protected:
        QString m_serverName;
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwCommandServerBase);
    };
    
}

#endif // _RWNETWORKING_RWCOMMANDSERVERBASE_H_
