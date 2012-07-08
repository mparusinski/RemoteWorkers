INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwWorkerInterface_HEADERS
  RwWorker.h
  RwCommand.h
  RwReply.h
  RwConfiguration.h
  RwManagement.h
)

SET(RwWorkerInterface_SOURCES 
  RwWorker.cc
  RwCommand.cc
  RwReply.cc
  RwConfiguration.cc
  RwManagement.cc
)

ADD_LIBRARY(RwWorkerInterface STATIC 
  ${RwWorkerInterface_SOURCES} ${RwWorkerInterface_HEADERS})

TARGET_LINK_LIBRARIES(RwWorkerInterface RwLog)
TARGET_LINK_LIBRARIES(RwWorkerInterface RwSystem)
TARGET_LINK_LIBRARIES(RwWorkerInterface ${QT_LIBRAIRES})

