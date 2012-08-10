/* 

RwRemoteDevice.h: Encapsulate data for remote devices

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 26/07/2012.

*/

#include "RwRemoteDevice.h"

#include <QFile>
#include <QTextStream>
#include <QDataStream>

#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwSystem/RwFileManagement.h"

#include "RwWorkerInterface/RwReply.h"

#include "RwCommandClientLocal.h"
#include "RwCommandClientSSL.h"
#include "RwCommandClientTCP.h"

#include "RwCommandLocalPipeIn.h"

using namespace RwUtils::RwSystem;
using namespace RwUtils::RwLog;

namespace RwNetworking {
    
    namespace RwClients {
        
        RwRemoteDevice::RwRemoteDevice(QObject* parent, const QString& address, const RwRemoteDevice::RwDeviceConnectionType deviceConnection, quint16 portNumber) : QObject(parent)
        {
            m_address = address;
            m_deviceConnection = deviceConnection;
            m_init = false;
            m_portNumber = portNumber;
            m_client = 0;
        }
        
        RwRemoteDevice::~RwRemoteDevice()
        {
            if (m_client != 0)
            {
                delete m_client;
            }
        }
        
        QString& RwRemoteDevice::getAddress()
        {
            return m_address;
        }
        
        const QString& RwRemoteDevice::getAddress() const
        {
            return m_address;
        }
        
        RwRemoteDevice::RwDeviceConnectionType RwRemoteDevice::getType()
        {
            return m_deviceConnection;
        }
        
        void RwRemoteDevice::init()
        {
            if (m_client != 0)
            {
                delete m_client;
                m_client = 0;
            }
            
            switch (m_deviceConnection) {
                case RW_DEVICE_LOCAL_PIPE:
                    m_client = new RwCommandClientLocal(this, m_address);
                    break;
                case RW_DEVICE_REMOTE_TCP:
                    m_client = new RwCommandClientTCP(this, m_address, m_portNumber);
                    break;
                case RW_DEVICE_REMOTE_SSL:
                    m_client = new RwCommandClientSSL(this, m_address, m_portNumber);
                    break;
                default:
                    m_client = 0;
                    return; // uninitialised
            }
            
            m_init = true;
        }
        
        void RwRemoteDevice::connectToDevice()
        {
            if (!m_init)
                init();
            
            m_client->connectToServer();
        }
        
        void RwRemoteDevice::disconnectFromDevice()
        {
            m_client->disconnectFromServer();
        }
        
        bool RwRemoteDevice::sendRequest(const RwCommandRequest &request)
        {
            connectToDevice();
            if (m_client->sendRequest(request) != RW_NO_ERROR)
            {
                return false;
            }
            connect(m_client, SIGNAL(replyReady()), this, SLOT(receivedReply()));
            return true;
        }
        
        bool RwRemoteDevice::sendRequest(QByteArray request)
        {
            connectToDevice();
            if (m_client->sendRequest(request) != RW_NO_ERROR)
            {
                return false;
            }
            connect(m_client, SIGNAL(replyReady()), this, SLOT(receivedReply()));
            return true;
        }
        
        void RwRemoteDevice::getReply(RwCommandReply &reply) const
        {
            m_client->getReply(reply);
        }
        
        void RwRemoteDevice::receivedReply()
        {
            disconnect(m_client, SIGNAL(replyReady()), this, SLOT(receivedReply()));
            emit notifyOfReply();
        }
        
        void RwRemoteDevice::attachPipe() const
        {
            connect(RwCommandLocalPipeIn::getInstance(), SIGNAL(sendRequest(QByteArray)), this, SLOT(sendRequest(QByteArray)));
        }
        
        void RwRemoteDevice::detachPipe() const
        {
            disconnect(RwCommandLocalPipeIn::getInstance(), SIGNAL(sendRequest(QByteArray)), this, SLOT(sendRequest(QByteArray)));
        }
        
        void RwRemoteDevice::writeReply() const
        {
            RwCommandReply reply;
            m_client->getReply(reply);
            
            const QString responseDataFolder = RW_RESPONSE_DATA_FOLDER;
            
            // cleaning previous reply
            QFileInfoList files;
            RwFileManagement::getListOfFilesInDir(responseDataFolder, files);
            RwFileManagement::deleteFiles(files);
            
            if (reply.isError())
            {
                const RwReturnType errorCode = reply.getErrorCode();
                const QString errorFilePath = responseDataFolder + "/error_code.txt";
                
                QFile errorFile(errorFilePath);
                
                if ( !errorFile.open(QIODevice::WriteOnly | QIODevice::Text) )
                {
                    rwError() << "Unable to open error file" << endLine();
                    return;
                }
                
                QTextStream out(&errorFile);
                
                out << static_cast<int>(errorCode) << endLine();
                
                errorFile.close();
            }
            else
            {
                const RwWorkerInterface::RwReply::RwReplyPtr actualReply = reply.getReply();
                const RwWorkerInterface::RwReply::ByteArrays arrays = actualReply->getRawData();
                
                RwWorkerInterface::RwReply::ByteArrays::const_iterator iter;
                
                for (iter = arrays.begin(); iter != arrays.end(); ++iter)
                {
                    const QString& fileName = iter->first;
                    const QByteArray& fileRawData = iter->second;
                    
                    const QString filePath = responseDataFolder + '/' + fileName;
                    
                    QFile fileHandle(filePath);
                    
                    if ( !fileHandle.open(QIODevice::WriteOnly) )
                    {
                        rwError() << "Unable to open file " << fileName << ": skipping" << endLine();
                        continue;
                    }
                    
                    QDataStream out(&fileHandle);
                    
                    out << fileRawData;
                    
                    fileHandle.close();
                }
                
            }
        }
        
    }
    
}
