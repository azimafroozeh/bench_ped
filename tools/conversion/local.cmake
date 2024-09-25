# ---------------------------------------------------------------------------
# Conversion
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------

add_executable(csvtobtr ${CMAKE_CURRENT_LIST_DIR}/csvtobtr.cpp)
add_dependencies(csvtobtr cengine)
target_include_directories(csvtobtr PRIVATE ${CENGINE_INCLUDE_DIR})
target_link_libraries(csvtobtr cengine gflags)

add_executable(btrtocsv ${CMAKE_CURRENT_LIST_DIR}/btrtocsv.cpp)
add_dependencies(btrtocsv cengine)
target_include_directories(btrtocsv PRIVATE ${CENGINE_INCLUDE_DIR})
target_link_libraries(btrtocsv cengine mmapvector gflags)

add_executable(btrmeta ${CMAKE_CURRENT_LIST_DIR}/btrmeta.cpp)
add_dependencies(btrmeta cengine)
target_include_directories(btrmeta PRIVATE ${CENGINE_INCLUDE_DIR})
target_link_libraries(btrmeta cengine gflags)

add_executable(decompression-speed ${CMAKE_CURRENT_LIST_DIR}/decompression-speed.cpp)
add_dependencies(decompression-speed cengine)
target_include_directories(decompression-speed PRIVATE ${CENGINE_INCLUDE_DIR})
target_link_libraries(decompression-speed cengine gflags)

add_executable(decompression-speed-s3 ${CMAKE_CURRENT_LIST_DIR}/decompression-speed-s3.cpp)
add_dependencies(decompression-speed-s3 cengine)
target_include_directories(decompression-speed-s3 PRIVATE ${CENGINE_INCLUDE_DIR})
target_link_libraries(decompression-speed-s3 cengine gflags libaws-cpp-sdk-core libaws-cpp-sdk-s3-crt libaws-cpp-sdk-s3)

add_executable(bintocsv ${CMAKE_CURRENT_LIST_DIR}/bintocsv.cpp)
add_dependencies(bintocsv cengine)
target_include_directories(bintocsv PRIVATE ${CENGINE_INCLUDE_DIR})
target_link_libraries(bintocsv cengine mmapvector gflags)
