INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwServers_SOURCES
    RwCommandServerBase.cc
    RwCommandServerTCP.cc
    RwCommandServerSSL.cc
    RwCommandServerLocal.cc
    RwCommandServerThread.cc
)

SET(RwServers_HEADERS
    RwCommandServerBase.h
    RwCommandServerThread.h
)

SET(RwServers_HEADERS_QT
    RwCommandServerTCP.h
    RwCommandServerSSL.h
    RwCommandServerLocal.h
)

QT4_WRAP_CPP(RwServers_HEADERS_MOC ${RwServers_HEADERS_QT})

ADD_LIBRARY(RwServers STATIC 
  ${RwServers_SOURCES}  ${RwServers_HEADERS_QT} ${RwServers_HEADERS}
  ${RwServers_HEADERS_MOC})

TARGET_LINK_LIBRARIES(RwServers RwWorkerInterface RwLog RwNetDataStructures RwHistory)
TARGET_LINK_LIBRARIES(RwServers ${QT_LIBRARIES})

