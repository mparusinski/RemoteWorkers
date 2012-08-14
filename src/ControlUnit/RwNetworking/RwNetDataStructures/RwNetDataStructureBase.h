/* 

RwNetDataStructureBase.h: Defines a common interface to basic data structures used in networking

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 25/06/2012.

*/

#ifndef _RWNETWORKING_RWNETDATASTRUCTURES_RWNETDATASTRUCTUREBASE_H_
#define _RWNETWORKING_RWNETDATASTRUCTURES_RWNETDATASTRUCTUREBASE_H_

#include <QString>
#include <QDataStream>
#include <QByteArray>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This is an abstract interface to data structures used in networking.
        ////////////////////////////////////////////////////////////////////////////////
        class RwNetDataStructureBase {
          
        public:
            RwNetDataStructureBase();
            virtual ~RwNetDataStructureBase();
            
            virtual QString toString() const = 0;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwNetDataStructureBase);
            // NOTHING
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWNETDATASTRUCTURES_RWNETDATASTRUCTUREBASE_H_
