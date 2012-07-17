INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwHistory_HEADERS
  RwEvent.h
)

SET(RwHistory_SOURCES 
  RwEvent.cc
)

ADD_LIBRARY(RwHistory STATIC 
  ${RwHistory_SOURCES} ${RwHistory_HEADERS})

TARGET_LINK_LIBRARIES(RwHistory ${QT_LIBRAIRES})

