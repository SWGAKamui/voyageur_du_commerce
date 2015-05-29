add_library(bruteforce Bruteforce.c)

link_directories(${VDC_C_SOURCE_DIR}/lib)

add_executable (TestBruteforce Bruteforce.c TestBruteforce.c)

target_link_libraries(TestBruteforce matrix)

install(TARGETS TestBruteforce DESTINATION bin)
