INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwHistory_HEADERS_QT
  RwEventLog.h
)

SET(RwHistory_HEADERS
  RwEvent.h 
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

QT4_WRAP_CPP(RwHistory_HEADERS_MOC ${RwHistory_HEADERS_QT})

ADD_LIBRARY(RwHistory STATIC 
  ${RwHistory_SOURCES} ${RwHistory_HEADERS} ${RwHistory_HEADERS_QT} ${RwHistory_HEADERS_MOC})

TARGET_LINK_LIBRARIES(RwHistory RwWorkerInterface)
TARGET_LINK_LIBRARIES(RwHistory ${QT_LIBRAIRES})

