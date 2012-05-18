INCLUDE_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_SOURCE_DIR}
)

LINK_DIRECTORIES(
    ${RemoteWorkers_ControlUnit_BINARY_DIR}
)

SET(UtilsSRC STATIC
   CrossPlatform.hpp
   CrossPlatform.cpp
   Logger.hpp
   Logger.cpp
   LoggerBaseClass.hpp
   LoggerBaseClass.cpp
   FileLogger.hpp
   FileLogger.cpp
   ConsoleLogger.hpp
   ConsoleLogger.cpp
)

ADD_LIBRARY(Utils ${UtilsSRC})

TARGET_LINK_LIBRARIES(Utils ${Boost_LIBRARIES})

