file(GLOB_RECURSE FLEXR_INTERMEDIATE_KERNEL_SRCS *.cc)

add_library(flexr_intermediate_kernel ${FLEXR_INTERMEDIATE_KERNEL_SRCS})
target_include_directories(flexr_intermediate_kernel PUBLIC "${PROJECT_SOURCE_DIR}")

target_compile_options(flexr_intermediate_kernel PUBLIC ${FLEXR_KERNEL_CXX_FLAGS})
target_link_libraries(flexr_intermediate_kernel ${FLEXR_KERNEL_LINKER_FLAGS})
target_link_libraries(flexr_intermediate_kernel ${FLEXR_KERNEL_LINKER_LIBS})
target_link_libraries(flexr_intermediate_kernel flexr_core)

install(TARGETS flexr_intermediate_kernel ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

