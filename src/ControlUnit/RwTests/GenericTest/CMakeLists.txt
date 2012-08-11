INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(GenericTestSRC
  main.cc
)

ADD_EXECUTABLE(GenericTest ${GenericTestSRC})

TARGET_LINK_LIBRARIES(GenericTest ${QT_LIBRARIES})


