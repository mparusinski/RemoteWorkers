INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Return_SOURCES
  Return.cc
)

SET(Return_HEADERS
  Return.h
)

ADD_LIBRARY(Return STATIC ${Return_SOURCES} ${Return_HEADERS})
