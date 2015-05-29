add_library(tspReader TSP.c)

link_directories(${VDC_C_SOURCE_DIR}/lib)

add_executable (TestTSP TSP.c TestTSP.c)

target_link_libraries(TestTSP matrix)

install(TARGETS TestTSP DESTINATION bin)
install(FILES exemple10.tsp exemple14.tsp DESTINATION resources)