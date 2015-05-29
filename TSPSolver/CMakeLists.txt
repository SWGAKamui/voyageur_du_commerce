set(SDL2_INCLUDE_DIR /usr/local/include/SDL2/)
set(SDL2_LIB_DIR /usr/local/lib/)

include_directories(
    ${SDL2_INCLUDE_DIR}
)

link_directories(${VDC_C_SOURCE_DIR}/lib ${SDL2_LIB_DIR})

add_executable (TSPSolver TSPSolver.c Drawer.c Input.c TSPDrawer.c)

target_link_libraries(TSPSolver nearestNeighbour matrix tspReader mst bruteforce graph branchAndBound SDL2 SDL2_ttf)

install(TARGETS TSPSolver DESTINATION bin)
install(FILES fonts/PWBoldScript.ttf DESTINATION bin/fonts)
