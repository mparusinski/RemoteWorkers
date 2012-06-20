INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Log_SOURCES
   Logger.cc
   LoggerBaseClass.cc
   FileLogger.cc
   ConsoleLogger.cc
)

SET(Log_HEADERS
   Logger.h
   LoggerBaseClass.h
   FileLogger.h
   ConsoleLogger.h
)

ADD_LIBRARY(Log STATIC ${Log_SOURCES} ${Log_HEADERS})

TARGET_LINK_LIBRARIES(Log ${QT_LIBRAIRES})
