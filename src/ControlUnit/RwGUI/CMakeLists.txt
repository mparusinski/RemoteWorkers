INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwGUI_HEADERS
    RwMainWindow.h
    RwPrefWindow.h
    RwAbstractMode.h
    RwWorkersCenterMode.h
    RwRemoteDevicesMode.h
    RwEventsMode.h
)

SET(RwGUI_SOURCES 
    RwMainWindow.cc
    RwPrefWindow.cc
    RwAbstractMode.cc
    RwWorkersCenterMode.cc
    RwRemoteDevicesMode.cc
    RwEventsMode.cc
)

ADD_LIBRARY(RwGUI STATIC 
  ${RwGUI_SOURCES} ${RwGUI_HEADERS})

TARGET_LINK_LIBRARIES(RwGUI ${QT_LIBRAIRES})

