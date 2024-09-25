add_executable(bench_ped alp/manual/bench_ped.cpp)
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_ped.hpp)
target_include_directories(bench_ped PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(bench_ped PRIVATE ${CMAKE_SOURCE_DIR}/shared-headers)
target_include_directories(bench_ped PRIVATE ${CMAKE_SOURCE_DIR}/cengine)
target_include_directories(bench_ped PRIVATE ${CMAKE_SOURCE_DIR}/tools/mmapvector)
target_link_libraries(bench_ped PRIVATE cengine)


add_executable(test_ped alp/manual/test_ped.cpp)
target_include_directories(test_ped PRIVATE ${CMAKE_SOURCE_DIR}/shared-headers)
target_include_directories(test_ped PRIVATE ${CMAKE_SOURCE_DIR}/cengine)
target_include_directories(test_ped PRIVATE ${CMAKE_SOURCE_DIR}/tools/mmapvector)
target_link_libraries(test_ped PRIVATE cengine gtest)
