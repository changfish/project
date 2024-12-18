# Project-specific configurations
cmake_minimum_required(VERSION 3.10)

# Project name and setup
project(Ripes CACHE CXX)

# Remove old library definition if exists
if(TARGET cachesim_lib)
    message(STATUS "Removing old cachesim_lib target")
    remove_library(cachesim_lib)
endif()

# Create a new library with the correct name
create_ripes_lib(cachesim cachesim_lib_new LINK_TO_RIPES_LIB)

# Add additional configuration, if needed
target_sources(cachesim_lib_new PRIVATE
    src/cachesim/l1cacheshim.cpp
    src/cachesim/l2cache.cpp
)

# Ensure Ripes library dependencies are linked
target_link_libraries(cachesim_lib_new Ripes)
