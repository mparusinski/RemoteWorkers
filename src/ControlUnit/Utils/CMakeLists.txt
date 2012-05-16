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
   LoggerStrategy.hpp
   LoggerStrategy.cpp
   LoggerFileStrategy.hpp
   LoggerFileStrategy.cpp
   LoggerConsoleStrategy.hpp
   LoggerConsoleStrategy.cpp
)

ADD_LIBRARY(Utils ${UtilsSRC})

TARGET_LINK_LIBRARIES(Utils ${Boost_LIBRARIES})

