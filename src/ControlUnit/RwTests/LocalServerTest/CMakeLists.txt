INCLUDE_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(LocalServerTestSRC
  LocalServerTest.cc
)

SET(LocalServerTestHEADERS
  DummyClass.h
)

QT4_WRAP_CPP(LocalServerTestHEADERS_MOC ${LocalServerTestHEADERS})

ADD_EXECUTABLE(LocalServerTest ${LocalServerTestSRC} ${LocalServerTestHEADERS} 
  ${LocalServerTestHEADERS_MOC})

TARGET_LINK_LIBRARIES(LocalServerTest RwServers RwClients RwLog RwProfile)
TARGET_LINK_LIBRARIES(LocalServerTest ${QT_LIBRARIES})
