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
    RwCommandClientLocal.cc
    RwCommandRequest.cc
    RwCommandReply.cc
)

SET(RwNetworking_HEADERS_QT
    RwCommandServerBase.h
    RwCommandServerTCP.h
    RwCommandServerSSL.h
    RwCommandServerLocal.h
    RwCommandClientLocal.h
)

SET(RwNetworking_HEADERS_PURE
    RwCommandRequest.h    
    RwCommandReply.h
)

QT4_WRAP_CPP(RwNetworking_HEADERS_MOC ${RwNetworking_HEADERS_QT})

ADD_LIBRARY(RwNetworking STATIC 
  ${RwNetworking_SOURCES}  ${RwNetworking_HEADERS_QT} ${RwNetworking_HEADERS_PURE}
  ${RwNetworking_HEADERS_MOC})

TARGET_LINK_LIBRARIES(RwNetworking RwWorkerInterface)
TARGET_LINK_LIBRARIES(RwNetworking ${QT_LIBRARIES})

