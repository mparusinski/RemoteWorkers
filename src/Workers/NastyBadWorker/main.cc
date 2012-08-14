/* 

main.cc: Worker that purposefully works poorly

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 13/07/2012

*/

#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QDataStream>
#include <QList>
#include <QPair>
#include <QByteArray>

typedef QPair<QString, QByteArray> ElemType;
typedef QList<ElemType> ArrayType;

void generateFibonaciText(const int number, QString& outputText)
{
    qint64 a = 0;
    qint64 b = 1;
    outputText.clear();
    for (int i = 0; i < number; ++i)
    {
        outputText += QString::number(a) + '\n';
        qint64 tmp = a;
        a = b;
        b = b + tmp;
    }
}

void generateBlankText(const int lengthOfText, QString& outputText)
{
    outputText.clear();
    for (int i = 0; i < lengthOfText; ++i)
    {
        outputText += '_';
    }
}

void listDirectoriesRecursively(const int limit, QDir& directory, QStringList& list)
{
    list.clear();
    directory.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList queue = directory.entryInfoList();
    int visited = 0;
    while (!queue.isEmpty() && visited < limit)
    {
        const QFileInfo current = queue.first();
        queue.removeFirst();
        visited++;
        
        list.append(current.filePath());
        
        QDir currentDir(current.filePath());
        currentDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        const QFileInfoList newDirs = currentDir.entryInfoList();
        queue.append(newDirs);
    }
}

void generateListOfDirsText(const int lengthOfText, QString& outputText)
{
    outputText.clear();
    QDir rootDir = QDir::root();
    QStringList list;
    listDirectoriesRecursively(lengthOfText, rootDir, list);
    outputText = list.join("\n");
}

void generateRandomText(const int length, QString& outputText)
{
    outputText.clear();
    for (int i = 0; i < length; ++i)
    {
        char randChr = rand();
        outputText += randChr;
    }
}

void createHTMLFileWithBody(const QString& fileName, const QString& body, ArrayType& array)
{
  QByteArray fileData;
    
  fileData += "<!DOCTYPE html>\n";
  fileData += "<html>\n";
  fileData += "<head>\n";
  fileData += "<meta charset=\"utf-8\" />\n";
  fileData += "<title>";
  fileData += fileName;
  fileData += "</title>\n";
  fileData += "</head>\n";
  fileData += "<body>\n";
  fileData += body;
  fileData += "</body>\n";
  fileData += "</html>\n";
    
  array << ElemType(fileName, fileData);
}

int main(int argc, char* argv[])
{
    srand(time(NULL)); // init random
    
    QFileInfo executableFile(argv[0]);
    QDir currentDir(executableFile.dir());
    
    if (!currentDir.cd("output"))
    {
        fprintf(stderr, "No output folder\n");
        return -1;
    }
    
    const int size = 1000000;
    
    QString fibonaciText;
    QString listOfFilesText;
    QString blankText;
    QString randomText;
    
    generateFibonaciText(3250, fibonaciText);
    generateListOfDirsText(8000, listOfFilesText);
    generateBlankText(size, blankText);
    generateRandomText(size, randomText);
    
    const QString currentPath = currentDir.path();
    
    ArrayType array;

    for (int i = 0; i < 25; ++i)
    {
        const QString numberI = QString::number(i);
        
        const QString fibonaciFileName    = currentPath + "/fibonaci" + numberI;
        const QString listOfFilesFileName = currentPath + "/ls" + numberI;
        const QString blankTextFileName   = currentPath + "/blank" + numberI;
        const QString randomFileName      = currentPath + "/random" + numberI;
        
        createHTMLFileWithBody(fibonaciFileName, fibonaciText, array);
        createHTMLFileWithBody(listOfFilesFileName, listOfFilesText, array);
        createHTMLFileWithBody(blankTextFileName, blankText, array);
        createHTMLFileWithBody(randomFileName, randomText, array);
    }

    QFile stdOutFile;

    stdOutFile.open(stdout, QIODevice::WriteOnly);
    QDataStream out(&stdOutFile);
    
    out << array;

    return 0;
}
