SET( SOURCES
    Server.cpp
    parsing/RequestParser.cpp
    connectivity/ServerListener.cpp
    parsing/UrlParser.cpp)

add_library(Core ${SOURCES})