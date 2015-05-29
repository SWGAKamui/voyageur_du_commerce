add_library(nearestNeighbour NearestNeighbour.c)

link_directories(${VDC_C_SOURCE_DIR}/lib)

add_executable (TestNearestNeighbour NearestNeighbour.c TestNearestNeighbour.c)

target_link_libraries(TestNearestNeighbour matrix)

install(TARGETS TestNearestNeighbour DESTINATION bin)