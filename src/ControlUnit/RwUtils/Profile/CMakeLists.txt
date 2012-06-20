INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Profile_SOURCES
  Profiler.cc
)

SET(Profile_HEADERS
  Profiler.h
)

ADD_LIBRARY(Profile STATIC ${Profile_SOURCES} ${Profile_HEADERS})

TARGET_LINK_LIBRARIES(Profile ${QT_LIBRAIRES})
