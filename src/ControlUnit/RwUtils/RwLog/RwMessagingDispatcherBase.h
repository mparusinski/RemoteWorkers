/* 

RwMessageDispatcherBase.h: Set of basic functions to handle messaging (ABSTRACT)

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _RWUTILS_RWLOG_RWMESSAGINGDISPATCHERBASE_H_
#define _RWUTILS_RWLOG_RWMESSAGINGDISPATCHERBASE_H_

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class is the core class handling messaging. It provide an 
        ///        interface to messaing in general. Should not be use directly.
        ////////////////////////////////////////////////////////////////////////////////
        class RwMessagingDispatcherBase
        {
        public:
            
            RwMessagingDispatcherBase();
            virtual ~RwMessagingDispatcherBase();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a message
            /// \param[in] message	message to be displayed
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeMessage(const char* message) const = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a report an error
            /// \param[in] errorMessage	error message to be reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeError(const char* errorMessage) const = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a report a bug
            /// \param[in] debugMessage	debug message to be reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeDebug(const char* debugMessage) const = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a warning
            /// \param[in] warningMessage	warning message to be reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeWarning(const char* warningMessage) const = 0;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwMessagingDispatcherBase);
        };
        
    }
}

#endif // _RWUTILS_RWLOG_RWMESSAGINGDISPATCHERBASE_H_
