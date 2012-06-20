INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(System_SOURCES
  ExternalApplication.cpp
  FileManagement.cpp
)

SET(System_HEADERS
  FileManagement.hpp
  ExternalApplication.hpp
)

ADD_LIBRARY(System STATIC ${System_SOURCES} ${System_HEADERS})

TARGET_LINK_LIBRARIES(System ${QT_LIBRAIRES})
