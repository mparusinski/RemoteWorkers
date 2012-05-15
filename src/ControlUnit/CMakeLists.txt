CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

MESSAGE("-- Checking operating system:")

MESSAGE("Checking for Apple system")

IF(APPLE)
  MESSAGE("Apple system detected")
  SET(CMAKE_CXX_COMPILER /usr/bin/g++)
  SET(CMAKE_C_COMPILER /usr/bin/gcc)
  INCLUDE_DIRECTORIES(
    /usr/include
    /usr/include/c++/4.2.1/
  )
ENDIF(APPLE)

PROJECT(RemoteWorkers_ControlUnit CXX)

#MESSAGE("Setting up QT4")
#FIND_PACKAGE(Qt4 REQUIRED)
#MESSAGE("QT4 successfully setup")

MESSAGE("Setting up Boost")
FIND_PACKAGE(Boost REQUIRED)
IF (Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../../lib/boost_1_49_0/")
ENDIF()

MESSAGE("Adding LZMA library")
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../../lib/lzma920/C/")
INCLUDE_DIRECTORIES(../../lib/lzma920/C/)

ADD_SUBDIRECTORY(Tests)
ADD_SUBDIRECTORY(NetworkInterface)
ADD_SUBDIRECTORY(WorkerInterface)
ADD_SUBDIRECTORY(ConsoleInterface)
ADD_SUBDIRECTORY(Utils)
