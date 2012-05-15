INCLUDE_DIRECTORIES(${RemoteWorkers_ControlUnit_SOURCE_DIR}/Utils)
LINK_DIRECTORIES(${RemoteWorkers_ControlUnit_BINARY_DIR}/Utils)

SET(WorkerInterfaceSRC STATIC
  Worker.hpp
  Worker.cpp
  Command.hpp
  Command.cpp
  Reply.hpp
  Reply.cpp
)

ADD_LIBRARY(WorkerInterface ${WorkerInterfaceSRC})

TARGET_LINK_LIBRARIES(WorkerInterface Utils)
