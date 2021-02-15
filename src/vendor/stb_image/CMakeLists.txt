cmake_minimum_required(VERSION 3.7)

project(StbImage CXX)

add_library(
        StbImage
        stb_setup.cpp
        stb_image.cpp
        stb_image.h
)

add_library(StbImage::StbImage ALIAS StbImage)

target_include_directories(StbImage PUBLIC ".")

target_compile_features(StbImage PRIVATE cxx_std_17)