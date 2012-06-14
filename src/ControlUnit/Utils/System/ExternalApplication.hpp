/* 

ExternalApplication.hpp: Class dedicated into launching 3rd party applications

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 13/06/2012.

*/

#ifndef _EXTERNAL_APPLICATION_
#define _EXTERNAL_APPLICATION_

#include <QString>
#include <QProcess>

namespace Utils
{
namespace System
{

class ExternalApplication
{
public:
	// ExternalApplication();
	ExternalApplication(const QString& commandPath, const QStringList& arguments);
	virtual ~ExternalApplication();

	////////////////////////////////////////////////////////////////////////////////
	/// \brief     Execute application represented by application
	/// \return    True if successfully executed, otherwise false
	////////////////////////////////////////////////////////////////////////////////
	bool execute(void) const;

private:
	static const int m_waitingTime = -1;
	QString m_commandPath;
	QStringList m_arguments;
};

}
}

#endif // _EXTERNAL_APPLICATION_
