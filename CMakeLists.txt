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

##
# vcpkg portion
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
  set(bootstrap_vcpkg_ext "bat")
else()
  set(bootstrap_vcpkg_ext "sh")
endif()

execute_process(
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/vcpkg/bootstrap-vcpkg.${bootstrap_vcpkg_ext}"
  RESULT_VARIABLE bootstrap_vcpkg_result
)

if(NOT bootstrap_vcpkg_result EQUAL 0)
  message(FATAL_ERROR "Bootstrapping failed with code: ${bootstrap_vcpkg_result}")
else()
  message(STATUS "Bootstrapping succeeded.")
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "vcpkg toolchain file")

# Folders for IDEs that support it
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# We need to specify these types since we are supporting multi-config IDEs like Xcode and Visual Studio
set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

add_subdirectory(Prototype)

