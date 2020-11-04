project(task7)

add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(${PROJECT_NAME}
        share::simps
        )