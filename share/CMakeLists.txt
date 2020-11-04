project (share)

add_library(${PROJECT_NAME} src/Function.cpp)
add_library(share::function ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
