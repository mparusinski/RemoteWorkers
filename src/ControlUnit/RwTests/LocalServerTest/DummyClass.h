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

#include "RwNetworking/RwCommandServerLocal.h"
#include "RwNetworking/RwCommandClientLocal.h"
#include "RwUtils/RwLog/RwCommon.h"

using namespace RwNetworking;
using namespace RwUtils::RwLog;

class DummyClass : public QWidget
{
    Q_OBJECT
    
public:
    
    explicit DummyClass(QWidget* parent = 0) : QWidget(parent) 
    { 
        m_server = new RwCommandServerLocal(this, "localServer");
        m_server->start();
        
        m_client = new RwCommandClientLocal(this, "localServer");
        m_button = new QPushButton(this);
        
        m_button->setText("Push button to connect");
        setWindowTitle("Dummy window");
        
        QObject::connect(m_button, SIGNAL(pressed()), this, SLOT(run()));
    }
    
    ~DummyClass()
    {
        delete m_client;
        delete m_server;
        delete m_button;
    }
    
    public slots:
    
    void run()
    {
        rwMessage() << "Button pressed" << endLine();
        m_client->connectToServer();
    }
    
private:
    RwCommandServerLocal* m_server;
    RwCommandClientLocal* m_client;
    
    QPushButton* m_button;
    
};

#endif // _RWTESTS_LOCALSERVERTEST_DUMMYCLASS_H_
