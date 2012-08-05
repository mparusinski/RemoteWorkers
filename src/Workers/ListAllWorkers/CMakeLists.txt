INCLUDE_DIRECTORIES(
  ${RemoteWorkers_Workers_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_Workers_BINARY_DIR}
)

FILE( MAKE_DIRECTORY ${RemoteWorkers_Workers_BINARY_DIR}/ListAllWorkers/output )

SET(ListAllWorkersHEADERS
  Functions.h
)

SET(ListAllWorkersSRC
  Functions.cc
  main.cc
)

ADD_EXECUTABLE(ListAllWorkers
  ${ListAllWorkersSRC} ${ListAllWorkersHEADERS}
)

TARGET_LINK_LIBRARIES(ListAllWorkers ${QT_LIBRARIES})
