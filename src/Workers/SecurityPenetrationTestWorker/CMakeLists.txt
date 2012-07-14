INCLUDE_DIRECTORIES(
  ${RemoteWorkers_Workers_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_Workers_BINARY_DIR}
)

FILE( MAKE_DIRECTORY ${RemoteWorkers_Workers_BINARY_DIR}/SecurityPenetrationTestWorker/output )

SET(SecurityPenetrationTestWorker_HEADERS
  SanitizedEnvironment.h
)

SET(SecurityPenetrationTestWorker_SOURCES
  SanitizedEnvironment.cc
  main.cc
)

ADD_EXECUTABLE(SecurityPenetrationTestWorker
  ${SecurityPenetrationTestWorker_SOURCES}
  ${SecurityPenetrationTestWorker_HEADERS}
)

TARGET_LINK_LIBRARIES(SecurityPenetrationTestWorker ${QT_LIBRARIES})

#ADD_CUSTOM_COMMAND(
#  OUTPUT DenialOfService.py
#  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/DenialOfService.py ${CMAKE_CURRENT_BINARY_DIR}/DenialOfService
#  DEPENDS DenialOfService.py
#)

#ADD_CUSTOM_COMMAND(
#  OUTPUT SanitizedEnvironment.py
#  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/SanitizedEnvironment.py ${CMAKE_CURRENT_BINARY_DIR}/SanitizedEnvironment
#  DEPENDS SanitizedEnvironment.py
#)

#ADD_CUSTOM_TARGET( SecurityPenetrationTestWorker ALL DEPENDS DenialOfService.py SanitizedEnvironment.py )



