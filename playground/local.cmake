# ---------------------------------------------------------------------------
# Playground
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# Files
# ---------------------------------------------------------------------------

add_executable(playground playground/playground.cpp)
target_include_directories(playground PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(playground fsst gflags Threads::Threads asan fastpfor)


if (CMAKE_BUILD_TYPE MATCHES Debug)
    # CMAKE_<LANG>_STANDARD_LIBRARIES
    target_compile_options(playground PRIVATE -fsanitize=address)
endif()

add_executable(rle playground/rle.cpp)
target_include_directories(rle PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(rle fastpfor gflags Threads::Threads mmapvector)

add_executable(fsst_0 playground/fsst_0.cpp)
target_compile_options(fsst_0 PUBLIC -fsanitize=address)
target_link_libraries(fsst_0 fsst pthread mmapvector asan)

add_executable(for_tests playground/for_tests.cpp)
target_include_directories(for_tests PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(for_tests cengine gflags)

add_executable(tbb_exmaple playground/tbb.cpp)
target_link_libraries(tbb_exmaple tbb)

add_executable(p_double playground/double.cpp)
target_include_directories(p_double PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_include_directories(p_double PUBLIC ${GDOUBLE_ROOT_DIR})
target_link_libraries(p_double ${GDOUBLE_ROOT_DIR}/libdouble-conversion.a)

add_executable(double_benchmarking playground/double_benchmarking.cpp)
target_include_directories(double_benchmarking PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_link_libraries(double_benchmarking gdouble)

add_executable(pseudodecimal_benchmark playground/pseudodecimal_benchmark.cpp)
#target_include_directories(pseudodecimal_benchmark PUBLIC ${SHARED_INCLUDE_DIRECTORY})
target_include_directories(pseudodecimal_benchmark PRIVATE ${CENGINE_INCLUDE_DIR})
add_dependencies(pseudodecimal_benchmark cengine)
#target_link_libraries(pseudodecimal_benchmark cengine fsst pthread mmapvector gflags)
target_link_libraries(pseudodecimal_benchmark cengine gflags)

configure_file(playground/pbi-double-columns.txt pbi-double-columns.txt COPYONLY)
configure_file(playground/pbi-double-columns-filtered.txt pbi-double-columns-filtered.txt COPYONLY)

add_executable(test-s3 playground/test-s3.cpp)
target_link_libraries(test-s3 libaws-cpp-sdk-core libaws-cpp-sdk-s3)
add_executable(test-s3-crt playground/test-s3-crt.cpp)
target_link_libraries(test-s3-crt libaws-cpp-sdk-core libaws-cpp-sdk-s3-crt libaws-cpp-sdk-s3)
add_executable(test-s3-custom-stream playground/test-s3-custom-stream.cpp)
target_link_libraries(test-s3-custom-stream libaws-cpp-sdk-core libaws-cpp-sdk-s3)
add_executable(test-s3-transfer playground/test-s3-transfer.cpp)
target_link_libraries(test-s3-transfer libaws-cpp-sdk-core libaws-cpp-sdk-s3 libaws-cpp-sdk-transfer)
add_executable(generate_s3_data playground/generate_s3_data.cpp)
target_link_libraries(generate_s3_data libaws-cpp-sdk-core libaws-cpp-sdk-s3-crt tbb)
