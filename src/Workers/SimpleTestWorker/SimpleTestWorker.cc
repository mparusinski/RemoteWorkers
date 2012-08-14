/* 

SimpleTestWorker.hpp: Class file for simple test worker that generates a generic output

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 17/05/2012.

*/

#include "SimpleTestWorker.h"

#include <cstdio>
#include <cstdlib>

#include <QDataStream>
#include <QFile>
#include <QString>
#include <QList>
#include <QPair>

SimpleTestWorker::SimpleTestWorker()
{

}

SimpleTestWorker::~SimpleTestWorker()
{

}

void SimpleTestWorker::createGenericHTMLFile()
{
  typedef QPair<QString, QByteArray> ElemType;
  typedef QList< ElemType > ArrayType;

  QFile fileOut;

  if ( !fileOut.open(stdout, QIODevice::WriteOnly) )
    {
      exit(-1);
    }

  QDataStream out(&fileOut);

  QString fileName("index.html");

  QByteArray fileData;

  fileData += "<!DOCTYPE html>\n";
  fileData += "<html>\n";
  fileData += "\t<head>\n";
  fileData += "\t\t<meta charset=\"utf-8\"/>\n";
  fileData += "\t\t<title>Generic web page</title>\n";
  fileData += "\t</head>\n\n";
  fileData += "\t<body>\n";
  fileData += "Simple message\n";
  fileData += "\t</body>\n";
  fileData += "</html>\n";

  ElemType elem(fileName, fileData);
  ArrayType array;
  array << elem;

  out << array;

  fileOut.flush();
  fileOut.close();
}
