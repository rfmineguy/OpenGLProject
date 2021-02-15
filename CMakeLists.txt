cmake_minimum_required(VERSION 3.7)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/glad.c
        src/engine/util/Logger.cpp
        src/engine/test_framework/Test.cpp
        src/tests/QuadTest.cpp src/engine/shader/Shader.cpp src/engine/shader/Shader.h src/tests/ShaderTest.cpp src/tests/ShaderTest.h src/engine/model/Vertex.h src/engine/rendering/Renderer.cpp src/engine/rendering/Renderer.h)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

#include vendor files
include_directories(src/vendor src/engine src)

#Include library files
include_directories(dependencies/glfw/include)
include_directories(dependencies/glad/include)

#Add deps
add_subdirectory(dependencies)
add_subdirectory(src/vendor/imgui)

#Create .exe with the source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw)

target_include_directories(${PROJECT_NAME} PUBLIC src/vendor/imgui)

target_link_libraries(${PROJECT_NAME} ImGui::ImGui)