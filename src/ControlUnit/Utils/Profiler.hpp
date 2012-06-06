/* 

Profiler.hpp: Help perform performance measurement on software without relying on 3rd party software

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 19/05/2012.

*/

#ifndef _PROFILER_HPP_
#define _PROFILER_HPP_

#include <ctime>
#include <string>
#include <stack>

#include <QElapsedTimer>

using namespace std;

namespace Utils
{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is a utility class to help perform performance analysis of
///        the code without relying on external tools. Since this is an internal
///        profiler using C++ STL code it is not 100% reliable. It should be used
///        for simple quick profiling. For better results use a proper profiler
///        like Valgrind.
////////////////////////////////////////////////////////////////////////////////
class Profiler
{
public:
	typedef stack<QElapsedTimer> TimerTypes;

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Starts the profiler i.e checks the system clock and record the time
	////////////////////////////////////////////////////////////////////////////////
	static void startProfiler();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Stops the profiler i.e checks the system clock and returns the time taken
	////////////////////////////////////////////////////////////////////////////////
	static double stopProfiler();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Measure the time spent between when the profiler has been started
	///        and when it stops
	/// \return Time spent between start time and stop time in milliseconds
	////////////////////////////////////////////////////////////////////////////////
	static double timeElapsed();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief Outputs a profiling message which includes input message and time
	///        taken between start time and stop time in milliseconds
	/// \param[in] message	Message corresponding to the profiling measure did
	////////////////////////////////////////////////////////////////////////////////
	static void profile(const string& message);

private:
	static TimerTypes m_timers;
};

}

#endif // _PROFILER_HPP_
