#! /usr/bin/env python

"""

main.py: main file for the nasty bad worker

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/05/2012.

"""

import random
import os.path
import sys

def generateFibonaciText(number):
    text = ""
    a, b = 0, 1
    for i in xrange(number):
        text = str(a) + '\n' + text
        a, b = b, a + b
    return text


def generateBlankText(lengthOfBlankText):
    blankText = ""
    for i in xrange(lengthOfBlankText):
        blankText = "_"  + blankText
    return blankText   
    

def generateListOfFilesText(directory):
    files = listOfFilesRecursively(directory)
    text = ""
    for file in files:
        text = file + '\n' + text
    return text
    
def listOfFilesRecursively(directory):
    if (os.path.exists(directory) and os.path.isdir(directory)):
        content = os.listdir(directory)
        files = content
        for file in content:
            subContent = listOfFilesRecursively(directory + os.path.sep + file)
            files = files + subContent
        return files
    else:   
        return []


def generateRandomText(lengthOfRandomText):
    randomText = ""
    for i in xrange(lengthOfRandomText):
        randomInteger   = random.randint(0,2**8 - 1)
        randomCharacter = chr(randomInteger)
        randomText = randomCharacter + randomText # Not normal way of appending text
    return randomText
        

def generateHTMLWithBody(fileName, bodyContent):
    file = open(fileName + ".html", 'w')
    file.write("<!DOCTYPE html>")
    file.write("<html>")
    file.write("<head>")
    file.write('<meta charset="utf-8"/>')
    file.write("<title>"+fileName+"</title>")
    file.write("</head>")
    file.write("<body>")
    file.write(bodyContent)
    file.write("</body>")
    file.write("</html>")
    file.close()


def main(arguments):
    randomText      = generateRandomText(1000)
    listOfFilesText = generateListOfFilesText("/Users/mparusinski/")
    blankText       = generateBlankText(1000)
    fibonaciText    = generateFibonaciText(1000)
    currentPath = arguments[0]
    currentPath = os.path.dirname(currentPath) 
    outputPath  = currentPath + os.path.sep + 'output/'
    for i in xrange(25):
        randomTextName      = "random" + str(i)
        listOfFilesTextName = "ls" + str(i)
        blankTextName       = "blank" + str(i)
        fibonaciTextName    = "fib" + str(i)
        generateHTMLWithBody(randomTextName, randomText)
        generateHTMLWithBody(listOfFilesTextName, listOfFilesText)
        generateHTMLWithBody(blankTextName, blankText)
        generateHTMLWithBody(fibonaciTextName, fibonaciText)

if (__name__ == "__main__"):
    main(sys.argv)