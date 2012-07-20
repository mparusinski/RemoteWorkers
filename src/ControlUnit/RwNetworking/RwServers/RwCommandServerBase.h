/* 

RwCommandServerBase.h: Abstract base class for the functionality of the command server
                       The command server handles requests and sends back replies

As part of the RemoteWorkers program which creates a ramework for remote
management of laptops,desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 14/05/2012.

*/

#ifndef _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_
#define _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_

#include <QString>

#include <QLocalSocket>
#include <QTcpSocket>
#include <QSslSocket>

#include "RwUtils/RwGlobal/RwClasses.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwHistory/RwEventLog.h"

#include "../RwNetDataStructures/RwCommandRequest.h"
#include "../RwNetDataStructures/RwCommandReply.h"

using namespace RwUtils::RwGlobal;
using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwServers {
        
        ////////////////////////////////////////////////////////////////////////////////
        /// \brief This abstract class is a base class for all Command Server.
        ///        Command Servers handles requests and sends back responses.
        ///        The server should run in a separate thread.
        ////////////////////////////////////////////////////////////////////////////////
        template <typename SocketType>
        class RwCommandServerBase : public QObject {
            
        public:
            RwCommandServerBase(QObject* parent) : QObject(parent) { }
            virtual ~RwCommandServerBase() { }
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Starts the server which listens for requests.
            ////////////////////////////////////////////////////////////////////////////////
            virtual void start() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Stops the server which listens no more for requests
            ////////////////////////////////////////////////////////////////////////////////
            virtual void stop() = 0;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Checks if the server is currently running.
            ////////////////////////////////////////////////////////////////////////////////
            virtual bool isRunning() const = 0;

        protected:
            bool m_pendingConnection;
            SocketType* m_currentConnection;
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Process the data, the data coming in represents the request,
            ///         the data coming represents the response. Each in raw format.
            /// \param[in]  in  Represents the request in raw format
            /// \param[out] out Represents the response in raw format
            /// \return Returns an error code telling if any error did occur
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType processData(const QByteArray& in, QByteArray& out) const
            {
            	// READING REQUEST
            	RwNetDataStructures::RwCommandRequest request;
            	RwReturnType errorCode = request.fromRawData(in);

            	// CREATING REPLY
            	RwNetDataStructures::RwCommandReply commandReply;
            	errorCode = errorCode | executeRequest(request, commandReply);

            	commandReply.toRawData(out);

            	return errorCode;
            }
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Executes the request and return the response
            /// \param[in]  request  Represents the request
            /// \param[out] reply    Represents the response
            /// \return Returns an error code telling if any error did occur
            ////////////////////////////////////////////////////////////////////////////////
            RwReturnType executeRequest(const RwNetDataStructures::RwCommandRequest& request, RwNetDataStructures::RwCommandReply& reply) const
            {
            	RwReturnType errorCode = RW_NO_ERROR;
            	RwReply::RwReplyPtr realReply;
            	RwWorker::RwWorkerPtr worker;

            	errorCode = RwManagement::getInstance()->createWorker(request.getWorkerName(), worker);

            	if (errorCode != RW_NO_ERROR)
            		goto cut_through;

            	errorCode = worker->executeCommand(request.getCommand());

            	RwHistory::RwEventLog::getInstance()->workerExecutedCommand(worker, request.getCommand());

            	if (errorCode != RW_NO_ERROR)
            		goto cut_through;

            	errorCode = worker->getReply(realReply);

            	cut_through:

            	if ( errorCode != RW_NO_ERROR ) {
            		reply.setErrorCode(errorCode);
            	} else {
            		reply.setReply(realReply);
            	}

            	return errorCode;
            }
            
            ////////////////////////////////////////////////////////////////////////////////
            /// \brief  Processes the connection regardless of the type of socket
            ////////////////////////////////////////////////////////////////////////////////
            void abstractProcessConnection() const
            {
            	QObject::connect(m_currentConnection, SIGNAL(disconnected()),
            			         m_currentConnection, SLOT(deleteLater()));

            	while (m_currentConnection->bytesAvailable() < (int)sizeof(quint32)) // waiting for at least 32 bits of data
            		m_currentConnection->waitForReadyRead();

            	// RECEIVING DATA
            	QByteArray receivedData = m_currentConnection->readAll(); // This may be dangerous
            	QByteArray responseData;
            	RwReturnType errorCode = processData(receivedData, responseData);

            	// SENDING RAW DATA
            	//QByteArray responseContainerData;
            	//QDataStream out(&responseContainerData, QIODevice::WriteOnly);
            	//out << responseData.size();
            	//out << responseData;

            	m_currentConnection->write(responseData);
            }


        private:
            DISALLOW_COPY_AND_ASSIGN(RwCommandServerBase);
            
        };

    }
    
}

#endif // _RWNETWORKING_RWSERVERS_RWCOMMANDSERVERBASE_H_

