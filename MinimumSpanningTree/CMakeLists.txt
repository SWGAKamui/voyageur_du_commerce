add_library(mst MinSpanTree.c)
link_directories(${VDC_C_SOURCE_DIR}/lib)

add_executable (TestMST MinSpanTree.c TestMST.c)

target_link_libraries(TestMST matrix graph)

install(TARGETS TestMST DESTINATION bin)
