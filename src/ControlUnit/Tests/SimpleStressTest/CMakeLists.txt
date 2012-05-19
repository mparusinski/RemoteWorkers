INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(SimpleStressTestSRC
  SimpleStressTest.cpp
)

ADD_EXECUTABLE(SimpleStressTest ${SimpleStressTestSRC})

TARGET_LINK_LIBRARIES(SimpleStressTest WorkerInterface)
