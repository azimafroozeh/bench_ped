# ---------------------------------------------------------------------------
# Benchmark
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Tester
# ---------------------------------------------------------------------------

add_executable(benchmark benchmark/placeholder.cpp)
target_link_libraries(benchmark cengine Threads::Threads)
target_include_directories(benchmark PRIVATE ${SHARED_INCLUDE_H})
target_include_directories(benchmark PRIVATE ${HARBOOK_INCLUDE_DIR})

# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_clang_tidy_target(lint_benchmark "${TEST_CC}")
add_dependencies(lint_benchmark gtest)
list(APPEND lint_targets lint_benchmark)
