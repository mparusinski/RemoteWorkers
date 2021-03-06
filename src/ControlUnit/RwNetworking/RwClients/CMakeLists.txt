INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwClients_SOURCES
    RwCommandClientLocal.cc
    RwCommandClientTCP.cc
    RwCommandClientSSL.cc
    RwCommandClientBase.cc
    RwCommandLocalPipeIn.cc
    RwCommandLocalPipeOut.cc
    RwCommandLocalPipeServer.cc
    RwRemoteDevice.cc
    RwRemoteDeviceList.cc
)

SET(RwClients_HEADERS
    RwRemoteDeviceList.h
)

SET(RwClients_HEADERS_QT
    RwCommandClientLocal.h
    RwCommandClientTCP.h
    RwCommandClientSSL.h
    RwCommandClientBase.h
    RwCommandLocalPipeIn.h
    RwCommandLocalPipeOut.h
    RwCommandLocalPipeServer.h
    RwRemoteDevice.h
)

QT4_WRAP_CPP(
    RwClients_HEADERS_MOC 
    ${RwClients_HEADERS_QT}
)

ADD_LIBRARY(RwClients STATIC 
  ${RwClients_SOURCES}  ${RwClients_HEADERS_QT} 
  ${RwClients_HEADERS_MOC} ${RwClients_HEADERS})

TARGET_LINK_LIBRARIES(RwClients RwWorkerInterface RwLog RwSocket RwNetDataStructures)
TARGET_LINK_LIBRARIES(RwClients ${QT_LIBRARIES})

