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
  FileManagement.cpp
)

ADD_LIBRARY(System STATIC ${System_SOURCES} ${System_HEADERS})
