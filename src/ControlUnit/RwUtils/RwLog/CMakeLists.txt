INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwLog_SOURCES
   RwMessagingManager.cc
)

SET(RwLog_HEADERS
   RwMessagingManager.h
   RwCommon.h
)

ADD_LIBRARY(RwLog STATIC ${RwLog_SOURCES} ${RwLog_HEADERS})

TARGET_LINK_LIBRARIES(RwLog ${QT_LIBRAIRES})
