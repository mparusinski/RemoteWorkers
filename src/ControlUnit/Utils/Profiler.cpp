/* 

Profiler.hpp: Help perform performance measurement on software without relying on 3rd party software

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 19/05/2012.

*/

#include "Profiler.hpp"

#include <iostream>

namespace Utils
{

Profiler::TimerTypes Profiler::m_timers = Profiler::TimerTypes();

void Profiler::startProfiler()
{
	QElapsedTimer timer;
	timer.start();
	m_timers.push(timer);
}

double Profiler::stopProfiler()
{
	double time = timeElapsed();
	m_timers.pop();
	return time;
}

double Profiler::timeElapsed()
{
	const QElapsedTimer& timer = m_timers.top();
	const qint64& time = timer.elapsed();
	return (double) time; // milliseconds
}

void Profiler::profile(const string& message)
{
	cout << "PROFILE: " << message << " took time " << stopProfiler() << " ms" << endl;
}

}
