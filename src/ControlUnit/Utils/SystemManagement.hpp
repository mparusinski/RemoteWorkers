/* 

CrossPlatform.hpp: Handle cross platform stuff

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _SYSTEMMANAGEMENT_HPP_
#define _SYSTEMMANAGEMENT_HPP_

#include <string>
#include <vector>
#include <iostream>

#include <QProcess>
#include <QString>

using namespace std;

namespace Utils
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class contains a set of function to allow cross platform
///        functionality.
////////////////////////////////////////////////////////////////////////////////
class SystemManagement
{
public:

#define PATH_SEPERATOR "/";

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Executes a command in given directory with given arguments
	/// \param[in] directory	Name of the directory in which is placed command
	/// \param[in] command		Name of the command to be run
	/// \param[in] arguments	Name of the arguments to be passed to the command
	/// \return    Return 1 if success 0 otherwise
	////////////////////////////////////////////////////////////////////////////////
	static int executeCommand(
				const string& directory,
				const string& command,
				const vector<string>& arguments);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief      Function that returns the list of files in a given directory.
	///             The function mimics the "ls" unix command but only returns files
	/// \param[in]  directory	Directory in which we want to list all the files
	/// \param[out] files		List of the files in the directory
	////////////////////////////////////////////////////////////////////////////////
	static void getListOfFilesInDir(const string& directory, vector<string>& files);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief	    Function that returns the list of subdirectories in a directory
	/// \param[in]  directory	Directory in which we want to list all the directories
	/// \param[out] directories	List of all subdirectories in input directory
	////////////////////////////////////////////////////////////////////////////////
	static void getListOfDirsInDir(const string& directory, vector<string>& directories);

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Delete all the files given
	/// \param[in] files 	Files to be deleted
	////////////////////////////////////////////////////////////////////////////////
	static void deleteFiles(const vector<string>& files);

private:
	static void setSafeEnvironment(QProcessEnvironment& environment);

};

}

#endif //_SYSTEMMANAGEMENT_HPP_
