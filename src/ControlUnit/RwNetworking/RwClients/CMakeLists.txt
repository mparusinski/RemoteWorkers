INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwClients_SOURCES
    RwCommandClientLocal.cc
)

SET(RwClients_HEADERS_QT
    RwCommandClientLocal.h
)

QT4_WRAP_CPP(RwClients_HEADERS_MOC ${RwClients_HEADERS_QT})

ADD_LIBRARY(RwClients STATIC 
  ${RwClients_SOURCES}  ${RwClients_HEADERS_QT} 
  ${RwClients_HEADERS_MOC})

TARGET_LINK_LIBRARIES(RwClients RwWorkerInterface)
TARGET_LINK_LIBRARIES(RwClients RwLog)
TARGET_LINK_LIBRARIES(RwClients ${QT_LIBRARIES})

