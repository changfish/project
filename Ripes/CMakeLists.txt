cmake_minimum_required(VERSION 3.10)

project(CacheSim)

set(CMAKE_CXX_STANDARD 14)

add_library(cachesim_lib L1CacheShim.cpp L2Cache.cpp)

target_include_directories(cachesim_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)

create_ripes_lib(cachesim LINK_TO_RIPES_LIB)
