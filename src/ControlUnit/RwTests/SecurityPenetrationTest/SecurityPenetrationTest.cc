/* 
 
 SecurityPenetrationTest: Test designed to see if execution of workers is safe
 
 As part of the Remote Workers Project which creates a framework for remote
 management of laptops, desktop and servers. 
 
 Copyright (C) 2012 Remote Workers Project. All rights reserved.
 Created by Michal Parusinski <mparusinski@googlemail.com> on 21/05/2012
 
 */

#include <QString>
#include <QStringList>
#include <cstdlib>
#include <cstdio>

#include "RwWorkerInterface/RwWorker.h"
#include "RwWorkerInterface/RwManagement.h"
#include "RwUtils/RwLog/RwMessagingManager.h"
#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

#define TEST(condition, msg) do { if (condition) { \
		rwInfo() << "PASS: " << (msg) << " (which is bad!)" << endLine(); \
} else { \
	rwInfo() << "FAIL: " << (msg) << " (which is good!)" << endLine(); }  } while(0);

using namespace RwWorkerInterface;

int main(int argc, char *argv[])
{
	RwMessagingManager::turnAllOn();
    
	bool allTest = true;
    
	// Testing if shell is executed instead of command
    
	// TEST 1
    
    
	bool shellTest1;
	{
		RwWorker worker(QFileInfo("")); // empty path and command echo
		QStringList arguments;
		arguments.push_back(QString("Managed to execute shell!!!! FAILED"));
		RwCommand::RwCommandPtr command(new RwCommand("echo", arguments));
		shellTest1 = worker.executeCommand(command);
		allTest = allTest && !shellTest1;
        
		TEST(shellTest1, "Shell test 1");
	}
    
	// TEST 2
	bool shellTest2;
	{
		RwWorker worker(QFileInfo("echo "));
		QStringList arguments;
		arguments.push_back(QString("Managed to execute shell!!!! FAILED"));
		RwCommand::RwCommandPtr command(new RwCommand("", arguments));
		shellTest2 = worker.executeCommand(command);
		allTest = allTest && !shellTest2;
        
		TEST(shellTest2, "Shell test 2");
	}
    
    
	// TESTING IF WE CAN EXECUTE DANGEROUS SYSTEM COMMANDS
	bool systemTest1;
	{
		RwWorker worker(QFileInfo("/bin/sh echo"));
		QStringList arguments;
		arguments.push_back(QString("Managed to execute a shell!!!!! FAILED"));
		RwCommand::RwCommandPtr command(new RwCommand("", arguments));
		systemTest1 = worker.executeCommand(command);
		allTest = allTest && !systemTest1;
        
		TEST(systemTest1, "System test 1");
	}
    
	bool systemTest2;
	{
		RwWorker worker(QFileInfo("/bin/echo "));
		QStringList arguments;
		arguments.push_back(QString("Managed to execute a shell!!!!!!  FAILED"));
		RwCommand::RwCommandPtr command(new RwCommand("", arguments));
		systemTest2 = worker.executeCommand(command);
		allTest = allTest && !systemTest2;
        
		TEST(systemTest2, "System test 2");
	}
    
	bool theGreatEscapeTest1;
	{
		QString workerName = "; echo \"The great escape test succeeded (not good)\" ";
		RwWorker::RwWorkerPtr worker;
		RwManagement::getInstance()->createWorker(workerName, worker);
		QStringList arguments;
		RwCommand::RwCommandPtr command(new RwCommand("", arguments));
		theGreatEscapeTest1 = worker->executeCommand(command);
		allTest = allTest && !theGreatEscapeTest1;
        
		TEST(theGreatEscapeTest1, "The great escape test");
	}
    
	bool theGreatEscapeTest2;
	{
		QString workerName = "";
		RwWorker::RwWorkerPtr worker;
		RwManagement::getInstance()->createWorker(workerName, worker);
		QStringList arguments;
		QString theGreatEscape = "; echo \"The great escape test succeeded (not good)\" ";
		RwCommand::RwCommandPtr command(new RwCommand("", arguments));
		theGreatEscapeTest2 = worker->executeCommand(command);
		allTest = allTest && !theGreatEscapeTest2;
        
		TEST(theGreatEscapeTest2, "The great escape test 2");
	}
    
	bool theGreatEscapeTest3;
	{
		QString workerName = "SimpleTestWorker";
		RwWorker::RwWorkerPtr worker;
		RwManagement::getInstance()->createWorker(workerName, worker);
		QString theGreatEscape = "; echo \"The great escape test succeeded (not good)\" ";
		QStringList arguments;
		arguments.push_back(theGreatEscape);
		RwCommand::RwCommandPtr command(new RwCommand(workerName, arguments));
		theGreatEscapeTest3 = worker->executeCommand(command);
		allTest = allTest && !theGreatEscapeTest3;
        
		TEST(theGreatEscapeTest3, "The great escape test 3");
	}
    
	bool theGreatEscapeTest4;
	{
		QString workerName = "SimpleTestWorker";
		RwWorker::RwWorkerPtr worker;
		RwManagement::getInstance()->createWorker(workerName, worker);
		QString theGreatEscape
        = "`VAR=\"The great escape test succeeded (not good)\"; echo SimpleTestWorker`";
		QStringList arguments;
		RwCommand::RwCommandPtr command(new RwCommand(theGreatEscape, arguments));
		theGreatEscapeTest4 = worker->executeCommand(command);
		allTest = allTest && !theGreatEscapeTest4;
        
		TEST(theGreatEscapeTest4, "The great escape test 4");
	}
    
	bool environmentTest;
	{
		QString workerName = "SecurityPenetrationTestWorker";
		RwWorker::RwWorkerPtr worker;
		RwManagement::getInstance()->createWorker(workerName, worker);
		QString commandName = "SanitizedEnvironment";
		QStringList arguments;
		RwCommand::RwCommandPtr command(new RwCommand(commandName, arguments));
        
		// changing the environment
		char* originalPath = getenv("HOME");
        const QString newPath_str = QString("HOME=/usr/bin");
		char* newPath = new char[newPath_str.length()]; 
        strcpy(newPath, newPath_str.toAscii().data());
		putenv(newPath);
        
		environmentTest = worker->executeCommand(command);
		allTest = allTest && !environmentTest;
        
		QString restorePath = "HOME=";
		restorePath += originalPath;
		char* restorePathStr = new char[restorePath.length()];
		strncpy(restorePathStr, restorePath.toAscii().data(), restorePath.length());
		putenv(restorePathStr);
        
		TEST(environmentTest, "The environment test was passed");
		delete[] restorePathStr;
	}
    
	return allTest;
}


