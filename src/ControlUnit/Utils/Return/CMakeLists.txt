INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Return_SOURCES
  Return.cpp
)

SET(Return_HEADERS
  Return.hpp
)

ADD_LIBRARY(Return STATIC ${Return_SOURCES} ${Return_HEADERS})
