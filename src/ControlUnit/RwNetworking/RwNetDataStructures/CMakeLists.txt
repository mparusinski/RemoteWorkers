INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwNetDataStructures_SOURCES
    RwNetDataStructureBase.cc
    RwCommandRequest.cc
    RwCommandReply.cc
)

SET(RwNetDataStructures_HEADERS
    RwNetDataStructureBase.h
    RwCommandRequest.h    
    RwCommandReply.h
)

ADD_LIBRARY(RwNetDataStructures STATIC 
  ${RwNetDataStructures_SOURCES}  ${RwNetDataStructures_HEADERS})

TARGET_LINK_LIBRARIES(RwNetDataStructures RwWorkerInterface)
TARGET_LINK_LIBRARIES(RwNetDataStructures RwLog)
TARGET_LINK_LIBRARIES(RwNetDataStructures ${QT_LIBRARIES})

