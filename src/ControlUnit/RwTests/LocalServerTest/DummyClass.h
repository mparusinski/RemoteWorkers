/* 

DummyClass.h: Class that creates some QObject

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012.

*/

#ifndef _RWTESTS_LOCALSERVERTEST_DUMMYCLASS_H_
#define _RWTESTS_LOCALSERVERTEST_DUMMYCLASS_H_

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QThread>
#include <QInputDialog>

#include "RwNetworking/RwServers/RwCommandServerLocal.h"
#include "RwNetworking/RwClients/RwCommandClientLocal.h"
#include "RwUtils/RwLog/RwCommon.h"
#include "RwUtils/RwProfile/RwProfiler.h"

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
        
        m_currentReply = new RwNetDataStructures::RwCommandReply;
        
        m_mainLayout = new QVBoxLayout(this);
        
        m_workerNameDialog = new QHBoxLayout(this);
        m_workerNameLabel  = new QLabel(this);
        m_workerNameEdit   = new QLineEdit(this);
        
        m_orderNameDialog  = new QHBoxLayout(this);
        m_orderNameLabel   = new QLabel(this);
        m_orderNameEdit    = new QLineEdit(this);
        
        m_replyDialog      = new QHBoxLayout(this);
        m_replyFileList    = new QListWidget(this);
        m_replyTextView    = new QPlainTextEdit(this);
        
        m_argumentListDialog    = new QHBoxLayout(this);
        m_argumentsDropDownList = new QComboBox(this);
        m_argumentsAdd          = new QPushButton(this);
        m_argumentsRemove       = new QPushButton(this);
        
        m_timeLabel = new QLabel(this);

        m_button = new QPushButton(this);
        
        m_workerNameDialog->addWidget(m_workerNameLabel);
        m_workerNameDialog->addWidget(m_workerNameEdit);
        
        m_orderNameDialog->addWidget(m_orderNameLabel);
        m_orderNameDialog->addWidget(m_orderNameEdit);
        
        m_replyDialog->addWidget(m_replyFileList, 10);
        m_replyDialog->addWidget(m_replyTextView, 30);
        
        m_argumentListDialog->addWidget(m_argumentsDropDownList);
        m_argumentListDialog->addWidget(m_argumentsAdd);
        m_argumentListDialog->addWidget(m_argumentsRemove);
        
        m_mainLayout->addLayout(m_workerNameDialog);
        m_mainLayout->addLayout(m_orderNameDialog);
        m_mainLayout->addLayout(m_argumentListDialog);
        m_mainLayout->addWidget(m_button);
        m_mainLayout->addLayout(m_replyDialog);
        
        m_mainLayout->addWidget(m_timeLabel);

        m_workerNameLabel->setText("Worker name");
        m_orderNameLabel->setText("Order name");
        
        m_argumentsAdd->setText("Add argument");
        m_argumentsRemove->setText("Remove argument");
        
        m_timeLabel->setText(QString::number(0.0) += " ms");

        m_button->setText("Send request");
        setWindowTitle("Dummy window");
        
        m_replyTextView->setReadOnly(true);
        
        QObject::connect(m_button, SIGNAL(pressed()), this, SLOT(run()));
        QObject::connect(m_localClient, SIGNAL(replyReady()), this, SLOT(obtainedReply()));
        QObject::connect(m_replyFileList, SIGNAL(clicked(QModelIndex)), this, SLOT(changeReply(QModelIndex)));
        QObject::connect(m_argumentsAdd, SIGNAL(pressed()), this, SLOT(addArgument()));
        QObject::connect(m_argumentsRemove, SIGNAL(pressed()), this, SLOT(removeArgument()));
    }
    
    virtual ~DummyClass()
    {
        delete m_currentReply;
        // Should be handled by QT
    }
    
    public slots:
    
    void run()
    {
    	RwUtils::RwProfile::RwProfiler::startProfiler();
        m_localClient->connectToServer();
        
        QString workerName = m_workerNameEdit->text();
        QString order      = m_orderNameEdit->text();
    
        RwWorkerInterface::RwCommand::RwCommandPtr command(new RwCommand(order, m_argumentsList));
        RwNetDataStructures::RwCommandRequest request(workerName, command);
        
        m_localClient->sendRequest(request);
    }
    
    void obtainedReply()
    {
        m_localClient->getReply(*m_currentReply);
        
        m_replyFileList->clear();
        m_replyTextView->clear();
        
        if (m_currentReply->isError()) {
            rwError() << "An error has occurred when executing request and/or reading reply" << endLine();
            m_replyTextView->insertPlainText("An error has occurred when processing request");
        } else {
            const RwWorkerInterface::RwReply& actualReply =  m_currentReply->getReply();
            const RwWorkerInterface::RwReply::ByteArrays& arrays = actualReply.getRawData();
            const int numberOfReplies = arrays.length();
            for (int i = 0; i < numberOfReplies; ++i)
            {
                m_replyFileList->addItem(arrays[i].first);
            }
        }
        double time = RwUtils::RwProfile::RwProfiler::stopProfiler();
        m_timeLabel->setText(QString::number(time) + " ms");
    }
    
    void changeReply(const QModelIndex& index)
    {
        const int i = index.row();
        
        const RwWorkerInterface::RwReply& actualReply =  m_currentReply->getReply();
        const RwWorkerInterface::RwReply::ByteArrays& arrays = actualReply.getRawData();
        
        const QByteArray& rawData = arrays[i].second;
        const QString& text(rawData.data());
        
        m_replyTextView->clear();
        m_replyTextView->insertPlainText(text);
    }
    
    void addArgument()
    {
        QString argument = QInputDialog::getText(this, "Add argument dialog", "Write the argument you wish to add", QLineEdit::Normal);
        m_argumentsDropDownList->addItem(argument);
        m_argumentsList.push_back(argument);
    }
    
    void removeArgument()
    {
        const int currentIndex = m_argumentsDropDownList->currentIndex();
        m_argumentsDropDownList->removeItem(currentIndex);
        m_argumentsList.removeAt(currentIndex);
    }
    
private:
    RwClients::RwCommandClientLocal * m_localClient;
    QVBoxLayout* m_mainLayout;
    
    QHBoxLayout* m_workerNameDialog;
    QLabel* m_workerNameLabel;
    QLineEdit* m_workerNameEdit;
    
    QHBoxLayout* m_orderNameDialog;
    QLabel* m_orderNameLabel;
    QLineEdit* m_orderNameEdit;
    
    QHBoxLayout* m_argumentListDialog;
    QComboBox* m_argumentsDropDownList;
    QPushButton* m_argumentsRemove;
    QPushButton* m_argumentsAdd;
    QStringList m_argumentsList;
    
    QHBoxLayout *m_replyDialog;
    QListWidget *m_replyFileList;
    QPlainTextEdit *m_replyTextView;
    
    QLabel *m_timeLabel;

    RwNetDataStructures::RwCommandReply* m_currentReply;
    
    QPushButton* m_button;
    
};

#endif // _RWTESTS_LOCALSERVERTEST_DUMMYCLASS_H_
