INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwGraphical_SRC
  main.cc
)

ADD_EXECUTABLE(RemoteWorkers_GUI ${RwGraphical_SRC})

TARGET_LINK_LIBRARIES(RemoteWorkers_GUI ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(RemoteWorkers_GUI RwGUI)

