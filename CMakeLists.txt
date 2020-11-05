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

add_executable(task3 3_parallel_sort.cpp)
target_link_libraries(task3
        share::function
        )

add_executable(task4 4_parallel_radixsort.cpp)
target_link_libraries(task4
        share::function
        )

add_executable(task5 5_task_group.cpp)
target_link_libraries(task5
        share::function
        )

add_executable(task6_1 6_1_concurrent_vector.cpp)
target_link_libraries(task6_1
        share::function
        )

add_executable(task6_2 6_2_concurrent_queue.cpp)
target_link_libraries(task6_2
        share::function
        )

add_executable(task7 7_simpson.cpp)
target_link_libraries(task7
        share::simps
        )

add_executable(task8_1 conveyor_8_1.cpp)
add_executable(task8_2 conveyor-transformer_8_2.cpp)








