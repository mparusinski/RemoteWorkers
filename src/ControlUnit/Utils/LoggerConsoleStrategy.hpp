/* 

LoggerConsoleStrategy.hpp: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 16/05/2012 Michal Parusinski <mparusinski@googlemail.com>

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

#ifndef _LOGGERCONSOLESTRATEGY_HPP_
#define _LOGGERCONSOLESTRATEGY_HPP_

#include <iostream>
#include <string>

#include "LoggerStrategy.hpp"

using namespace std;

namespace Utils
{

class LoggerConsoleStrategy : public LoggerStrategy
{
public:

	LoggerConsoleStrategy();
	virtual ~LoggerConsoleStrategy();

	virtual void WriteToLog(const string& message) const;
	virtual void WriteToError(const string& message) const;

private:

};

}

#endif // _LOGGERCONSOLESTRATEGY_HPP_
