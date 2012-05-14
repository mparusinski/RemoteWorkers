SET(networkInterfaceSRC STATIC
    NetworkSocketBase.hpp
    NetworkSocketBase.cpp
    NetworkSocketSsl.hpp
    NetworkSocketSsl.cpp
)

ADD_LIBRARY(networkInterface ${networkInterfaceSRC})
