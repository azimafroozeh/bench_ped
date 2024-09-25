# ---------------------------------------------------------------------------
# cengine
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------
file(GLOB_RECURSE TEST_CASES ${CMAKE_CURRENT_LIST_DIR}/test-cases/**.cpp ${CMAKE_CURRENT_LIST_DIR}/test-cases/**.hpp)
# ---------------------------------------------------------------------------
# Tester
# ---------------------------------------------------------------------------

#add_executable(tester ${CMAKE_CURRENT_LIST_DIR}/tester.cpp ${TEST_CASES})
#target_link_libraries(tester cengine gtest gmock Threads::Threads)
#target_include_directories(tester PRIVATE ${SHARED_INCLUDE_DIRECTORY})
#target_include_directories(tester PRIVATE ${CMAKE_CURRENT_LIST_DIR})

enable_testing()
#add_test(harbook tester)

# ---------------------------------------------------------------------------
# Test Dataset Generator
# ---------------------------------------------------------------------------

add_executable(test_dataset_generator ${CMAKE_CURRENT_LIST_DIR}/DatasetGenerator.cpp)
target_link_libraries(test_dataset_generator gflags Threads::Threads mmapvector)
target_include_directories(test_dataset_generator PRIVATE ${SHARED_INCLUDE_DIRECTORY})


# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_clang_tidy_target(lint_test "${TEST_CC}")
add_dependencies(lint_test gtest)
list(APPEND lint_targets lint_test)
