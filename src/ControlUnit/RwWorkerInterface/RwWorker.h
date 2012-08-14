/* 

RwWorker.h: Interface to a worker program

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _RWWORKERINTERFACE_RWWORKER_H_
#define _RWWORKERINTERFACE_RWWORKER_H_

#include <QDir>
#include <QString>
#include <QSharedPointer>

#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwReply.h"
#include "RwCommand.h"

using namespace RwUtils::RwGlobal;

namespace RwWorkerInterface
{
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class represents a worker. It can execute commands and produce
    ///        replies. This is the core class behind workers system.
    ////////////////////////////////////////////////////////////////////////////////
    class RwWorker {
        
    public:
    	typedef QSharedPointer<RwWorker> RwWorkerPtr;

        explicit RwWorker(const QDir& path);
        virtual ~RwWorker() { }
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief       Get the reply from worker (which is present of the disk). Reply
        ///              will be empty if the worker has not executed a command. After
        ///              each call this function remove all the content form the disk
        ///              corresponding to the reply. So this can be called only once.
        /// \param[out]  reply Reply corresponding to output of the worker.
        ////////////////////////////////////////////////////////////////////////////////
        RwReturnType getReply(RwReply::RwReplyPtr& reply);
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Worker will execute the command represented by the input and
        ///            and produce an output accessible from getReply().
        /// \param[in] command
        /// \return    Returns the appropriate error code
        ////////////////////////////////////////////////////////////////////////////////
        RwReturnType executeCommand(const RwCommand::RwCommandPtr& command);
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Returns the path to the worker (not the worker name)
        /// \return    Path to the worker, not the name
        ////////////////////////////////////////////////////////////////////////////////
        const QDir& getPath() const;
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Returns the name of the worker
        /// \return    Name of the worker
        ////////////////////////////////////////////////////////////////////////////////
        const QString& getWorkerName() const;
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwWorker);
        
        QString commandToString(const RwCommand& command) const;
        RwReturnType createReply(RwReply::RwReplyPtr& reply);
        void getOutputPath();
        void cleanOutput();
        
        bool m_outputPathComputed;
        
        QString m_workerName;
        QDir m_path;
        QDir m_outputPath;
        
        QByteArray m_outputData;
    };
    
}

#endif // _RWWORKERINTERFACE_RWWORKER_H_
