INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}/WorkerInterface
)
LINK_DIRECTORIES(${RemoteWorkers_ControlUnit_BINARY_DIR}/WorkerInterface)

SET(ControlUnitConsoleSRC
    Console.cpp
)

ADD_EXECUTABLE(ControlUnitConsole ${ControlUnitConsoleSRC})

TARGET_LINK_LIBRARIES(ControlUnitConsole WorkerInterface)
