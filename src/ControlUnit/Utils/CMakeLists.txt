INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(Utils_SOURCES
   SystemManagement.cpp
   Logger.cpp
   LoggerBaseClass.cpp
   FileLogger.cpp
   ConsoleLogger.cpp
   Profiler.cpp
)

SET(Utils_HEADERS
   SystemManagement.hpp
   Logger.hpp
   LoggerBaseClass.hpp
   FileLogger.hpp
   ConsoleLogger.hpp
   Profiler.hpp
)

ADD_LIBRARY(Utils STATIC ${Utils_SOURCES} ${Utils_HEADERS})

TARGET_LINK_LIBRARIES(Utils ${QT_LIBRARIES})
