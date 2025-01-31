cmake_minimum_required(VERSION 3.10)
project(chess960)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${SMAKE_CXX_FLAGS} -O2")

add_executable(chess960 src/main.cpp)

target_link_libraries(chess960
    glfw
    GLEW
    GL
    pthread
)
