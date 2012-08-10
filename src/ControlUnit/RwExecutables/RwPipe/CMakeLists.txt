INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwPipe_SRC
  main.cc
)

ADD_EXECUTABLE(CommandPipe ${RwPipe_SRC})

TARGET_LINK_LIBRARIES(CommandPipe ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(CommandPipe RwClients RwNetDataStructures)

