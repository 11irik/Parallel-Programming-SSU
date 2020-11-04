project(share)

add_library(function src/Function.cpp)
add_library(simps src/Concurrent_Simps.cpp)

add_library(share::function ALIAS function)
add_library(share::simps ALIAS simps)

target_include_directories(function
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )

target_include_directories(simps
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )
