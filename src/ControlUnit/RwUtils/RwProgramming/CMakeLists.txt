INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwProgramming_SOURCES
  RwReturn.cc
  RwClasses.cc
)

SET(RwProgramming_HEADERS
  RwReturn.h
  RwClasses.h
)

ADD_LIBRARY(RwProgramming STATIC 
  ${RwProgramming_SOURCES} ${RwProgramming_HEADERS})
