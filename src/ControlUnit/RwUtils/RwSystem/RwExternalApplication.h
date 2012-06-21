/* 

RwExternalApplication.h: Class dedicated into launching 3rd party applications

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 13/06/2012.

*/

#ifndef _RWUTILS_RWSYSTEM_RWEXTERNAL_APPLICATION_H_
#define _RWUTILS_RWSYSTEM_RWEXTERNAL_APPLICATION_H_

#include <QString>
#include <QStringList>

#include "RwUtils/RwProgramming/RwReturn.h"
#include "RwUtils/RwProgramming/RwClasses.h"

using namespace RwUtils::RwProgramming;

namespace RwUtils
{
    namespace RwSystem
    {
        
        class RwExternalApplication
        {
        public:
            // ExternalApplication();
            explicit RwExternalApplication(const QString& commandPath, const QStringList& arguments);
            virtual ~RwExternalApplication();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Execute application represented by application
            /// \return    True if successfully executed, otherwise false
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType execute(void) const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwExternalApplication);
            
            static const int m_waitingTime = -1;
            QString m_commandPath;
            QStringList m_arguments;
        };
        
    }
}

#endif // _RWUTILS_RWSYSTEM_RWEXTERNAL_APPLICATION_H_
