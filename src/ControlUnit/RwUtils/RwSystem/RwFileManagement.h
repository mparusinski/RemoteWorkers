/* 

RwFileManagement.h: Handles file operations

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _RWUTILS_RWSYSTEM_RWFILEMANAGEMENT_H_
#define _RWUTILS_RWSYSTEM_RWFILEMANAGEMENT_H_

#include <QFileInfo>

#include "RwUtils/RwProgramming/RwReturn.h"

using namespace RwUtils::RwProgramming;

namespace RwUtils
{
    namespace RwSystem
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class contains a set of function to allow cross platform
        ///        functionality.
        ////////////////////////////////////////////////////////////////////////////////
        class RwFileManagement
        {
        public:
            
#define PATH_SEPERATOR "/";
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief      Function that returns the list of files in a given directory.
            ///             The function mimics the "ls" unix command but only returns files
            /// \param[in]  directory	Directory in which we want to list all the files
            /// \param[out] files		List of the files in the directory
            /// \return     Error message if an error occurs
            ////////////////////////////////////////////////////////////////////////////////
            static RwReturnType getListOfFilesInDir(const QFileInfo& directory, QFileInfoList& files);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief	    Function that returns the list of subdirectories in a directory
            /// \param[in]  directory	Directory in which we want to list all the directories
            /// \param[out] directories	List of all subdirectories in input directory
            /// \return     Error message if an error occurs
            ////////////////////////////////////////////////////////////////////////////////
            static RwReturnType getListOfDirsInDir(const QFileInfo& directory, 
                                                   QFileInfoList& directories);
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Delete all the files given
            /// \param[in] files 	Files to be deleted
            /// \return     Error message if an error occurs
            ////////////////////////////////////////////////////////////////////////////////
            static RwReturnType deleteFiles(const QFileInfoList& files);
            
        };
        
    }
}

#endif //_RWUTILS_RWSYSTEM_RWFILEMANAGEMENT_H_
