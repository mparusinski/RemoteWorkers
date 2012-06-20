INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(NetworkInterface_SOURCES
    NetworkSocketBase.cc
    NetworkSocketSsl.cc
)

SET(NetworkInterface_HEADERS
    NetworkSocketBase.h
    NetworkSocketSsl.h
)

ADD_LIBRARY(NetworkInterface STATIC ${NetworkInterface_SOURCES} ${NetworkInterface_HEADERS})
