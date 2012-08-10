/* 

RwDefines.h: General definitions about Remote Workers

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 24/06/2012.

*/

#ifndef _RWUTILS_RWGLOBAL_RWDEFINES_H_
#define _RWUTILS_RWGLOBAL_RWDEFINES_H_

#include <QtGlobal>

namespace RwUtils {
    
    namespace RwGlobal {
        
#define RW_VERSION 0.3
#define RW_COMMUNICATION_PORT 51234 // for now
#define RW_RESPONSE_DATA_FOLDER "./responseData"
#define RW_LISTWORKER_WORKER_NAME "ListAllWorkers"
        
#define RW_COMMAND_PIPE "RwRemoteWorkers_Command_Pipe"
        
#define RW_DEVICE_LOCAL_PIPE 0
#define RW_DEVICE_REMOTE_TCP 1
#define RW_DEVICE_REMOTE_SSL 2
        
        typedef quint16 RwDeviceConnectionType;
        
#define RW_LOCAL_SERVER_NAME "LocalRemoteWorkerServer"
        
    }
    
}

#endif // _RWUTILS_RWGLOBAL_RWDEFINES_H_
