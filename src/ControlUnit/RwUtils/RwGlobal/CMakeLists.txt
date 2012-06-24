INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwGlobal_SOURCES
  RwDefines.cc
  RwClasses.cc
  RwReturn.cc
)

SET(RwGlobal_HEADERS
  RwDefines.h
  RwClasses.h
  RwReturn.h
)

ADD_LIBRARY(RwGlobal STATIC 
  ${RwGlobal_SOURCES} ${RwGlobal_HEADERS})
