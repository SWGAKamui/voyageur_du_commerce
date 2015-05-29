
link_directories(${VDC_C_SOURCE_DIR}/lib)

add_library(branchAndBound BranchAndBound.c)

add_executable (TestBranchAndBound BranchAndBound.c TestBranchAndBound.c)

target_link_libraries(TestBranchAndBound matrix bruteforce)

install(TARGETS TestBranchAndBound DESTINATION bin)
