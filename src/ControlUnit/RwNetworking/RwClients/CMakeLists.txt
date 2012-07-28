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
    RwRemoteDevice.cc
    RwRemoteDeviceList.cc
)

SET(RwClients_HEADERS_QT
    RwCommandClientLocal.h
    RwCommandClientTCP.h
    RwCommandClientSSL.h
    RwCommandClientBase.h
    RwRemoteDevice.h
    RwRemoteDeviceList.h
)

QT4_WRAP_CPP(RwClients_HEADERS_MOC ${RwClients_HEADERS_QT})

ADD_LIBRARY(RwClients STATIC 
  ${RwClients_SOURCES}  ${RwClients_HEADERS_QT} 
  ${RwClients_HEADERS_MOC})

TARGET_LINK_LIBRARIES(RwClients RwWorkerInterface RwLog RwSocket)
TARGET_LINK_LIBRARIES(RwClients ${QT_LIBRARIES})

