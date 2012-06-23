/* 

RwError.h: Reports an error

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWUTILS_RWLOG_RWERROR_H_
#define _RWUTILS_RWLOG_RWERROR_H_

#include <QString>

#include "RwCommon.h"
#include "RwUtils/RwProgramming/RwClasses.h"
#include "RwMessagingManager.h"

namespace RwUtils {
    
    namespace RwLog {
        
        inline RwWriter _rwError(const char* fileName, 
                                 const char* funcName, 
                                 const int lineNum)
        {
            RwWriter machine(RW_WRITER_ERROR);
            machine << "(ERROR: " << fileName << " in " << funcName << " at " << lineNum << ") ";
            return machine;
        }
        
#define rwError() _rwError(__FILE__,(__func__), __LINE__)

    }
    
}

#endif // _RWUTILS_RWLOG_RWERROR_H_
