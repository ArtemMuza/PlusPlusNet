SET( SOURCES
    Log_system.cpp)

add_library(Log_sys ${SOURCES})
target_link_libraries(Log_sys Utils)