cmake_minimum_required(VERSION 3.7)

project(ImGui CXX)

add_library(
        ImGui
        imconfig.h
        imgui.h
        imgui.cpp
        imgui_draw.cpp
        #imgui_internal.h
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        imgui_demo.cpp
        imgui_impl_opengl3.h
        imgui_impl_opengl3.cpp
        imgui_impl_glfw.h
        imgui_impl_glfw.cpp
)

add_library(ImGui::ImGui ALIAS ImGui)

target_include_directories (ImGui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(ImGui PRIVATE cxx_std_17)