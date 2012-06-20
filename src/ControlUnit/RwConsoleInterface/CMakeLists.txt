INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)
LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(ControlUnitConsoleSOURCES
    Console.cc
)

ADD_EXECUTABLE(ControlUnitConsole ${ControlUnitConsoleSOURCES})

TARGET_LINK_LIBRARIES(ControlUnitConsole WorkerInterface Log System Profile)
TARGET_LINK_LIBRARIES(ControlUnitConsole ${QT_LIBRARIES})
