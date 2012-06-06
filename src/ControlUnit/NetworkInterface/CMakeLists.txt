INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(NetworkInterface_SOURCES
    NetworkSocketBase.cpp
    NetworkSocketSsl.cpp
)

SET(NetworkInterface_HEADERS
    NetworkSocketBase.hpp
    NetworkSocketSsl.hpp
)

ADD_LIBRARY(NetworkInterface STATIC ${NetworkInterface_SOURCES} ${NetworkInterface_HEADERS})
