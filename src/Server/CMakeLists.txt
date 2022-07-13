SET( SOURCES
    Server.cpp
    parsing/RequestParser.cpp
    connectivity/ServerListener.cpp)

add_library(Core ${SOURCES})