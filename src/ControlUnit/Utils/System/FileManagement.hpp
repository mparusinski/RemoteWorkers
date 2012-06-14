/* 

CrossPlatform.hpp: Handle cross platform stuff

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _FILEMANAGEMENT_HPP_
#define _FILEMANAGEMENT_HPP_

#include <QProcess>
#include <QString>
#include <QFileInfo>
#include <QFileInfoList>

using namespace std;

namespace Utils
{
namespace System
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class contains a set of function to allow cross platform
///        functionality.
////////////////////////////////////////////////////////////////////////////////
class FileManagement
{
public:

#define PATH_SEPERATOR "/";

	////////////////////////////////////////////////////////////////////////////////
	/// \brief      Function that returns the list of files in a given directory.
	///             The function mimics the "ls" unix command but only returns files
	/// \param[in]  directory	Directory in which we want to list all the files
	/// \param[out] files		List of the files in the directory
	////////////////////////////////////////////////////////////////////////////////
	static void getListOfFilesInDir(const QFileInfo& directory, QFileInfoList& files);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief	    Function that returns the list of subdirectories in a directory
	/// \param[in]  directory	Directory in which we want to list all the directories
	/// \param[out] directories	List of all subdirectories in input directory
	////////////////////////////////////////////////////////////////////////////////
	static void getListOfDirsInDir(const QFileInfo& directory, QFileInfoList& directories);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Delete all the files given
	/// \param[in] files 	Files to be deleted
	////////////////////////////////////////////////////////////////////////////////
	static void deleteFiles(const QFileInfoList& files);

private:
	static void setSafeEnvironment(QProcessEnvironment& environment);

};

}
}

#endif //_FILEMANAGEMENT_HPP_
