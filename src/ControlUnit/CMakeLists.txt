CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

MESSAGE("-- Checking operating system:")

MESSAGE("Checking for Apple system")

IF(APPLE)
  MESSAGE("Apple system detected")
#  SET(CMAKE_CXX_COMPILER /usr/bin/g++)
#  SET(CMAKE_C_COMPILER /usr/bin/gcc)
  SET(CMAKE_OSX_ARCHITECTURES x86_64)
  INCLUDE_DIRECTORIES(
    /usr/include
    /usr/include/c++/4.2.1/
  )
ENDIF(APPLE)

PROJECT(RemoteWorkers_ControlUnit CXX)

MESSAGE("Setting up QT4")
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
MESSAGE("QT4 successfully setup")

MESSAGE("Adding LZMA library")
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../../lib/lzma920/C/")
INCLUDE_DIRECTORIES(../../lib/lzma920/C/)

ADD_SUBDIRECTORY(Tests)
ADD_SUBDIRECTORY(NetworkInterface)
ADD_SUBDIRECTORY(WorkerInterface)
ADD_SUBDIRECTORY(ConsoleInterface)
ADD_SUBDIRECTORY(Utils)
ADD_SUBDIRECTORY(DataStructures)

FILE( COPY conf.txt DESTINATION ${RemoteWorkers_ControlUnit_BINARY_DIR} )
