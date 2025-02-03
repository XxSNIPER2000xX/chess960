cmake_minimum_required(VERSION 3.10)
project(chess960)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${SMAKE_CXX_FLAGS} -O2")

file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(chess960 ${SRC})

target_include_directories(chess960 PRIVATE ${CMAKE_SOURCE_DIR}/src/h)

target_link_libraries(chess960
    glfw
    GLEW
    GL
    pthread
)
