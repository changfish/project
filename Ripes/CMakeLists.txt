# Project-specific configurations
cmake_minimum_required(VERSION 3.10)

# Project name and setup
project(Ripes CACHE CXX)

# Create a new library with the correct name
create_ripes_lib(cachesim cachesim_lib_new LINK_TO_RIPES_LIB)

# Add sources for L1 and L2 cache shim implementation
target_sources(cachesim_lib_new PRIVATE
    src/cachesim/l1cacheshim.cpp
    src/cachesim/l2cache.cpp
)

# Link required libraries
target_link_libraries(cachesim_lib_new Ripes)
