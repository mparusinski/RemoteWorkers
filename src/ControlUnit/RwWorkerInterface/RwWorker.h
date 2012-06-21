/* 

RwWorker.h: Interface to a worker program

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _RWWORKERINTERFACE_RWWORKER_H_
#define _RWWORKERINTERFACE_RWWORKER_H_

#include <QFileInfo>
#include <QString>

#include "RwUtils/RwProgramming/RwReturn.h"
#include "RwUtils/RwProgramming/RwClasses.h"

#include "RwReply.h"
#include "RwCommand.h"

using namespace RwUtils::RwProgramming;

namespace RwWorkerInterface
{
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class represents a worker. It can execute commands and produce
    ///        replies. This is the core class behind workers system.
    ////////////////////////////////////////////////////////////////////////////////
    class RwWorker {
        
    public:
        RwWorker();
        explicit RwWorker(const QFileInfo& path);
        virtual ~RwWorker() { }
        
        RwWorker(const RwWorker& otherWorker);
        RwWorker& operator=(const RwWorker& otherWorker);
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief       Get the reply from worker (which is present of the disk). Reply
        ///              will be empty if the worker has not executed a command. After
        ///              each call this function remove all the content form the disk
        ///              corresponding to the reply. So this can be called only once.
        /// \param[out]  reply Reply corresponding to output of the worker.
        ////////////////////////////////////////////////////////////////////////////////
        RwReturnType getReply(RwReply& reply) const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Worker will execute the command represented by the input and
        ///            and produce an output accessible from getReply().
        /// \param[in] command
        /// \return    Returns the appropriate error code
        ////////////////////////////////////////////////////////////////////////////////
        RwReturnType executeCommand(const RwCommand& command) const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Returns the path to the worker (not the worker name)
        /// \return    Path to the worker, not the name
        ////////////////////////////////////////////////////////////////////////////////
        const QFileInfo& getPath() const;
        
    private:
        
        QString commandToString(const RwCommand& command) const;
        void createReply(RwReply& reply) const;
        void getOutputPath();
        void cleanOutput() const;
        
        QFileInfo m_path;
        QFileInfo m_outputPath;
    };
    
}

#endif // _RWWORKERINTERFACE_RWWORKER_H_
