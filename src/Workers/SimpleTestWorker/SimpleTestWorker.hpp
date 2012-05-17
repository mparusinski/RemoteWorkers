/* 

SimpleTestWorker.hpp: Class file for simple test worker that generates a generic output

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#ifndef _SIMPLETESTWORKER_HPP_
#define _SIMPLETESTWORKER_HPP_

#include <string>

using namespace std;

class SimpleTestWorker
{
public:

	SimpleTestWorker();
	virtual ~SimpleTestWorker();

	static void createGenericHTMLFile(const string& fileName);

private:
};

#endif // _SIMPLETESTWORKER_HPP_
