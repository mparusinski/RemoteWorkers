/* 

RwCommand.h: Encapsulate a command

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 15/05/2012.

*/

#ifndef _RWWORKERINTERFACE_RWCOMMAND_H_
#define _RWWORKERINTERFACE_RWCOMMAND_H_

#include <QString>
#include <QStringList>
#include <QSharedPointer>

#include "RwUtils/RwGlobal/RwClasses.h"

namespace RwWorkerInterface
{
    
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief This class encapsulate a command into a data structure which can be
    ///        passed to a worker.
    ////////////////////////////////////////////////////////////////////////////////
    class RwCommand
    {
        
    public:
        typedef QSharedPointer<RwCommand> RwCommandPtr;
        
        RwCommand();
        RwCommand(const QString& order, const QStringList& arguments);
        virtual ~RwCommand() { }
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief     Return the order i.e the command the object represents
        /// \return    A string representing the command
        /////////////////////////////////////////////////////////////////////////////////
        const QString& getOrder() const;
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief     Sets the order of the command
        /// \param[in] order A string representing the order
        /////////////////////////////////////////////////////////////////////////////////
        void setOrder(const QString& order);
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief     Returns the list of arguments the real command needs to receive
        /// \return    A list of arguments
        /////////////////////////////////////////////////////////////////////////////////
        const QStringList& getArguments() const;
        
        /////////////////////////////////////////////////////////////////////////////////
        /// \brief     Sets the arguments of the command
        /// \param[in] arguments List of arguments
        /////////////////////////////////////////////////////////////////////////////////
        void setArguments(const QStringList& arguments);
        
    private:
        DISALLOW_COPY_AND_ASSIGN(RwCommand);
        QString m_order;
        QStringList m_arguments;
    };

}

#endif // _RWWORKERINTERFACE_RWCOMMAND_H_
