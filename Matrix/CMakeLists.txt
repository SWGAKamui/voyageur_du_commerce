add_library(matrix Matrix.c)

add_executable(TestMatrix Matrix.c TestMatrix.c)

install(TARGETS TestMatrix DESTINATION bin)
