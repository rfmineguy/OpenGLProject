cmake_minimum_required(VERSION 3.7)

project(TinyObjLoader)

add_library(
        TinyObjLoader
        tiny_obj_loader.cc)

add_library(TinyObjLoader::TinyObjLoader ALIAS TinyObjLoader)

target_include_directories(TinyObjLoader PUBLIC ".")

target_compile_features(TinyObjLoader PRIVATE cxx_std_17)