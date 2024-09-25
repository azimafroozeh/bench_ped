# ---------------------------------------------------------------------------
# Stats
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------

add_executable(integer_stats ${CMAKE_CURRENT_LIST_DIR}/IntegerStats.cpp)
target_include_directories(integer_stats PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(integer_stats Threads::Threads gflags mmapvector)
