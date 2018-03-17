cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(PoloParser)

if($ENV{BUILD_NUMBER})
  set(BUILD_NUMBER $ENV{BUILD_NUMBER})
else()
  set(BUILD_NUMBER 0)
endif()

set(MYPROJECT_NAME "PoloParser")
set(MYPROJECT_VERSION "0.0.1.${BUILD_NUMBER}")

set(DEBUG_FLAGS "-g -O0 -Wall -Werr")
set(RELEASE_FLAGS "-O3 -Wall")

# Compiler flags
set(CMAKE_CXX_FLAGS ${RELEASE_FLAGS} )
if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -std=c++14  -stdlib=libc++" )
else()
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -std=c++14" )
endif()

set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${GCOV_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS_DEBUG ${GCOV_FLAGS})

set(CMAKE_CONFIGURATION_TYPES Debug Release)

add_subdirectory(src)

# Test project
enable_testing()
add_subdirectory(test)
