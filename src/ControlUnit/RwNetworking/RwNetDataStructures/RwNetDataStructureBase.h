/* 

RwNetDataStructureBase.h: Defines a common interface to basic data structures

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 25/06/2012.

*/

#ifndef _RWNETWORKING_RWNETDATASTRUCTURES_RWNETDATASTRUCTUREBASE_H_
#define _RWNETWORKING_RWNETDATASTRUCTURES_RWNETDATASTRUCTUREBASE_H_

#include <QString>
#include <QDataStream>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwDataStructures/RwByteArray.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwNetDataStructures {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class is an interface to net data structures. This class is abstract
        ////////////////////////////////////////////////////////////////////////////////
        class RwNetDataStructureBase {
          
        public:
            RwNetDataStructureBase();
            virtual ~RwNetDataStructureBase();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Reads a reply from raw data
            /// \param[in]  rawData The raw data representing the CommandReply
            /// \return An error code representing the error occurred
            ////////////////////////////////////////////////////////////////////////////////
            virtual RwReturnType fromRawData(const RwDataStructures::RwByteArray &rawData) = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief Converts the request to raw data
            /// \param[out]  rawData The raw data representing the CommandRequest
            /// \return An error code representing the error occurred
            ////////////////////////////////////////////////////////////////////////////////
            virtual RwReturnType toRawData(RwDataStructures::RwByteArray& rawData) const = 0;
            
            
        private:
            // NOTHING
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWNETDATASTRUCTURES_RWNETDATASTRUCTUREBASE_H_
