CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

MESSAGE("-- Checking operating system:")

MESSAGE("Checking for Apple system")

IF(APPLE)
  MESSAGE("Apple system detected")
  SET(CMAKE_CXX_COMPILER /usr/bin/g++)
  SET(CMAKE_C_COMPILER /usr/bin/gcc)
  SET(CMAKE_OSX_ARCHITECTURES i386)
  INCLUDE_DIRECTORIES(
    /usr/include
    /usr/include/c++/4.2.1/
  )
ENDIF(APPLE)

PROJECT(RemoteWorkers_Workers CXX)

MESSAGE("Adding Boost library")
SET(BOOST_ROOT "../../lib/boost_1_49_0/")
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)
IF (Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
  MESSAGE( STATUS "Include dirs: " ${Boost_INCLUDE_DIR})
  MESSAGE( STATUS "Library dirs: " ${Boost_LIBRARY_DIRS})
  MESSAGE( STATUS "Libraries: " ${Boost_LIBRARIES})
#  SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../../lib/boost_1_49_0/")
ENDIF()

ADD_SUBDIRECTORY(SimpleTestWorker)
ADD_SUBDIRECTORY(NastyBadWorker)
ADD_SUBDIRECTORY(SecurityPenetrationTestWorker)
