INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Log_SOURCES
   Logger.cpp
   LoggerBaseClass.cpp
   FileLogger.cpp
   ConsoleLogger.cpp
)

SET(Log_HEADERS
   Logger.hpp
   LoggerBaseClass.hpp
   FileLogger.hpp
   ConsoleLogger.hpp
)

ADD_LIBRARY(Log STATIC ${Log_SOURCES} ${Log_HEADERS})

TARGET_LINK_LIBRARIES(Log ${QT_LIBRAIRES})
