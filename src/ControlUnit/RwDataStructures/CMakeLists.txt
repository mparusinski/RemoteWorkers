SET(RwDataStructures_SOURCES
    RwByteStream.cc
)

SET(RwDataStructures_HEADERS
    RwByteStream.h
)

ADD_LIBRARY(RwDataStructures STATIC 
  ${RwDataStructures_SOURCES} ${RwDataStructures_HEADERS})
