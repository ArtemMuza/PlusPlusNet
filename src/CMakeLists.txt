SET(SOURCES 
    main.cpp
    RequestParser.cpp
    ServerListener.cpp)

add_subdirectory(log_system)
add_subdirectory(utils)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Utils)
target_link_libraries(${PROJECT_NAME} Log_sys)
