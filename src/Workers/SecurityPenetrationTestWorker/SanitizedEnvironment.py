#! /usr/bin/env python

"""

SanitizedEnvironment.py: checking if we are dealing with a sanitized environment

As part of the RemoteWorkers program which creates a framework for remote
management of laptops, desktop and servers. 

Copyright (C) 2012 Remote Workers Project. All rights reserved.
Created by Michal Parusinski <mparusinski@googlemail.com> on 18/05/2012.

"""

import sys
import os

def main(arguments):
    environ = os.environ
    homeVar = environ['HOME']
    userVar = environ['USER']
    if not homeVar == '/Users/' + userVar:
        print "The environment variables were changed"
        return 0
    else :
        print "The environment variables were not changed"
        return 1

if __name__ == "__main__":
    sys.exit(main(sys.argv))