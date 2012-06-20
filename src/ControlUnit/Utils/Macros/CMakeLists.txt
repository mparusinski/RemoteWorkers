INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Macros_SOURCES
  Macros.cc
)

SET(Macros_HEADERS
  Macros.h
)

ADD_LIBRARY(Macros STATIC ${Macros_SOURCES} ${Macros_HEADERS})
