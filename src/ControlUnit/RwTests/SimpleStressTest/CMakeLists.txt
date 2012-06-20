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

TARGET_LINK_LIBRARIES(SimpleStressTest RwWorkerInterface)
TARGET_LINK_LIBRARIES(SimpleStressTest RwProfile)
TARGET_LINK_LIBRARIES(SimpleStressTest ${QT_LIBRARIES})

