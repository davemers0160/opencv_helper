# ----------------------------------------------------------------------------
#  Root CMake file for the Select ROI Library
# ----------------------------------------------------------------------------
#
# To perform an out of source build do the following on the command line:
# 1. navigate to the root project directory (in this case DfD2)
# 2. mkdir build
# 3. cd build
# 4. depending on your system (windows/linux) type the following
# Example CMake build line for windows & VS2015
# windows: cmake -G "Visual Studio 14 2015 Win64" -DUSE_AVX_INSTRUCTIONS=ON ..
# linux: cmake -DUSE_AVX_INSTRUCTIONS=ON ..
#
# 5. To compile:
# windows: cmake --build . --config Release
# linux: cmake --build . --config Release -- -j10
#

cmake_minimum_required(VERSION 3.10)

project(draw_line VERSION 1.0 DESCRIPTION "Shared library for an viewing an image and selecting an roi using opencv")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(exe_name "draw_line")
set(default_build_type "Release")

set(PLATFORM "$ENV{PLATFORM}" CACHE INTERNAL "Copied from environment variable")
if("${PLATFORM}" STREQUAL "")
    set(PLATFORM "NOT_SET")
    message("The PLATFORM Environment variable is not set on this system.  Setting it to:")
endif()
message("Platform: " ${PLATFORM})

# find the root of the main project
string(FIND ${PROJECT_SOURCE_DIR} "/" INDEX REVERSE)
string(SUBSTRING ${PROJECT_SOURCE_DIR} 0 ${INDEX} PR_ROOT)

# Build Options
#option(DLIB_NO_GUI_SUPPORT "Enable this if you don't want to compile any of the dlib GUI code" ON)
option(USE_AVX_INSTRUCTIONS  "Compile your program with AVX instructions"  ON)
#option(BUILD_LIB  "Build the project into a library (.dll/.so) vs a standalone executable"  ON)
#option(WITH_OPENCV  "Build the project with OpenCV"  OFF)

#include(../cmake_utils/use_cpp_11.cmake)
#include(../cmake_utils/use_sse_avx.cmake)

# ----------------------------------------------------------------------------
if(WIN32)

elseif(UNIX)
    set(HOME "$ENV{HOME}" CACHE INTERNAL "Copied from environment variable")

endif()


# ----------------------------------------------------------------------------
# get the source files for the Library
file(GLOB SOURCES "src/*.cpp")

set(project_includes "include" 
    "${PR_ROOT}/common/include"
    )


# ----------------------------------------------------------------------------
# find OpenCV

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    set(project_includes ${project_includes} ${OpenCV_INCLUDE_DIRS})
    set(project_libs ${project_libs} ${OpenCV_LIBS})
else()
    message("OpenCV not found, so we won't build the project.")
endif()


# ----------------------------------------------------------------------------
message(" ")
message("--------------------------------------------------------------------------------")
message("Source Files: ")
foreach(S ${SOURCES})
    message("  " ${S})
endforeach()
message("--------------------------------------------------------------------------------")

message(" ")

message("--------------------------------------------------------------------------------")
message("Project Includes: ")
foreach(S ${project_includes})
    message("  " ${S})
endforeach()
message("--------------------------------------------------------------------------------")

message(" ")

message("--------------------------------------------------------------------------------")
message("Project Libraries: ")
foreach(S ${project_libs})
    message("  " ${S})
endforeach()
message("--------------------------------------------------------------------------------")


# ----------------------------------------------------------------------------
message("Building...")

include_directories(${project_includes})
add_executable(${exe_name} ${SOURCES})


if(WIN32)
    target_link_libraries(${exe_name} ${project_libs})
    
    message("MSVC Version: " ${MSVC_VERSION})
    
    if(MSVC AND (${CMAKE_VERSION} VERSION_GREATER "3.6.0"))
        target_compile_options(${exe_name} PRIVATE "/MP")
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${exe_name})
    endif()
    
elseif(UNIX)
    target_link_libraries(${exe_name} ${project_libs} ${CMAKE_DL_LIBS})
    
endif()

# ----------------------------------------------------------------------------
message(" ")
message(STATUS "Build Complete!")
message(" ")

