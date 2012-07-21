/* 

RwFileManagement.cc: Handles file operations

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "RwFileManagement.h"

#include "RwUtils/RwLog/RwCommon.h"

#include <QString>
#include <QDir>

#define PATH_SEPERATOR "/";

using namespace RwUtils::RwLog;

namespace RwUtils
{
    namespace RwSystem
    {
        
        RwReturnType RwFileManagement::getListOfFilesInDir(const QFileInfo& directory, 
                                                           QFileInfoList& files)
        {
            if (directory.exists() && directory.isDir())
            {
                const QDir directoryReal(directory.filePath());
                files = directoryReal.entryInfoList(QDir::Files);
                return RW_NO_ERROR;
            }
            else
            {
                rwError() << "Directory " << directory.filePath() 
                          << " has not been found" << endLine();
                return RW_ERROR_FILE_OR_DIR_NOT_FOUND;
            }
        }
        
        RwReturnType RwFileManagement::getListOfDirsInDir(const QFileInfo& directory, 
                                                          QFileInfoList& directories)
        {
            if (directory.exists() && directory.isDir())
            {
                const QDir directoryReal(directory.filePath());
                directories = directoryReal.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
                return RW_NO_ERROR;
            }
            else
            {
                rwError() << "Directory " << directory.filePath() 
                          << " has not been found" << endLine();
                return RW_ERROR_FILE_OR_DIR_NOT_FOUND;
            }
        }
        
        RwReturnType RwFileManagement::deleteFiles(const QFileInfoList& files)
        {
            const int numberOfFiles = files.size();
            
            for (int i = 0; i < numberOfFiles; ++i)
            {
                const QFileInfo& filePath = files[i];
                QDir fileDirectory = filePath.absoluteDir();
                fileDirectory.remove(filePath.fileName());
            }
            
            return RW_NO_ERROR;
        }
    }
}
