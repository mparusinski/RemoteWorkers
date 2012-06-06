INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(WorkerInterface_HEADERS
  Worker.hpp
  Command.hpp
  Reply.hpp
  Configuration.hpp
  Management.hpp
)

SET(WorkerInterface_SOURCES 
  Worker.cpp
  Command.cpp
  Reply.cpp
  Configuration.cpp
  Management.cpp
)

ADD_LIBRARY(WorkerInterface
  ${WorkerInterface_SOURCES} ${WorkerInterface_HEADERS})

TARGET_LINK_LIBRARIES(WorkerInterface Utils)
TARGET_LINK_LIBRARIES(WorkerInterface DataStructures)


