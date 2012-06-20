INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(SimpleStressTestSRC
  SimpleStressTest.cc
)

ADD_EXECUTABLE(SimpleStressTest ${SimpleStressTestSRC})

TARGET_LINK_LIBRARIES(SimpleStressTest WorkerInterface)
TARGET_LINK_LIBRARIES(SimpleStressTest Profile)
TARGET_LINK_LIBRARIES(SimpleStressTest ${QT_LIBRARIES})

