/* 
 
 RwConfiguration.h: Create the configuration for the worker management system
 
 As part of the RemoteWorkers program which creates a framework for remote
 management of laptops, desktop and servers. 
 
 Copyright (C) 2012 Remote Workers Project. All rights reserved.
 Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.
 
 */

#ifndef _RWUTILS_RWGLOBAL_RWCONFIGURATION_H_
#define _RWUTILS_RWGLOBAL_RWCONFIGURATION_H_

#include <QString>
#include <QHash>

#include "RwClasses.h"
#include "RwReturn.h"

namespace RwUtils
{
    
namespace RwGlobal
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
        /// \return     An error code
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType getWorkersPath(QString& workerPath);

        /////////////////////////////////////////////////////////////////////////////////
        /// \brief      Returns the path to the file containing the workers
        /// \param[out] workerListPath path to the workers list file
        /// \return     An error code
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType getWorkersListPath(QString& workerListPath);

        /////////////////////////////////////////////////////////////////////////////////
        /// \brief      Returns the path to the file containing the list of devices
        /// \param[out] deviceListPath path to device list file
        /// \return     An error code
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType getDeviceListPath(QString& deviceListPath);
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief      Returns the path to the file where the event log is saved too
        /// \param[out] eventLogPath path to event log file
        /// \return     An error code
        /////////////////////////////////////////////////////////////////////////////////
        RwReturnType getEventLogPath(QString& eventLogPath);

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

}

#endif // _RWUTILS_RWGLOBAL_RWCONFIGURATION_H_
