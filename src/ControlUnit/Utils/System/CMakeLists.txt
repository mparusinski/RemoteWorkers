INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(System_SOURCES
  ExternalApplication.cc
  FileManagement.cc
)

SET(System_HEADERS
  FileManagement.h
  ExternalApplication.h
)

ADD_LIBRARY(System STATIC ${System_SOURCES} ${System_HEADERS})

TARGET_LINK_LIBRARIES(System ${QT_LIBRAIRES})
