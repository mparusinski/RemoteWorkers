INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwLog_SOURCES
   RwLogger.cc
   RwLoggerBaseClass.cc
   RwFileLogger.cc
   RwConsoleLogger.cc
)

SET(RwLog_HEADERS
   RwLogger.h
   RwLoggerBaseClass.h
   RwFileLogger.h
   RwConsoleLogger.h
)

ADD_LIBRARY(RwLog STATIC ${RwLog_SOURCES} ${RwLog_HEADERS})

TARGET_LINK_LIBRARIES(RwLog ${QT_LIBRAIRES})
