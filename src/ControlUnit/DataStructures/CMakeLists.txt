SET(DataStructures_SOURCES
    ByteStream.cpp
)

SET(DataStructures_HEADERS
    ByteStream.hpp
)

ADD_LIBRARY(DataStructures STATIC 
  ${DataStructures_SOURCES} ${DataStructures_HEADERS})
