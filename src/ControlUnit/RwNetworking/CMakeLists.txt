INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwNetworking_SOURCES
    RwCommandServerBase.cc
    RwCommandServerTCP.cc
    RwCommandServerSSL.cc
    RwCommandServerLocal.cc
)

SET(RwNetworking_HEADERS
    RwCommandServerBase.h
    RwCommandServerTCP.h
    RwCommandServerSSL.h
    RwCommandServerLocal.h
)

QT4_WRAP_CPP(RwNetworking_HEADERS_MOC ${RwNetworking_HEADERS})

ADD_LIBRARY(RwNetworking STATIC 
  ${RwNetworking_SOURCES}  ${RwNetworking_HEADERS})

