/* 

RwFileManagement.cpp: Handles file operations

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#include "RwFileManagement.h"

#include "RwUtils/RwLog/RwLogger.h"

#include <QString>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>

#define PATH_SEPERATOR "/";

namespace RwUtils
{
    namespace RwSystem
    {
        
        RwReturnType RwFileManagement::getListOfFilesInDir(const string& directory, vector<string>& files)
        {
            const QFileInfo qDirectory(directory.c_str());
            if (qDirectory.exists() && qDirectory.isDir())
            {
                const QDir directoryReal(qDirectory.absolutePath());
                QFileInfoList qFiles = directoryReal.entryInfoList(QDir::Files);
                
                const int numOfFiles = qFiles.length();
                files.reserve(numOfFiles);
                for (int i = 0; i < numOfFiles; ++i)
                {
                    files.push_back(qFiles[i].fileName().toStdString());
                }
                return RW_NO_ERROR;
            }
            else
            {
                string errorMessage = "Directory ";
                errorMessage += directory;
                errorMessage += " not found";
                
                RwUtils::RwLog::RwLogger::getInstance()->error_msg(errorMessage);
                return RW_ERROR_FILE_OR_DIR_NOT_FOUND;
            }
        }
        
        RwReturnType RwFileManagement::getListOfDirsInDir(const string& directory, 
                                                  vector<string>& directories)
        {
            const QFileInfo qDirectory(directory.c_str());
            if (qDirectory.exists() && qDirectory.isDir())
            {
                const QDir directoryReal(qDirectory.absolutePath());
                
                const QFileInfoList qDirectories = directoryReal.entryInfoList(QDir::Dirs);
                
                const int numOfDirs = qDirectories.length();
                directories.reserve(numOfDirs);
                for (int i = 0; i < numOfDirs; ++i)
                {
                    directories.push_back(qDirectories[i].fileName().toStdString());
                }
                
                return RW_NO_ERROR;
            }
            else
            {
                string errorMessage = "Directory ";
                errorMessage += directory;
                errorMessage += " not found";
                RwUtils::RwLog::RwLogger::getInstance()->error_msg(errorMessage);
                
                return RW_ERROR_FILE_OR_DIR_NOT_FOUND;
            }
        }
        
        RwReturnType RwFileManagement::deleteFiles(const vector<string>& files)
        {
            const int numberOfFiles = files.size();
            
            for (int i = 0; i < numberOfFiles; ++i)
            {
                const QFileInfo filePath(files[i].c_str());
                QDir fileDirectory = filePath.absoluteDir();
                fileDirectory.remove(filePath.filePath());
            }
            
            return RW_NO_ERROR;
        }
        
        RwReturnType RwFileManagement::getSizeOfFile(ifstream &inputFile, int &size)
        {
            if (!inputFile.is_open())
            {
                string errMsg = "Unable to read size of file as it is not open";
                RwUtils::RwLog::RwLogger::getInstance()->error_msg(errMsg);
                
                return RW_ERROR_GENERIC;
            }
            
            int current = inputFile.tellg();
            
            inputFile.seekg(0, ifstream::end);
            size = inputFile.tellg();
            inputFile.seekg(current);
            
            return RW_NO_ERROR;
        }
    }
}
