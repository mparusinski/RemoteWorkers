/* 

Reply.hpp: Captures the response of a worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 15/05/2012 Michal Parusinski <mparusinski@googlemail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 

*/

#include "Reply.hpp"

#include <QString>
//#include <LzmaLib.h>

#include "Worker.hpp"

using namespace std;

namespace WorkerInterface
{
    
    Reply::Reply()
    {
        m_empty = true;
    }
    
    Reply::~Reply()
    {
        
    }
    
    Reply::Reply(const ByteStreams & rawData)
    {
        m_rawData = rawData;
        m_empty = false;
    }
    
    bool Reply::empty() const
    {
        return m_empty;
    }
    
    const Reply::ByteStreams& Reply::getRawData() const
    {
        return m_rawData;
    }
    
    void Reply::setRawData(Reply::ByteStreams& rawData)
    {
        m_rawData = rawData;
    }
    
}
