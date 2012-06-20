INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwSystem_SOURCES
  RwExternalApplication.cc
  RwFileManagement.cc
)

SET(RwSystem_HEADERS
  RwFileManagement.h
  RwExternalApplication.h
)

ADD_LIBRARY(RwSystem STATIC ${RwSystem_SOURCES} ${RwSystem_HEADERS})

TARGET_LINK_LIBRARIES(RwSystem ${QT_LIBRAIRES})
