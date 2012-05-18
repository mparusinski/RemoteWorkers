/* 

Command.hpp: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <string>
#include <vector>

using namespace std;

namespace WorkerInterface
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class encapsulate a command into a data structure which can be
///        passed to a worker.
////////////////////////////////////////////////////////////////////////////////
class Command
{

public:
	typedef vector<string> ArgumentsType;

	Command(const string& order, const vector<string>& arguments);
	virtual ~Command() { }

	/////////////////////////////////////////////////////////////////////////////////
	/// \brief     Return the order i.e the command the object represents
	/// \return    A string representing the command
	/////////////////////////////////////////////////////////////////////////////////
	string getOrder() const;

	/////////////////////////////////////////////////////////////////////////////////
	/// \brief     Returns the list of arguments the real command needs to receive
	/// \return    A list of arguments
	/////////////////////////////////////////////////////////////////////////////////
	vector<string> getArguments() const;

private:
	string m_order;
	vector<string> m_arguments;
};

}

#endif // _COMMAND_HPP_
