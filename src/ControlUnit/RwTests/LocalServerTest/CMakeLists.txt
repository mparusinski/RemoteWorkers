INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(LocalServerTestSRC
  LocalServerTest.cc
)

ADD_EXECUTABLE(LocalServerTest ${LocalServerTestSRC})

TARGET_LINK_LIBRARIES(LocalServerTest RwNetworkInterface)
TARGET_LINK_LIBRARIES(LocalServerTest ${QT_LIBRARIES})
