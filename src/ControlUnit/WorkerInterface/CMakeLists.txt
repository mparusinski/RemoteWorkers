INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(WorkerInterfaceSRC STATIC
  Worker.hpp
  Worker.cpp
  Command.hpp
  Command.cpp
  Reply.hpp
  Reply.cpp
  Configuration.hpp
  Configuration.cpp
)

ADD_LIBRARY(WorkerInterface ${WorkerInterfaceSRC})

TARGET_LINK_LIBRARIES(WorkerInterface Utils)
TARGET_LINK_LIBRARIES(WorkerInterface DataStructures)

