cmake_minimum_required(VERSION 3.14)

project(fastemaBenchmarks LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/project-is-top-level.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/folders.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/fetch-nanobench.cmake)

add_executable(ema_bench ema_bench.cpp)
target_include_directories(ema_bench PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(ema_bench nanobench)
target_compile_features(ema_bench PRIVATE cxx_std_23)