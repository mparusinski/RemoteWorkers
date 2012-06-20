INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Programming_SOURCES
  Return.cc
  Classes.cc
)

SET(Programming_HEADERS
  Return.h
  Classes.h
)

ADD_LIBRARY(Programming STATIC ${Programming_SOURCES} ${Programming_HEADERS})
