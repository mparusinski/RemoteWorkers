/* 

Return.hpp: Return error message

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/06/2012.

*/

#ifndef _RETURN_
#define _RETURN_

namespace Utils {
    
    namespace Return{
        
        typedef unsigned int ReturnType;
        
#define RW_NO_ERROR 0x0
#define RW_ERROR_GENERIC 0x1
#define RW_ERROR_NO_WORKER 0x2
#define RW_ERROR_NO_REPLY 0x4
#define RW_ERROR_NO_EXECUTION 0x8
#define RW_ERROR_EXECUTION_FAIL 0x10
        
        inline ReturnType combine(const ReturnType& ret1, 
                                  const ReturnType& ret2)
        {
            return ret1 | ret2;
        }
        
    }
    
}

#endif // _RETURN_
