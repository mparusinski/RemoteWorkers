INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(SecurityPenetrationTestSRC
  SecurityPenetrationTest.cc
)

ADD_EXECUTABLE(SecurityPenetrationTest ${SecurityPenetrationTestSRC})

TARGET_LINK_LIBRARIES(SecurityPenetrationTest WorkerInterface)
TARGET_LINK_LIBRARIES(SecurityPenetrationTest ${QT_LIBRARIES})

