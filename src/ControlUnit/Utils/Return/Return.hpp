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
        
        typedef enum 
        {
            NO_ERROR,
            ERROR_GENERIC
            
        } ReturnType;
        
    }
    
}

#endif // _RETURN_
