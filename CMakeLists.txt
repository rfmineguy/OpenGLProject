cmake_minimum_required(VERSION 3.7)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES code/main.cpp code/glad.c
                code/engine/util/Logger.cpp
                code/engine/test_framework/Test.cpp code/tests/QuadTest.cpp code/tests/QuadTest.h)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

#include vendor files
include_directories(vendor code/engine code)

#Include library files
include_directories(dependencies/glfw/include)
include_directories(dependencies/glad/include)

#Add deps
add_subdirectory(dependencies)
add_subdirectory(vendor/imgui)

#Create .exe with the source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/vendor/imgui)

target_link_libraries(${PROJECT_NAME} ImGui::ImGui)