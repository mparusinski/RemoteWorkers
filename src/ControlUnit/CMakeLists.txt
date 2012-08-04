CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(RemoteWorkers_ControlUnit CXX)

MESSAGE("-- Checking operating system:")

IF(APPLE)
  MESSAGE("Apple system detected")
  SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
  SET(CMAKE_C_COMPILER /usr/bin/clang)
  SET(CMAKE_OSX_ARCHITECTURES x86_64)
ENDIF(APPLE)

IF(NOT APPLE AND UNIX)
  MESSAGE("Linux system detected - or other unix system")
  SET(CMAKE_CXX_COMPILER /usr/bin/g++)
  SET(CMAKE_C_COMPILER /usr/bin/gcc)
ENDIF(NOT APPLE AND UNIX)

IF(WIN32)
  MESSAGE("Windows system detected")
  LINK_DIRECTORIES(C:/QtSDK/Desktop/Qt/4.8.1/mingw/lib/) #Quick fix
ENDIF(WIN32)

MESSAGE("Setting up QT4")
FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTNETWORK TRUE)
SET(QT_USE_QTWEBKIT TRUE)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
MESSAGE("QT4 successfully setup")

#MESSAGE("Adding LZMA library")
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../../lib/lzma920/C/")
#INCLUDE_DIRECTORIES(../../lib/lzma920/C/)

ADD_SUBDIRECTORY(RwTests)
ADD_SUBDIRECTORY(RwNetworking)
ADD_SUBDIRECTORY(RwWorkerInterface)
ADD_SUBDIRECTORY(RwHistory)
ADD_SUBDIRECTORY(RwUtils)
ADD_SUBDIRECTORY(RwGUI)
ADD_SUBDIRECTORY(RwExecutables)

FILE( COPY conf.txt DESTINATION ${RemoteWorkers_ControlUnit_BINARY_DIR} )
FILE( COPY WorkersList.txt DESTINATION ${RemoteWorkers_ControlUnit_BINARY_DIR} )
FILE( COPY Devices.txt DESTINATION ${RemoteWorkers_ControlUnit_BINARY_DIR} )

FILE( MAKE_DIRECTORY ${RemoteWorkers_ControlUnit_BINARY_DIR}/responseData )
