INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwHistory_HEADERS
  RwEvent.h 
  RwEventLog.h
  RwEventType.h
  RwWorkerAddedEvent.h
  RwWorkerRemovedEvent.h
  RwWorkerExecutionEvent.h
  RwServerStartedEvent.h
  RwServerStoppedEvent.h
)

SET(RwHistory_SOURCES 
  RwEvent.cc
  RwEventLog.cc
  RwEventType.cc
  RwWorkerAddedEvent.cc
  RwWorkerRemovedEvent.cc
  RwWorkerExecutionEvent.cc
  RwServerStartedEvent.cc
  RwServerStoppedEvent.cc
)

ADD_LIBRARY(RwHistory STATIC 
  ${RwHistory_SOURCES} ${RwHistory_HEADERS})

TARGET_LINK_LIBRARIES(RwHistory RwWorkerInterface)
TARGET_LINK_LIBRARIES(RwHistory ${QT_LIBRAIRES})

