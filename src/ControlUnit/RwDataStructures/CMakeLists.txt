SET(DataStructures_SOURCES
    ByteStream.cc
)

SET(DataStructures_HEADERS
    ByteStream.h
)

ADD_LIBRARY(DataStructures STATIC 
  ${DataStructures_SOURCES} ${DataStructures_HEADERS})
