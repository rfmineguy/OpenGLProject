cmake_minimum_required(VERSION 3.7)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/glad.c
        src/vendor/tiny_obj_loader/tiny_obj_loader.cc
        src/engine/test_framework/Test.cpp
        src/tests/QuadTest.cpp
        src/engine/shader/Shader.cpp
        src/tests/MainTest.cpp
        src/engine/model/Vertex.h
        src/engine/texture/Texture.cpp
        src/vendor/stb_image/stb_setup.cpp
        src/engine/camera/Camera.h
        src/engine/camera/Camera.cpp
        src/tests/CameraTest.cpp src/tests/CameraTest.h
        src/tests/CubeTest.cpp  src/tests/CubeTest.h
        src/tests/TexturedCubeTest.cpp src/tests/TexturedCubeTest.h
        src/tests/LightingTest.cpp src/tests/LightingTest.h
        src/tests/MaterialTest.cpp src/tests/MaterialTest.h
        src/engine/shader/Material.h
        src/engine/shader/LightTypes.h
        src/engine/model/Mesh.cpp
        src/engine/model/Mesh.h
        src/tests/ModelTest.cpp
        src/tests/ModelTest.h
        src/engine/model/Model.cpp
        src/engine/model/Model.h src/engine/shader/Environment.h)

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
add_subdirectory(src/vendor/stb_image)
add_subdirectory(src/vendor/tiny_obj_loader)

#Create .exe with the source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC src/vendor/imgui)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ImGui::ImGui)
target_link_libraries(${PROJECT_NAME} StbImage::StbImage)
target_link_libraries(${PROJECT_NAME} TinyObjLoader)