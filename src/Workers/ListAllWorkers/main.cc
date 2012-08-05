/* 

main.cc: Point of entry of the ListAllWorkers worker

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 05/08/2012

*/

#include "Functions.h"

#include <QFileInfo>
#include <QDir>

int main(int argc, char* argv[])
{
  QFileInfo thisExecFileInfo(argv[0]);
  QString pathToDir = thisExecFileInfo.absoluteDir().absolutePath();

  // GET LIST OF WORKERS
  QStringList listOfWorkers;
  getListOfWorkers(listOfWorkers);
    
  // CREATE HTML FILE CONTENT
  QString htmlData;
  generateHTMLContent(listOfWorkers, htmlData);
    
  // WRITE CONTENT
  QString indexHTMLFile = pathToDir + "/output/index.html";
  writeDataToFile(htmlData, indexHTMLFile);
    
  return 0;
}
