/* 
 
 Macros.h: Several useful general purpose macros
 
 As part of the RemoteWorkers program which creates a framework for remote
 management of laptops, desktop and servers. 
 
 Copyright (C) 2012 Remote Workers Project. All rights reserved.
 Created by Michal Parusinski <mparusinski@googlemail.com> on 21/06/2012.
 
 */

#ifndef _MACROS_
#define _MACROS_

namespace Utils {
    namespace Macros {
        
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&);               \
        void operator=(const TypeName&)
        
    }
}

#endif // _MACROS_
