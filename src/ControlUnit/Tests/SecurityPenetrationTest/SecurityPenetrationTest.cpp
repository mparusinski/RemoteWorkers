/* 

SecurityPenetrationTest: Test designed to see if execution of workers is safe

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 21/05/2012

*/

#include <vector>
#include <string>

#include "WorkerInterface/Worker.hpp"
#include "WorkerInterface/Management.hpp"
#include "Utils/Logger.hpp"

#define TEST(condition, msg) do { if (condition) { \
	cout << "PASS: " << (msg) << " (which is bad!)" << endl; \
    } else { \
	cout << "FAIL: " << (msg) << " (which is good!)" << endl; }  } while(0);

using namespace std;
using namespace WorkerInterface;

int main(int argc, char *argv[])
{
	Utils::Logger::getInstance()->turnAllOn();

	bool allTest = true;

	// Testing if shell is executed instead of command

	// TEST 1
	bool shellTest1;
	{
		Worker worker("", ""); // empty path and command echo
		vector<string> arguments;
		arguments.push_back(string("Managed to execute shell!!!! FAILED"));
		Command command("echo", arguments);
		shellTest1 = worker.executeCommand(command);
		allTest = allTest && !shellTest1;

		TEST(shellTest1, "Shell test 1");
	}

	// TEST 2
	bool shellTest2;
	{
		Worker worker("echo ","");
		vector<string> arguments;
		arguments.push_back(string("Managed to execute shell!!!! FAILED"));
		Command command("", arguments);
		shellTest2 = worker.executeCommand(command);
		allTest = allTest && !shellTest2;

		TEST(shellTest2, "Shell test 2");
	}

	bool shellTest3;
	{
		Worker worker("", " echo");
		vector<string> arguments;
		arguments.push_back(string("Managed to execute shell!!!!! FAILED"));
		Command command("", arguments);
		shellTest3 = worker.executeCommand(command);
		allTest = allTest && !shellTest3;

		TEST(shellTest3, "Shell test 3");
	}

	// TESTING IF WE CAN EXECUTE DANGEROUS SYSTEM COMMANDS
	bool systemTest1;
	{
		Worker worker("/bin/sh ", " echo ");
		vector<string> arguments;
		arguments.push_back(string("Managed to execute a shell!!!!! FAILED"));
		Command command("", arguments);
		systemTest1 = worker.executeCommand(command);
		allTest = allTest && !systemTest1;

		TEST(systemTest1, "System test 1");
	}

	bool systemTest2;
	{
		Worker worker("/bin/echo ", " ");
		vector<string> arguments;
		arguments.push_back(string("Managed to execute a shell!!!!!!  FAILED"));
		Command command("", arguments);
		systemTest2 = worker.executeCommand(command);
		allTest = allTest && !systemTest2;

		TEST(systemTest2, "System test 2");
	}

	bool theGreatEscapeTest1;
	{
		string workerName = "; echo \"The great escape test succeeded\" ";
		Worker worker;
		Management::getInstance()->createWorker(workerName, worker);
		vector<string> arguments;
		Command command("", arguments);
		theGreatEscapeTest1 = worker.executeCommand(command);
		allTest = allTest && !theGreatEscapeTest1;

		TEST(theGreatEscapeTest1, "The great escape test");
	}

	bool theGreatEscapeTest2;
	{
		string workerName = "";
		Worker worker;
		Management::getInstance()->createWorker(workerName, worker);
		vector<string> arguments;
		string theGreatEscape = "; echo \"The great escape test succeeded\" ";
		Command command("", arguments);
		theGreatEscapeTest2 = worker.executeCommand(command);
		allTest = allTest && !theGreatEscapeTest2;

		TEST(theGreatEscapeTest2, "The great escape test 2");
	}

	bool theGreatEscapeTest3;
	{
		string workerName = "SimpleTestWorker";
		Worker worker;
		Management::getInstance()->createWorker(workerName, worker);
		string theGreatEscape = "; echo \"The great escape test succeeded\" ";
		vector<string> arguments;
		arguments.push_back(theGreatEscape);
		Command command(workerName, arguments);
		theGreatEscapeTest3 = worker.executeCommand(command);
		allTest = allTest && !theGreatEscapeTest3;

		TEST(theGreatEscapeTest3, "The great escape test 3");
	}

	return allTest;
}


