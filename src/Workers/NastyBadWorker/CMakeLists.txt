FILE( MAKE_DIRECTORY ${RemoteWorkers_Workers_BINARY_DIR}/NastyBadWorker/output )

ADD_CUSTOM_COMMAND(
  OUTPUT main.py
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/main.py ${CMAKE_CURRENT_BINARY_DIR}/NastyBadWorker
  DEPENDS main.py
)

ADD_CUSTOM_TARGET(NastyBadWorker ALL DEPENDS main.py)


