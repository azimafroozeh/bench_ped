# ---------------------------------------------------------------------------
# Stats
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------

add_executable(string_stats ${CMAKE_CURRENT_LIST_DIR}/StringStats.cpp)
target_include_directories(string_stats PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(string_stats Threads::Threads gflags mmapvector)


add_executable(string_fsst ${CMAKE_CURRENT_LIST_DIR}/StringFSST.cpp)
target_include_directories(string_fsst PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(string_fsst Threads::Threads gflags mmapvector fsst)


add_executable(string_sharing ${CMAKE_CURRENT_LIST_DIR}/StringSharing.cpp)
target_include_directories(string_sharing PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(string_sharing Threads::Threads gflags mmapvector cengine)