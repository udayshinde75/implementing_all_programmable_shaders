cmake_minimum_required(VERSION 3.10)

project(OpenGLShader)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

add_executable(
    OpenGLShader
    src/main.cpp
)