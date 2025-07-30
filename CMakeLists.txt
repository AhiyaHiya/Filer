cmake_minimum_required(VERSION 3.20)

# Set the project name and version
project(Filer VERSION 0.1.0 LANGUAGES CXX)

# Specify the C++ standard
if(APPLE)
    set(CMAKE_CXX_STANDARD 20)
else()
    set(CMAKE_CXX_STANDARD 23)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(Prototype)

