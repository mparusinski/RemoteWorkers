SET(RwDataStructures_SOURCES
  RwByteArray.cc
)

SET(RwDataStructures_HEADERS
  RwByteArray.h
)

ADD_LIBRARY(RwDataStructures STATIC 
  ${RwDataStructures_SOURCES} ${RwDataStructures_HEADERS})

