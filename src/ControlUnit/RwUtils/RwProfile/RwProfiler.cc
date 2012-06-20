/* 

Profiler.hpp: Help perform performance measurement on software without relying on 3rd party software

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 19/05/2012.

*/

#include "RwProfiler.h"

namespace RwUtils
{
    namespace RwProfile
    {
        
        RwProfiler::TimerTypes RwProfiler::m_timers = RwProfiler::TimerTypes();
        
        void RwProfiler::startProfiler()
        {
            QElapsedTimer timer;
            timer.start();
            m_timers.push(timer);
        }
        
        double RwProfiler::stopProfiler()
        {
            double time = timeElapsed();
            m_timers.pop();
            return time;
        }
        
        double RwProfiler::timeElapsed()
        {
            const QElapsedTimer& timer = m_timers.top();
            const qint64& time = timer.elapsed();
            return (double) time; // milliseconds
        }
        
        void RwProfiler::profile(const char* message)
        {
            printf("PROFILE: %s took time %f ms\n", message, stopProfiler());
        }
        
    }
}
