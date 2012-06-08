/* 

Worker.hpp: Interface to a worker program

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers.

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _WORKER_HPP_
#define _WORKER_HPP_

#include <QString>
#include <QFileInfo>

#include "Reply.hpp"
#include "Command.hpp"

using namespace std;

namespace WorkerInterface
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents a worker. It can execute commands and produce
///        replies. This is the core class behind workers system.
////////////////////////////////////////////////////////////////////////////////
class Worker {

public:
	Worker();
	Worker(const QFileInfo& path);
	virtual ~Worker() { }

	////////////////////////////////////////////////////////////////////////////////
	/// \brief       Get the reply from worker (which is present of the disk). Reply
	///              will be empty if the worker has not executed a command. After
	///              each call this function remove all the content form the disk
	///              corresponding to the reply. So this can be called only once.
	/// \param[out]  reply Reply corresponding to output of the worker.
	////////////////////////////////////////////////////////////////////////////////
	void getReply(Reply& reply) const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Worker will execute the command represented by the input and
	///            and produce an output accessible from getReply().
	/// \param[in] command
	/// \return    true if successful, false otherwise
	////////////////////////////////////////////////////////////////////////////////
	bool executeCommand(const Command& command) const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Returns the path to the worker (not the worker name)
	/// \return    Path to the worker, not the name
	////////////////////////////////////////////////////////////////////////////////
	const QFileInfo& getPath() const;

private:
	QString commandToString(const Command& command) const;
	void createReply(Reply& reply) const;
	void getOutputPath();
	void cleanOutput() const;

	QFileInfo m_path;
	QFileInfo m_outputPath;
};

}

#endif // _WORKER_HPP_
