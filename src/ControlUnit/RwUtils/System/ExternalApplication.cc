/* 

ExternalApplication.cpp: Class dedicated into launching 3rd party applications

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 13/06/2012.

*/

#include "ExternalApplication.h"

#include <QProcess>

#include "Utils/Log/Logger.h"

namespace Utils
{
namespace System
{

ExternalApplication::ExternalApplication(const QString& pathToCommand, const QStringList& arguments)
{
	m_commandPath = pathToCommand;
	m_arguments   = arguments;
}

ExternalApplication::~ExternalApplication()
{

}

ReturnType ExternalApplication::execute() const
{
	QString errorMsg;

	QProcess externalProcess;
	// TODO: Sanitise environment
	QStringList environment = QProcess::systemEnvironment();
	externalProcess.setEnvironment(environment);

	externalProcess.start(m_commandPath, m_arguments);
	if (!externalProcess.waitForStarted())
	{
		QString errorMsg = m_commandPath;
		errorMsg += ": External process did not launch successfully";
		Utils::Log::Logger::getInstance()->error_msg(errorMsg);
		return RW_ERROR_NO_EXECUTION;
	}

	if (!externalProcess.waitForFinished(m_waitingTime))
	{
		errorMsg = m_commandPath;
		errorMsg += ": External process did not finish without errors or took too long to execute";
		Utils::Log::Logger::getInstance()->error_msg(errorMsg);

		externalProcess.terminate();
		return RW_ERROR_NO_EXECUTION;
	}

	QProcess::ExitStatus exitStatus = externalProcess.exitStatus();
	switch (exitStatus)
	{
	case QProcess::CrashExit:
		errorMsg  = m_commandPath;
		errorMsg += ": External process crashed";
		Utils::Log::Logger::getInstance()->error_msg(errorMsg);
		return RW_ERROR_EXECUTION_FAIL;
	default:
		return RW_NO_ERROR;
	}
}

}
}
