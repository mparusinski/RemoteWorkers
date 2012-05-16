INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(NetworkInterfaceSRC STATIC
    NetworkSocketBase.hpp
    NetworkSocketBase.cpp
    NetworkSocketSsl.hpp
    NetworkSocketSsl.cpp
)

ADD_LIBRARY(NetworkInterface ${NetworkInterfaceSRC})
