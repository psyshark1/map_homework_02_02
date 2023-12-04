cmake_minimum_required (VERSION 3.8)

project (map_homeworks_02_01)
set (CMAKE_CXX_STANDARD 17)

add_executable (map_homeworks_02_01 map_homeworks_02_01.cpp)

target_compile_features(map_homeworks_02_01 PRIVATE cxx_std_17)