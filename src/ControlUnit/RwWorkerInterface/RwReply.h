/* 

Reply.hpp: Captures the response of a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _REPLY_HPP_
#define _REPLY_HPP_

#include <QString>
#include <QPair>
#include <QList>

#include "Utils/Programming/Classes.h"
#include "DataStructures/ByteStream.h"

using namespace DataStructures;

namespace WorkerInterface
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class encapsulate the information of a worker reply. It contains
///        the raw data of a reply. This class should not be created directly,
///        but by a third party object like a worker.
////////////////////////////////////////////////////////////////////////////////
class Reply
{
public:
	typedef QList< QPair<QString, ByteStream> > ByteStreams;

	Reply();
	explicit Reply(const ByteStreams& rawData);
	virtual ~Reply();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Checks if the reply has data corresponding to a reply from a
	///            worker.
	/// \return    True if the reply has no data, false otherwise
	////////////////////////////////////////////////////////////////////////////////
	bool empty() const;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Returns the raw data representing the reply
	/// \return    Raw data representing the reply
	////////////////////////////////////////////////////////////////////////////////
	const ByteStreams& getRawData() const;
    
    ////////////////////////////////////////////////////////////////////////////////
	/// \brief        Returns the raw data representing the reply
	/// \param[in]    rawData Raw data representing the reply
	////////////////////////////////////////////////////////////////////////////////
    void setRawData(ByteStreams& rawData);

private:
    DISALLOW_COPY_AND_ASSIGN(Reply);
    
	bool m_empty;
	ByteStreams m_rawData;

};

}

#endif // _REPLY_HPP_
