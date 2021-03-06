cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

################################################################################
# Require out-of-source builds
################################################################################
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

################################################################################
# Build Options
################################################################################
option(VoidEngine_Build_Standalone "Include sample project in game project" ON)
option(VoidEngine_Enable_Sample_Project "Include sample project in game project" OFF)

################################################################################
# Set build-configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Allow cmake to generate Solution Folders
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Set project-wide C++ compile flags
################################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("$<$<CONFIG:RELEASE>:/GL>")
add_compile_options("$<$<CONFIG:RELEASE>:/Ot>")
add_link_options("$<$<CONFIG:RELEASE>:/LTCG>")

################################################################################
# Set project root dir
################################################################################
set(VoidEngine_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Include dependencies and engine modules
################################################################################
add_subdirectory(Dependencies)
add_subdirectory(VoidEngine)