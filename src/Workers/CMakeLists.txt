CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

MESSAGE("-- Checking operating system:")

IF(APPLE)
  MESSAGE("Apple system detected")
  SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
  SET(CMAKE_C_COMPILER /usr/bin/clang)
  SET(CMAKE_OSX_ARCHITECTURES x86_64)
  INCLUDE_DIRECTORIES(
    /usr/include
    /usr/include/c++/4.2.1/
  )
ENDIF(APPLE)

IF(NOT APPLE AND UNIX)
  MESSAGE("Linux system detected - or other unix")
  SET(CMAKE_CXX_COMPILER /usr/bin/g++)
  SET(CMAKE_C_COMPILER /usr/bin/gcc)
ENDIF(NOT APPLE AND UNIX)

PROJECT(RemoteWorkers_Workers CXX)

ADD_SUBDIRECTORY(SimpleTestWorker)
ADD_SUBDIRECTORY(NastyBadWorker)
ADD_SUBDIRECTORY(SecurityPenetrationTestWorker)
