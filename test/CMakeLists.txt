cmake_minimum_required(VERSION 2.8.2)

#project(PoloParser_Test)

include(CTest)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(
    PROJ                googletest
    GIT_REPOSITORY      https://github.com/google/googletest.git
    GIT_TAG             master
    ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()


# Get the source files (could use GLOB_RECURSE)
file(GLOB PoloParser_SOURCES "${PROJECT_SOURCE_DIR}/src/polo-parser/*.cpp")
file(GLOB PoloParser_Test_SOURCES "${PROJECT_SOURCE_DIR}/test/polo-parser-test/*.cpp")
list(REMOVE_ITEM PoloParser_SOURCES "${PROJECT_SOURCE_DIR}/src/polo-parser/main.cpp")

# Add includes
include_directories("${PROJECT_SOURCE_DIR}/inc")

add_executable(polo-parser-test ${PoloParser_Test_SOURCES} ${PoloParser_SOURCES})
target_link_libraries(
    polo-parser-test
    gtest
    "/usr/local/lib/libclang.dylib"
)
add_test(NAME polo-parser-test COMMAND polo-parser-test)
