cmake_minimum_required(VERSION 2.6)

# Remember the name of your project!!
project(VDC_C)

#Send the -std=c99 flag to the gcc compiler
add_definitions(-std=c99 -g)

set (CMAKE_INSTALL_PREFIX .)

#Indicate directories to find library header files
include_directories(
    ${VDC_C_SOURCE_DIR}/include
)

#Indicate directories to find project code
add_subdirectory(Bruteforce)
add_subdirectory(Matrix)
add_subdirectory(NearestNeighbour)
add_subdirectory(MinimumSpanningTree)
add_subdirectory(Graph)
add_subdirectory(BranchAndBound)
add_subdirectory(TSP)

enable_testing()

# Crée une cible "check" pour make. Cette cible lance la commande "ctest"
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

add_test(TestBruteforce Bruteforce/TestBruteforce)
add_test(TestMatrix Matrix/TestMatrix)
add_test(TestNearestNeighbour NearestNeighbour/TestNearestNeighbour)
add_test(TestMST MinimumSpanningTree/TestMST)
add_test(TestGraph Graph/TestGraph)
add_test(TestBranchAndBound BranchAndBound/TestBranchAndBound)
add_test(TestTSP TSP/TestTSP)

add_custom_target(memcheck COMMAND ${VDC_C_SOURCE_DIR}/Testing/memcheck.sh)
add_custom_target(speedcheck COMMAND ${VDC_C_SOURCE_DIR}/Testing/speedcheck.sh)

# Décommentez la ligne pour avoir le programme final (nécessite SDL2)

# add_subdirectory(TSPSolver)
