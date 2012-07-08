INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(SimpleRunSRC
  SimpleRun.cc
)

ADD_EXECUTABLE(SimpleRun ${SimpleRunSRC})

TARGET_LINK_LIBRARIES(SimpleRun ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(SimpleRun RwSystem RwWorkerInterface)

