/* 

RwExternalApplication.cc: Class dedicated into launching 3rd party applications

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 13/06/2012.

*/

#include "RwExternalApplication.h"

#include <QProcess>
#include <QString>

#include "RwUtils/RwLog/RwCommon.h"

using namespace RwUtils::RwLog;

namespace RwUtils
{
    namespace RwSystem
    {
        
        RwExternalApplication::RwExternalApplication(const QString& pathToCommand, 
                                                     const QStringList& arguments)
        {
            m_commandPath = pathToCommand;
            m_arguments   = arguments;
        }
        
        RwExternalApplication::~RwExternalApplication()
        {
            
        }
        
        RwReturnType RwExternalApplication::execute() const
        {            
            QProcess externalProcess;
            // TODO: Sanitise environment
            QStringList environment = QProcess::systemEnvironment();
            externalProcess.setEnvironment(environment);
            
            externalProcess.start(m_commandPath, m_arguments);
            if (!externalProcess.waitForStarted())
            {
                rwError() << m_commandPath 
                          << ": External process did not launch successfully" << endLine();
                return RW_ERROR_NO_EXECUTION;
            }
            
            if (!externalProcess.waitForFinished(m_waitingTime))
            {
                rwError() << m_commandPath << ": External process did not finish without errors or took too long to exectute" << endLine();
                externalProcess.terminate();
                return RW_ERROR_NO_EXECUTION;
            }
            
            QProcess::ExitStatus exitStatus = externalProcess.exitStatus();
            switch (exitStatus)
            {
                case QProcess::CrashExit:
                    rwError() << m_commandPath << ": External process crashed" << endLine();
                    return RW_ERROR_EXECUTION_FAIL;
                default:
                    return RW_NO_ERROR;
            }
        }
        
    }
}
