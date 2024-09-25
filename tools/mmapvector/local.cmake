add_library(mmapvector STATIC tools/mmapvector/MMapVector.cpp)
set(MMAPVECTOR_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(mmapvector PUBLIC ${SHARED_INCLUDE_DIRECTORY})
set_property(TARGET mmapvector APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${MMAPVECTOR_INCLUDE_DIR})