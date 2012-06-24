INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(GeneralPurposeNetworkingTestSRC
  GeneralPurposeNetworkingTest.cc
)

ADD_EXECUTABLE(GeneralPurposeNetworkingTest ${GeneralPurposeNetworkingTestSRC})

TARGET_LINK_LIBRARIES(GeneralPurposeNetworkingTest RwNetworking)
TARGET_LINK_LIBRARIES(GeneralPurposeNetworkingTest ${QT_LIBRARIES})
