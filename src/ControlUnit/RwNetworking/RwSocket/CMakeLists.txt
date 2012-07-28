INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwSocket_SOURCES
   RwAbstractSocket.cc
   RwLocalSocket.cc
   RwTCPSocket.cc
   RwSSLSocket.cc
)

SET(RwSocket_HEADERS_QT
   RwAbstractSocket.h
   RwLocalSocket.h
   RwTCPSocket.h
   RwSSLSocket.h
)

QT4_WRAP_CPP(RwSocket_HEADERS_MOC ${RwSocket_HEADERS_QT})

ADD_LIBRARY(RwSocket STATIC 
  ${RwSocket_SOURCES}  ${RwSocket_HEADERS_QT}
  ${RwSocket_HEADERS_MOC})

TARGET_LINK_LIBRARIES(RwSocket ${QT_LIBRARIES})

