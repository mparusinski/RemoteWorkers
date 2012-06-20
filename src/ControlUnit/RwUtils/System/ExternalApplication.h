/* 

ExternalApplication.hpp: Class dedicated into launching 3rd party applications

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 13/06/2012.

*/

#ifndef _EXTERNAL_APPLICATION_
#define _EXTERNAL_APPLICATION_

#include <QString>
#include <QProcess>

#include "Utils/Programming/Return.h"
#include "Utils/Programming/Classes.h"

using namespace Utils::Programming;

namespace Utils
{
    namespace System
    {
        
        class ExternalApplication
        {
        public:
            // ExternalApplication();
            explicit ExternalApplication(const QString& commandPath, const QStringList& arguments);
            virtual ~ExternalApplication();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Execute application represented by application
            /// \return    True if successfully executed, otherwise false
            ////////////////////////////////////////////////////////////////////////////////
            ReturnType execute(void) const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(ExternalApplication);
            
            static const int m_waitingTime = -1;
            QString m_commandPath;
            QStringList m_arguments;
        };
        
    }
}

#endif // _EXTERNAL_APPLICATION_
