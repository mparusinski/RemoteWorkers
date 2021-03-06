INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(RwGUI_HEADERS_QT
    RwMainWindow.h
    RwPrefWindow.h
    RwAboutWindow.h
    RwModeWidget.h
    RwAbstractMode.h
    RwWorkersCenterMode.h
    RwRemoteDevicesMode.h
    RwEventsMode.h
    RwWorkerWidget.h
)

SET(RwGUI_HEADERS
    RwRemoteDeviceItem.h
)

SET(RwGUI_SOURCES 
    RwMainWindow.cc
    RwAboutWindow.cc
    RwPrefWindow.cc
    RwModeWidget.cc
    RwAbstractMode.cc
    RwWorkersCenterMode.cc
    RwRemoteDevicesMode.cc
    RwEventsMode.cc
    RwWorkerWidget.cc
    RwRemoteDeviceItem.cc
)

QT4_WRAP_CPP(RwGUI_HEADERS_MOC ${RwGUI_HEADERS_QT})

ADD_LIBRARY(RwGUI STATIC ${RwGUI_HEADERS} 
  ${RwGUI_SOURCES} ${RwGUI_HEADERS_QT} ${RwGUI_HEADERS_MOC})

TARGET_LINK_LIBRARIES(RwGUI RwLog RwClients RwServers RwNetDataStructures)
TARGET_LINK_LIBRARIES(RwGUI ${QT_LIBRAIRES})

