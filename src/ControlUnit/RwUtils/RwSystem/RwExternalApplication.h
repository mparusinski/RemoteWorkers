/* 

ExternalApplication.hpp: Class dedicated into launching 3rd party applications

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 13/06/2012.

*/

#ifndef _RWEXTERNAL_APPLICATION_
#define _RWEXTERNAL_APPLICATION_

#include <string>
#include <vector>

#include "RwUtils/RwProgramming/RwReturn.h"
#include "RwUtils/RwProgramming/RwClasses.h"

using namespace std;

using namespace RwUtils::RwProgramming;

namespace RwUtils
{
    namespace RwSystem
    {
        
        class RwExternalApplication
        {
        public:
            // ExternalApplication();
            explicit RwExternalApplication(const string& commandPath, const vector<string>& arguments);
            virtual ~RwExternalApplication();
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief     Execute application represented by application
            /// \return    True if successfully executed, otherwise false
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType execute(void) const;
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwExternalApplication);
            
            static const int m_waitingTime = -1;
            string m_commandPath;
            vector<string> m_arguments;
        };
        
    }
}

#endif // _EXTERNAL_APPLICATION_
