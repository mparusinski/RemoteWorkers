/* 

LocalServerTest.cc: Checking if the local server works and more in general if server functionality works

As part of the Remote Workers Project which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 22/06/2012

*/

#include <QString>

#include "RwNetworking/RwCommandServerLocal.h"

using namespace RwNetworking;

int main(int argc, char* argv[])
{
    RwCommandServerLocal localServer("local");
    
    return 0;
}