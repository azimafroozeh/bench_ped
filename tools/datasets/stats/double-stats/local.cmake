# ---------------------------------------------------------------------------
# Stats
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------

add_executable(double_stats ${CMAKE_CURRENT_LIST_DIR}/DoubleStatsExec.cpp)
target_include_directories(double_stats PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(double_stats Threads::Threads gflags mmapvector)