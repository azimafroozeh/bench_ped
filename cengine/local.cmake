# ---------------------------------------------------------------------------
# CENGINE
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Includes
# ---------------------------------------------------------------------------
set(
        CENGINE_CC_LINTER_IGNORE
)
# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------
file(GLOB_RECURSE CENGINE_CC cengine/**/**.cpp cengine/**.cpp cengine/**.hpp cengine/**.c cengine/**.h)
if (NOT UNIX)
    message(SEND_ERROR "unsupported platform")
endif ()

# Gather lintable files
set(CENGINE_CC_LINTING "")
foreach (SRC_FILE ${CENGINE_CC})
    list(FIND CENGINE_CC_LINTER_IGNORE "${SRC_FILE}" SRC_FILE_IDX)
    if (${SRC_FILE_IDX} EQUAL -1)
        list(APPEND CENGINE_CC_LINTING "${SRC_FILE}")
    endif ()
endforeach ()

# ---------------------------------------------------------------------------
# Library
# ---------------------------------------------------------------------------

add_library(cengine STATIC ${CENGINE_CC})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    # CMAKE_<LANG>_STANDARD_LIBRARIES
    #    target_compile_options(cengine PUBLIC -fsanitize=address)
    target_compile_options(cengine PUBLIC -g)
endif ()
find_package(BZip2 1.0.6 REQUIRED)
target_link_libraries(cengine gflags Threads::Threads yaml mmapvector fsst fastpfor BZip2::BZip2 tbb croaring gdouble turbo lz4) #asan
target_include_directories(cengine PUBLIC ${SPDLOG_INCLUDE_DIR})
target_include_directories(cengine PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_include_directories(cengine PRIVATE cengine)
set(CENGINE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})

set_property(TARGET cengine APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CENGINE_INCLUDE_DIR})

add_dependencies(cengine spdlog_src)
# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_clang_tidy_target(lint_src "${CENGINE_CC_LINTING}")
list(APPEND lint_targets lint_src)
