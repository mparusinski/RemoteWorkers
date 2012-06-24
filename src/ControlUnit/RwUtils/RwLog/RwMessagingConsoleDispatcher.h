/* 

RwMessagingConsoleDispatcher.h: Console approach to logging

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 16/05/2012.

*/

#ifndef _RWUTILS_RWLOG_RWMESSAGINGCONSOLEDISPATCHER_H_
#define _RWUTILS_RWLOG_RWMESSAGINGCONSOLEDISPATCHER_H_

#include "RwMessagingDispatcherBase.h"

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwUtils
{
    namespace RwLog
    {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class implements a dispatcher that writes everything to the 
        ///        console. Should not be used directly.
        ////////////////////////////////////////////////////////////////////////////////
        class RwMessagingConsoleDispatcher : public RwMessagingDispatcherBase
        {
        public:
            
            RwMessagingConsoleDispatcher();
            virtual ~RwMessagingConsoleDispatcher();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a message
            /// \param[in] message	message to be displayed
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeMessage(const char* message) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a report an error
            /// \param[in] errorMessage	error message to be reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeError(const char* errorMessage) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a report a bug
            /// \param[in] debugMessage	debug message to be reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeDebug(const char* debugMessage) const;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Abstract method for writing a warning
            /// \param[in] warningMessage	warning message to be reported
            ////////////////////////////////////////////////////////////////////////////////
            virtual void writeWarning(const char* warningMessage) const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwMessagingConsoleDispatcher);
        };
        
    }
}

#endif // _RWUTILS_RWLOG_RWMESSAGINGCONSOLEDISPATCHER_H_
