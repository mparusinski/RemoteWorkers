/* 

DummyClass.h: Class that creates some QObject

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWTESTS_LOCALSERVERTEST_DUMMYCLASS_H_
#define _RWTESTS_LOCALSERVERTEST_DUMMYCLASS_H_

#include <QString>
#include <QPushButton>
#include <QThread>

#include "RwNetworking/RwServers/RwCommandServerLocal.h"
#include "RwNetworking/RwClients/RwCommandClientLocal.h"
#include "RwUtils/RwLog/RwCommon.h"

using namespace RwNetworking;
using namespace RwUtils::RwLog;

#define SERVER_NAME "localServer"


class ServerThread : public QThread
{
public:
    ServerThread() { m_localServer = 0; }
    ~ServerThread() { delete m_localServer; }
    
    void run()
    {
        m_localServer = new RwServers::RwCommandServerLocal(0, SERVER_NAME);
        m_localServer->start();
        
        exec();
    }
    
private:
    RwServers::RwCommandServerLocal* m_localServer;
    
};

class DummyClass : public QWidget
{
    Q_OBJECT
    
public:
    
    explicit DummyClass(QWidget* parent = 0) : QWidget(parent) 
    { 
        m_localClient = new RwClients::RwCommandClientLocal(this, SERVER_NAME);
        m_button = new QPushButton(this);
        m_button->setText("Push button to connect");
        setWindowTitle("Dummy window");
        
        QObject::connect(m_button, SIGNAL(pressed()), this, SLOT(run()));
        QObject::connect(m_localClient, SIGNAL(replyReady()), this, SLOT(obtainedReply()));
    }
    
    ~DummyClass()
    {
        delete m_button;
    }
    
    public slots:
    
    void run()
    {
        rwMessage() << "Button pressed" << endLine();
        
        m_localClient->connectToServer();
        
        QString workerName = "SimpleTestWorker";
        QString order      = "SimpleTestWorker";
        QStringList arguments;
        RwNetDataStructures::RwCommandRequest request(workerName, RwWorkerInterface::RwCommand(order, arguments));
        m_localClient->sendRequest(request);
    }
    
    void obtainedReply()
    {
        RwNetDataStructures::RwCommandReply reply;
        m_localClient->getReply(reply);
        
        if (reply.isError()) {
            rwError() << "An error has occurred when processing request" << endLine();
        } else {
            const RwWorkerInterface::RwReply& actualReply =  reply.getReply();
            const RwWorkerInterface::RwReply::ByteArrays& arrays = actualReply.getRawData();
            const int numberOfReplies = arrays.length();
            for (int i = 0; i < numberOfReplies; ++i)
            {
                const QByteArray& rawData = arrays[i].second;
                const char* cString = rawData.data();
                rwMessage() << "File: " << arrays[i].first << endLine();
                rwMessage() << cString << endLine();
            }
        }
    }
    
private:
    RwClients::RwCommandClientLocal * m_localClient;
    QPushButton* m_button;
    
};

#endif // _RWTESTS_LOCALSERVERTEST_DUMMYCLASS_H_
