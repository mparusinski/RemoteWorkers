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

PROJECT(RemoteWorkers_Workers CXX)

ADD_SUBDIRECTORY(SimpleTestWorker)
ADD_SUBDIRECTORY(NastyBadWorker)
ADD_SUBDIRECTORY(SecurityPenetrationTestWorker)
