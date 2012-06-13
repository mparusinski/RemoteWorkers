INCLUDE_DIRECTORIES(
  ${RemoteWorkers_Workers_SOURCE_DIR}
)

LINK_DIRECTORIES(
  ${RemoteWorkers_Workers_BINARY_DIR}
)

FILE( MAKE_DIRECTORY ${RemoteWorkers_Workers_BINARY_DIR}/SimpleTestWorker/output )

SET(SimpleTestWorkerSRC
  SimpleTestWorker.hpp
  SimpleTestWorker.cpp
  main.cpp
)

ADD_EXECUTABLE(SimpleTestWorker
  ${SimpleTestWorkerSRC}
)

TARGET_LINK_LIBRARIES(SimpleTestWorker ${QT_LIBRARIES})
