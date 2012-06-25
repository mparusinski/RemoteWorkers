/* 

RwReturn.h: Return error message

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/06/2012.

*/

#ifndef _RWUTILS_RWGLOBAL_RWRETURN_H_
#define _RWUTILS_RWGLOBAL_RWRETURN_H_

#include <QMap>
#include <QString>

#include "stdint.h"

namespace RwUtils {
    
    namespace RwGlobal {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \typedef RwReturnType Represents an error code
        /// \brief Error code to signal error if present. I aim to push the error 
        ///        messages upwards to the remote client.
        ////////////////////////////////////////////////////////////////////////////////
        typedef uint32_t RwReturnType;
        
#define RW_NO_ERROR 0x0
#define RW_ERROR_GENERIC 0x1
#define RW_ERROR_NO_WORKER 0x2
#define RW_ERROR_NO_REPLY 0x4
#define RW_ERROR_NO_EXECUTION 0x8
#define RW_ERROR_EXECUTION_FAIL 0x10
#define RW_ERROR_FILE_OR_DIR_NOT_FOUND 0x20
#define RW_ERROR_FILE_NOT_READ 0x40
#define RW_ERROR_SERVER_NOT_STARTED 0x80
#define RW_ERROR_SERVER_ALREADY_STARTED 0x100
#define RW_ERROR_READING_NETWORK_MESSAGE 0x200
#define RW_ERROR_NO_CONNECTION 0x400
        
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief Combines two error codes into one.
        ////////////////////////////////////////////////////////////////////////////////
        inline RwReturnType combine(const RwReturnType& ret1, 
                                    const RwReturnType& ret2)
        {
            return ret1 | ret2;
        }
        
//        inline char* returnTypetoString(const RwReturnType errorCode)
//        {
//            switch (errorCode)
//            {
//                case RW_NO_ERROR:
//                    return "NO ERROR";
//                case RW_ERROR_GENERIC:
//                    return "UNKNOWN ERROR";
//                case RW_ERROR_NO_WORKER:
//                    return "NO SUCH WORKER";
//                case RW_ERROR_NO_REPLY:
//                    return "NO REPLY";
//                case RW_ERROR_NO_EXECUTION:
//                    return "COMMAND DID NOT EXECUTE";
//                case RW_ERROR_EXECUTION_FAIL:
//                    return "COMMAND DID NOT EXECUTE PROPERLY";
//                case RW_ERROR_FILE_OR_DIR_NOT_FOUND:
//                    return "FILE OR DIRECTORY WAS NOT FOUND";
//                case RW_ERROR_FILE_NOT_READ:
//                    return "FILE WAS NOT READ";
//                case RW_ERROR_SERVER_NOT_STARTED:
//                    return "SERVER DID NOT START";
//                case RW_ERROR_SERVER_ALREADY_STARTED:
//                    return "SERVER ALREADY STARTED";
//                case RW_ERROR_READING_NETWORK_MESSAGE:
//                    return "ERROR WHEN READING MESSAGE FROM NETWORK";
//                case RW_ERROR_NO_CONNECTION:
//                    return "NO CONNECTION ESTABLISHED";
//                default:
//                    return "FUNCTION TO STRING DOES NOT COVER ALL CASES. CONTACT DEVELOPPERS";
//            }
//        }
        
    }
    
}

#endif // _RWUTILS_RWGLOBAL_RWRETURN_H_
