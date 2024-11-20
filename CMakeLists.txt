# ---------------------------------------------------------------------------
# BtrBlocks
# ---------------------------------------------------------------------------
project(BtrBlocks)
cmake_minimum_required(VERSION 3.7)

# ---------------------------------------------------------------------------
# Environment
# ---------------------------------------------------------------------------

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g")
add_compile_options(-march=native -Wno-error)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-fstandalone-debug)
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (APPLE)
    list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/bison)
    list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/flex)
endif (APPLE)

if (CYGWIN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif (CYGWIN)

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------

find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)

include("${CMAKE_SOURCE_DIR}/vendor/aws-sdk.cmake")
#include("${CMAKE_SOURCE_DIR}/vendor/benchmark.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/googletest.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/gflags.cmake")
#include("${CMAKE_SOURCE_DIR}/vendor/rapidjson.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/yaml-cpp.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/clang-tidy.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/fastpfor.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/spdlog.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/tbb.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/croaring.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/gdouble.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/turbo.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/lz4.cmake")
include("${CMAKE_SOURCE_DIR}/vendor/fsst.cmake")

# ---------------------------------------------------------------------------
# Includes
# ---------------------------------------------------------------------------

include("${CMAKE_SOURCE_DIR}/shared-headers/local.cmake")
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${FLEX_INCLUDE_DIRS}
        ${GTEST_INCLUDE_DIR}
        ${GFLAGS_INCLUDE_DIR}
)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

#include("${CMAKE_SOURCE_DIR}/playground/local.cmake")
include("${CMAKE_SOURCE_DIR}/cengine/local.cmake")
include("${CMAKE_SOURCE_DIR}/tools/local.cmake")

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Benchmarks
# ---------------------------------------------------------------------------

#include("${CMAKE_SOURCE_DIR}/benchmark/local.cmake")

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------

# add_executable(harbook harbook.cpp)
# add_dependencies(harbook cengine)
# target_link_libraries(harbook cengine psql)
# target_include_directories(harbook PRIVATE ${CENGINE_INCLUDE_DIR})
# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_custom_target(lint)
add_dependencies(lint ${lint_targets})

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------

message(STATUS "[cengine] settings")
message(STATUS "    GFLAGS_INCLUDE_DIR          = ${GFLAGS_INCLUDE_DIR}")
message(STATUS "    GFLAGS_LIBRARY_PATH         = ${GFLAGS_LIBRARY_PATH}")
message(STATUS "[TEST] settings")
message(STATUS "    GTEST_INCLUDE_DIR           = ${GTEST_INCLUDE_DIR}")
message(STATUS "    GTEST_LIBRARY_PATH          = ${GTEST_LIBRARY_PATH}")

include(FetchContent)
FetchContent_Declare(
        alp_repo
        GIT_REPOSITORY https://github.com/cwida/ALP.git
        GIT_TAG repro #
        GIT_SHALLOW TRUE
)

add_compile_definitions(PDE_CMAKE_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(ALP_ENABLE_CLANG_TIDY OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(alp_repo)
include_directories(${alp_repo_SOURCE_DIR}/data/include)

# Set ALP_CMAKE_SOURCE_DIR manually
set(ALP_CMAKE_SOURCE_DIR "${alp_repo_SOURCE_DIR}")
add_compile_definitions(ALP_CMAKE_SOURCE_DIR="${ALP_CMAKE_SOURCE_DIR}")

# Print the value of ALP_CMAKE_SOURCE_DIR
message("ALP_CMAKE_SOURCE_DIR: ${ALP_CMAKE_SOURCE_DIR}")

include("${CMAKE_SOURCE_DIR}/alp/manual/CMakeLists.txt")