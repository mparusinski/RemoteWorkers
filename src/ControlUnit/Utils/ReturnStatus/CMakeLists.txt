INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(ReturnStatus_SOURCES
  ReturnStatus.cpp
  StatusBase.cpp
  Success.cpp
  Failure.cpp
)

SET(ReturnStatus_HEADERS
  ReturnStatus.hpp
  StatusBase.hpp
  Success.hpp
  Failure.hpp
)

ADD_LIBRARY(ReturnStatus STATIC ${ReturnStatus_SOURCES} ${ReturnStatus_HEADERS})
