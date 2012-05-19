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
	cpu_timer timer;
	timer.start();
	m_timers.push(timer);
}

void Profiler::stopProfiler()
{
	m_timers.top().stop();
}

double Profiler::timeElapsed()
{
	const cpu_timer& timer = m_timers.top();
	m_timers.pop();

	const cpu_times& time = timer.elapsed();
	const nanosecond_type& diffNs = time.wall;
	return (double) diffNs / 1000000; // milliseconds
}

void Profiler::profile(const string& message)
{
	cout << "PROFILE: " << message << " took time " << timeElapsed() << " ms" << endl;
}

}
