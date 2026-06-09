cmake_minimum_required(VERSION 3.10)

project(OpenGLShader)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

add_executable(
    OpenGLShader
    src/main.cpp
    external/glad/src/glad.c
)

target_include_directories(OpenGLShader PRIVATE
    external
    include
    src
)

target_link_libraries(OpenGLShader
    glfw
)