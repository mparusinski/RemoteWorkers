INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwNetworkInterface_SOURCES
    RwNetworkSocketBase.cc
    RwNetworkSocketSsl.cc
)

SET(RwNetworkInterface_HEADERS
    RwNetworkSocketBase.h
    RwNetworkSocketSsl.h
)

ADD_LIBRARY(RwNetworkInterface STATIC 
  ${RwNetworkInterface_SOURCES} ${RwNetworkInterface_HEADERS})
