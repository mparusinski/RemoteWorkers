/* 

RwMessage.h: Logs messages to console, file ...

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWUTILS_RWLOG_RWMESSAGE_H_
#define _RWUTILS_RWLOG_RWMESSAGE_H_

#include "RwCommon.h"
#include "RwUtils/RwProgramming/RwClasses.h"
#include "RwMessagingManager.h"

namespace RwUtils {
    
    namespace RwLog {
        
        inline RwWriter rwMessage()
        {
            return RwWriter(RW_WRITER_MESSAGE);
        }
        
    }
    
}

#endif // _RWUTILS_RWLOG_RWMESSAGE_H_
