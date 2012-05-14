INCLUDE_DIRECTORIES(${RemoteWorkers_ControlUnit_SOURCE_DIR}/NetworkInterface)
LINK_DIRECTORIES(${RemoteWorkers_ControlUnit_BINARY_DIR}/NetworkInterface)

SET(controlUnitConsoleSRC
    Console.cpp
)

ADD_EXECUTABLE(controlUnitConsole ${controlUnitConsoleSRC})

TARGET_LINK_LIBRARIES(controlUnitConsole NetworkInterface)
