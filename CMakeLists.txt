cmake_minimum_required (VERSION 3.5)
project(subprojects)

add_subdirectory(share)

add_executable(task1_1 1_1_parallel_for.cpp)
target_link_libraries(task1_1
        share::function
        )

add_executable(task1_2 1_2_parallel_for_each.cpp)
target_link_libraries(task1_2
        share::function
        )

add_executable(task2 2_transform.cpp)
target_link_libraries(task2
        share::function
        )

add_executable(task3 sort_3.cpp)
target_link_libraries(task3
        share::function
        )

add_executable(task4 sort_4.cpp)
target_link_libraries(task4
        share::function
        )

add_executable(task5 task_group_5.cpp)
target_link_libraries(task5
        share::function
        )

add_executable(task6 concurrent_col_6.cpp)
target_link_libraries(task6
        share::function
        )

add_executable(task7 simpson_7.cpp)
target_link_libraries(task7
        share::simps
        )

add_executable(task8_1 conveyor_8_1.cpp)
add_executable(task8_2 conveyor-transformer_8_2.cpp)








