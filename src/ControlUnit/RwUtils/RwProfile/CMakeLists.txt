INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwProfile_SOURCES
  RwProfiler.cc
)

SET(RwProfile_HEADERS
  RwProfiler.h
)

ADD_LIBRARY(RwProfile STATIC ${RwProfile_SOURCES} ${RwProfile_HEADERS})

TARGET_LINK_LIBRARIES(RwProfile ${QT_LIBRAIRES})
