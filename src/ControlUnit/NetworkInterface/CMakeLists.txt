SET(NetworkInterfaceSRC STATIC
    NetworkSocketBase.hpp
    NetworkSocketBase.cpp
    NetworkSocketSsl.hpp
    NetworkSocketSsl.cpp
)

ADD_LIBRARY(NetworkInterface ${NetworkInterfaceSRC})
