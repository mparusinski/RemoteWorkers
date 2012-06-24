/* 
 
 RwClasses.h: Several useful general purpose macros
 
 As part of the RemoteWorkers program which creates a framework for remote
 management of laptops, desktop and servers. 
 
 Copyright (C) 2012 Remote Workers Project. All rights reserved.
 Created by Michal Parusinski <mparusinski@googlemail.com> on 21/06/2012.
 
 */

#ifndef _RWUTILS_RWGLOBAL_RWCLASSES_H_
#define _RWUTILS_RWGLOBAL_RWCLASSES_H_

namespace RwUtils {
    
    namespace RwGlobal {
        
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&);               \
        void operator=(const TypeName&)
        
    }
}

#endif // _RWUTILS_RWGLOBAL_RWCLASSES_H_
