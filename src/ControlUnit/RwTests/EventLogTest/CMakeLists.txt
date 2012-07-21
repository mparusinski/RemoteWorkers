INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(EventLogTestSRC
  EventLogTest.cc
)

ADD_EXECUTABLE(EventLogTest ${EventLogTestSRC})

TARGET_LINK_LIBRARIES(EventLogTest ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(EventLogTest RwHistory RwLog)
