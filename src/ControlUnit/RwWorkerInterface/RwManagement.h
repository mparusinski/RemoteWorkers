/* 
 
 RwManagement.h: Manages workers
 
 As part of the RemoteWorkers program which creates a framework for remote
 management of laptops, desktop and servers. 
 
 Copyright (C) 2012 Remote Workers Project. All rights reserved.
 Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.
 
 */

#ifndef _RWWOKRERINTERFACE_RWMANAGEMENT_H_
#define _RWWOKRERINTERFACE_RWMANAGEMENT_H_

#include <QFileInfo>
#include <QFileInfoList>

#include "RwUtils/RwGlobal/RwClasses.h"

#include "RwWorker.h"
#include "RwReply.h"

namespace RwWorkerInterface
{
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class is a singleton class which purpose is to manage workers.
    ///        It provides a interface to the workers by creating them on demand,
    ///        listing them and other.
    ////////////////////////////////////////////////////////////////////////////////
    class RwManagement
    {
    public:
        virtual ~RwManagement();
        static RwManagement* getInstance();
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief      Create the worker with given name. The function resolves the path
        ///             to the worker
        /// \param[in]  workerName	Name of the worker
        /// \param[out] worker      The worker we wish to create
        /// \return     returns true if successfully created worker
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType createWorker(const QString& workerName, RwWorker& worker);
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief     List all available workers in default path
        /// \return    List of worker names (not a list of workers)
        /////////////////////////////////////////////////////////////////////////////////
        const QFileInfoList& listAvailableWorkers();
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwManagement);
        RwManagement();
        
        inline RwReturnType init();
        
        inline RwReturnType getListOfWorkers();
        
        QFileInfo m_pathToWorkers;
        QFileInfoList m_availableWorkers;
    };
    
}

#endif // _RWWOKRERINTERFACE_RWMANAGEMENT_H_
