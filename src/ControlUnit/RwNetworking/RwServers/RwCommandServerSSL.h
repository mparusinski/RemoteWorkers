/* 

 RwCommandServerSSL.h: Command Server over SSL/TLS. The command server handles requests and sends back replies


As part of the RemoteWorkers program which creates a ramework for remote
management of laptops,desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#ifndef _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERSSL_H_
#define _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERSSL_H_

#include "RwCommandServerBase.h"

#include <QSslSocket>

#include "RwUtils/RwGlobal/RwReturn.h"
#include "RwUtils/RwGlobal/RwClasses.h"

using namespace RwUtils::RwGlobal;

namespace RwNetworking {
    
    namespace RwServers {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This class implements a Command Server using SSL/TLS.
        ///        Command Servers handles requests and sends back responses.
        ///        The server should run in a seperate thread.
        ////////////////////////////////////////////////////////////////////////////////
        class RwCommandServerSSL : public RwCommandServerBase {
            
            Q_OBJECT
            
        public:
            
            RwCommandServerSSL(QObject* parent);
            virtual ~RwCommandServerSSL();
            
        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandServerSSL);
            
        };
        
    }
    
}

#endif // _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERSSL_H_
