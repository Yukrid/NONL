cmake_minimum_required(VERSION 3.10)

project(NONL CXX)

add_executable(nonl ./no_newline.cpp)
target_compile_features(nonl PRIVATE cxx_std_14)
install(TARGETS nonl DESTINATION bin)
