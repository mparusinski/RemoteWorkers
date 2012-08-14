/* 

Functions.cc: All the useful functions of ListAllWorkers worker

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 05/08/2012.

*/

#include "Functions.h"

#include <QFile>
#include <QTextStream>
#include <QDataStream>

#define ENDLINE '\n'

void getListOfWorkers(QStringList& listOfWorkers)
{
    const QString pathToWorkerList = "../ControlUnit/WorkersList.txt";
    QFile workerListFile(pathToWorkerList);
    
    if ( !workerListFile.open(QIODevice::ReadOnly | QIODevice::Text) ){
		exit(-1);
	}
    
	QTextStream in(&workerListFile);
    
	while ( !in.atEnd())
	{
		QString workerName;
		int type;
		QString dateString;
		// QStringList dateTokens;
        
		in >> workerName;
        
		if (workerName[0] == '#')
		{
			in.readLine();
			continue;
		}
        else if ( workerName.isEmpty() )
        {
			break;
		}
        
		in >> type;
		in >> dateString;
        
		//dateTokens = dateString.split("/");
        
		//int day = dateTokens[0].toInt();
		//int month = dateTokens[1].toInt();
		//int year = dateTokens[2].toInt();
        
		//QDate date(year, month, day);
        
		// m_listOfWorkers[workerName] = WorkerDescriptionType(static_cast<WorkerType>(type), date);
        
        listOfWorkers.push_back(workerName);
	}
    
	workerListFile.close();
}

void generateHTMLContent(const QStringList& listOfWorkers, QString& htmlData)
{
    QTextStream out(&htmlData, QIODevice::WriteOnly | QIODevice::Text);
    
    out << "<!DOCTYPE html>" << ENDLINE;
    out << "<html>" << ENDLINE;
    out << "<head>" << ENDLINE;
    out << "<meta charset=\"utf-8\" />" << ENDLINE;
    out << "<title>List of Workers</title>" << ENDLINE;
    out << "</head>" << ENDLINE;
    out << "<body>" << ENDLINE;
    out << "<ul>" << ENDLINE;
    
    const int numberOfWorkers = listOfWorkers.length();
    for (int i = 0;  i < numberOfWorkers; ++i)
    {
        const QString& currentWorkerName = listOfWorkers[i];
        if (currentWorkerName == QString(THIS_WORKER))
        {
            continue;
        }
        
        out << "<li>" << currentWorkerName << "</li>" << ENDLINE;
    }
    
    out << "</ul>" << ENDLINE;
    out << "</body>" << ENDLINE;
    out << "</html>" << ENDLINE;

    out.flush();
}

