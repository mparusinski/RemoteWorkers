/* 
 
 RwConfiguration.h: Create the configuration for the worker management system
 
 As part of the RemoteWorkers program which creates a framework for remote
 management of laptops, desktop and servers. 
 
 Copyright (C) 2012 Remote Workers Project. All rights reserved.
 Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.
 
 */

#ifndef _RWWORKERINTERFACE_RWCONFIGURATION_H_
#define _RWWORKERINTERFACE_RWCONFIGURATION_H_

#include <QString>
#include <QHash>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

using namespace RwUtils::RwGlobal;

namespace RwWorkerInterface
{
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class is a singleton class which purpose is to retrieve
    ///        configuration data from the configuration file
    ////////////////////////////////////////////////////////////////////////////////
    class RwConfiguration
    {
    public:
        typedef QHash<QString, QString> ConfigurationsType;
        
        ~RwConfiguration();
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief     Returns an instance of the object (see Singleton pattern).
        ///            Most important function as it is the only way to access the object
        /// \return    The only possible instance of the object
        ////////////////////////////////////////////////////////////////////////////////
        static RwConfiguration* getInstance();
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief      Returns the path to the directory containing the workers
        /// \param[out] workerPath path to the workers
        /// \return     A string representing a file path
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType getWorkersPath(QString& workerPath);
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief      Returns the value of corresponding to the descriptor
        /// \param[in]  descriptor    Name of the configuration
        /// \param[out] configuration Value of the configuration
        /// \return     Configuration value for given descriptor
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType getConfiguration(const QString& descriptor, QString& configuration);
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwConfiguration);
        RwConfiguration();
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief     Reads the configuration file. This is already done at construction.
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType readConfiguration();
        
        bool m_configurationRead;
        ConfigurationsType m_configurations;
    };
    
}

#endif // _RWWORKERINTERFACE_RWCONFIGURATION_H_
