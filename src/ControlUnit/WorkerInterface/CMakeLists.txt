INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(WorkerInterface_HEADERS
  Worker.h
  Command.h
  Reply.h
  Configuration.h
  Management.h
)

SET(WorkerInterface_SOURCES 
  Worker.cc
  Command.cc
  Reply.cc
  Configuration.cc
  Management.cc
)

ADD_LIBRARY(WorkerInterface
  ${WorkerInterface_SOURCES} ${WorkerInterface_HEADERS})

TARGET_LINK_LIBRARIES(WorkerInterface Log)
TARGET_LINK_LIBRARIES(WorkerInterface System)
TARGET_LINK_LIBRARIES(WorkerInterface DataStructures)
TARGET_LINK_LIBRARIES(WorkerInterface ${QT_LIBRAIRES})

